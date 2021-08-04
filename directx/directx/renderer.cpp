#include <sstream>
#include <d3dcompiler.h>

#include "renderer.h"

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swapChainDesc = {};
	swapChainDesc.BufferDesc.Width = 0;
	swapChainDesc.BufferDesc.Height = 0;
	swapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDesc.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDesc.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDesc.SampleDesc.Count = 1;
	swapChainDesc.SampleDesc.Quality = 0;
	swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDesc.BufferCount = 1;
	swapChainDesc.OutputWindow = hWnd;
	swapChainDesc.Windowed = TRUE;
	swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDesc.Flags = 0;

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
		&swapChainDesc,
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
		struct
		{
			float x;
			float y;
		} pos;
		struct
		{
			unsigned char r;
			unsigned char g;
			unsigned char b;
			unsigned char a;
		} color;
	};

	const Vertex vertices[] =
	{
		{ 0.0f, 0.5f, 255, 0, 0, 0 },
		{ 0.5f, -0.5f, 0, 255, 0, 0 },
		{ -0.5f, -0.5f, 0, 0, 255, 0 },
		{ -0.3f, 0.3f, 0, 255, 0, 0 },
		{ 0.3f, 0.3f, 0, 0, 255, 0 },
		{ 0.0f, -0.8f, 255, 0, 0, 0 },
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> vertexBuffer;

	D3D11_BUFFER_DESC vertexBufferDesription = {};
	vertexBufferDesription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesription.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDesription.CPUAccessFlags = 0;
	vertexBufferDesription.MiscFlags = 0;
	vertexBufferDesription.ByteWidth = sizeof(vertices);
	vertexBufferDesription.StructureByteStride = sizeof(Vertex);

	D3D11_SUBRESOURCE_DATA vertexSourceData = {};
	vertexSourceData.pSysMem = vertices;

	HRESULT hResult;
	if (FAILED(hResult = device->CreateBuffer(&vertexBufferDesription, &vertexSourceData, &vertexBuffer)))
	{
		throw HrException(__LINE__, __FILE__, hResult);
	}

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

	const unsigned short indices[] =
	{
		0,1,2,
		0,2,3,
		0,4,1,
		2,1,5,
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> indexBuffer;

	D3D11_BUFFER_DESC indexBufferDesription = {};
	indexBufferDesription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesription.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesription.CPUAccessFlags = 0;
	indexBufferDesription.MiscFlags = 0;
	indexBufferDesription.ByteWidth = sizeof(indices);
	indexBufferDesription.StructureByteStride = sizeof(unsigned short);

	D3D11_SUBRESOURCE_DATA indexSourceData = {};
	indexSourceData.pSysMem = indices;

	if (FAILED(hResult = device->CreateBuffer(&indexBufferDesription, &indexSourceData, &indexBuffer)))
	{
		throw HrException(__LINE__, __FILE__, hResult);
	}

	deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

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
	const D3D11_INPUT_ELEMENT_DESC inputElementDesc[] =
	{
		{"Position", 0, DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0},
		{"Color", 0, DXGI_FORMAT_R8G8B8A8_UNORM, 0, 8, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(inputElementDesc, (UINT)std::size(inputElementDesc), blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);

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

	deviceContext->DrawIndexed((UINT)std::size(indices), 0, 0);

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