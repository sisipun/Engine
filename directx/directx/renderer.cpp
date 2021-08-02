#include <sstream>
#include <d3dcompiler.h>

#include "renderer.h"

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC sd = {};
	sd.BufferDesc.Width = 0;
	sd.BufferDesc.Height = 0;
	sd.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	sd.BufferDesc.RefreshRate.Numerator = 0;
	sd.BufferDesc.RefreshRate.Denominator = 0;
	sd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	sd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	sd.SampleDesc.Count = 1;
	sd.SampleDesc.Quality = 0;
	sd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	sd.BufferCount = 1;
	sd.OutputWindow = hWnd;
	sd.Windowed = TRUE;
	sd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	sd.Flags = 0;

	UINT swapCreateFlags = 0u;
#ifndef NDEBUG
	swapCreateFlags |= D3D11_CREATE_DEVICE_DEBUG;
#endif

	HRESULT hResult;
	if (FAILED(hResult = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		swapCreateFlags,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&sd,
		&swapChain,
		&device,
		nullptr,
		&deviceContext
	)))
	{
		throw Renderer::HrException(__LINE__, __FILE__, hResult);
	}

	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	if (FAILED(hResult = swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer)))
	{
		throw Renderer::HrException(__LINE__, __FILE__, hResult);
	}
	if (FAILED(hResult = device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTarget)))
	{
		throw Renderer::HrException(__LINE__, __FILE__, hResult);
	}
}

void Renderer::endFrame()
{
#ifndef NDEBUG
	infoManager.set();
#endif
	HRESULT hResult;
	if (FAILED(hResult = swapChain->Present(1u, 0u)))
	{
		if (hResult == DXGI_ERROR_DEVICE_REMOVED)
		{
			throw Renderer::DeviceRemovedException(__LINE__, __FILE__, hResult);
		}

		throw Renderer::HrException(__LINE__, __FILE__, hResult);
	}
}

void Renderer::clearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red, green, blue };
	deviceContext->ClearRenderTargetView(renderTarget.Get(), color);
}

void Renderer::drawTestTriangle()
{
	struct Vertex
	{
		float x;
		float y;
	};

	const Vertex vertices[] =
	{
		{0.0f, 0.5f},
		{0.5f, -0.5f},
		{-0.5f, -0.5f}
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

	D3D11_BUFFER_DESC bufferDesription = {};
	bufferDesription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bufferDesription.Usage = D3D11_USAGE_DEFAULT;
	bufferDesription.CPUAccessFlags = 0;
	bufferDesription.MiscFlags = 0;
	bufferDesription.ByteWidth = sizeof(vertices);
	bufferDesription.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA sourceData = {};
	sourceData.pSysMem = vertices;

	HRESULT hResult;
	if (FAILED(hResult = device->CreateBuffer(&bufferDesription, &sourceData, &vertexBuffer)))
	{
		throw HrException(__LINE__, __FILE__, hResult);
	}

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

	Microsoft::WRL::ComPtr<ID3DBlob> blob;

	Microsoft::WRL::ComPtr<ID3D11PixelShader> pixelShader;
	D3DReadFileToBlob(L"pixel.cso", &blob);
	device->CreatePixelShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &pixelShader);
	deviceContext->PSSetShader(pixelShader.Get(), nullptr, 0);

	Microsoft::WRL::ComPtr<ID3D11VertexShader> vertexShader;
	D3DReadFileToBlob(L"vertex.cso", &blob);
	device->CreateVertexShader(blob->GetBufferPointer(), blob->GetBufferSize(), nullptr, &vertexShader);
	deviceContext->VSSetShader(vertexShader.Get(), nullptr, 0);

	Microsoft::WRL::ComPtr<ID3D11InputLayout> inputLayout;
	const D3D11_INPUT_ELEMENT_DESC input_element_desc[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(input_element_desc, (UINT)std::size(input_element_desc), blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);

	deviceContext->IASetInputLayout(inputLayout.Get());
	deviceContext->OMSetRenderTargets(1, renderTarget.GetAddressOf(), nullptr);
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport;
	viewport.Width = 800;
	viewport.Height = 600;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	deviceContext->RSSetViewports(1, &viewport);

#ifndef NDEBUG
	infoManager.set();
#endif

	deviceContext->Draw((UINT)std::size(vertices), 0);

#ifndef NDEBUG
	{ auto v = infoManager.getMessages(); if (!v.empty()) { throw Renderer::InfoException(__LINE__, __FILE__, v); } }
#endif
}

Renderer::InfoException::InfoException(int line, const char* file, std::vector<std::string> infoMessages) noexcept : BaseException(line, file)
{
	for (const auto& message : infoMessages)
	{
		info += message;
		info.push_back('\n');
	}
	if (!info.empty())
	{
		info.pop_back();
	}
}


const char* Renderer::InfoException::what() const noexcept
{
	std::ostringstream oss;
	oss << getType() << std::endl << "\n[Error Info]\n" << getErrorInfo() << std::endl;
	oss << getOriginString();
	whatBuffer = oss.str();
	return whatBuffer.c_str();
}

const char* Renderer::InfoException::getType() const noexcept
{
	return "Renderer Info Exception";
}

std::string Renderer::InfoException::getErrorInfo() const noexcept
{
	return info;
}

const char* Renderer::HrException::getType() const noexcept
{
	return "Renderer Exception";
}

const char* Renderer::DeviceRemovedException::getType() const noexcept
{
	return "Renderer Exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}