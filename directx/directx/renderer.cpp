#include <sstream>
#include <cmath>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "renderer.h"
#include "renderer_throw_macros.h"

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
	RENDERER_THROW_NOINFO(hResult, D3D11CreateDeviceAndSwapChain(
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
	));

	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	RENDERER_THROW_NOINFO(hResult, swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer));
	RENDERER_THROW_NOINFO(hResult, device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTarget));

	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};
	depthStencilDesc.DepthEnable = TRUE;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;

	RENDERER_THROW_NOINFO(hResult, device->CreateDepthStencilState(&depthStencilDesc, &depthStencilState));
	deviceContext->OMSetDepthStencilState(depthStencilState.Get(), 1);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilTexture;
	D3D11_TEXTURE2D_DESC depthStencilTextureDesc = {};
	depthStencilTextureDesc.Width = 800;
	depthStencilTextureDesc.Height = 600;
	depthStencilTextureDesc.MipLevels = 1;
	depthStencilTextureDesc.ArraySize = 1;
	depthStencilTextureDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilTextureDesc.SampleDesc.Count = 1;
	depthStencilTextureDesc.SampleDesc.Quality = 0;
	depthStencilTextureDesc.Usage = D3D11_USAGE_DEFAULT;
	depthStencilTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	RENDERER_THROW_NOINFO(hResult, device->CreateTexture2D(&depthStencilTextureDesc, nullptr, &depthStencilTexture));

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc = {};
	depthStencilViewDesc.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilViewDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDesc.Texture2D.MipSlice = 0;
	RENDERER_THROW_NOINFO(hResult, device->CreateDepthStencilView(depthStencilTexture.Get(), &depthStencilViewDesc, &depthStencilView));

	deviceContext->OMSetRenderTargets(1, renderTarget.GetAddressOf(), depthStencilView.Get());
}

void Renderer::endFrame()
{
	HRESULT hResult;
	RENDERER_THROW_NOINFO(hResult, swapChain->Present(1u, 0u));
}

void Renderer::clearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red, green, blue };
	deviceContext->ClearRenderTargetView(renderTarget.Get(), color);
	deviceContext->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::drawTestTriangle(float angle, float x, float y)
{
	struct Vertex
	{
		struct
		{
			float x;
			float y;
			float z;
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
		{ -1.0f,-1.0f,-1.0f	 },
		{ 1.0f,-1.0f,-1.0f	 },
		{ -1.0f,1.0f,-1.0f	 },
		{ 1.0f,1.0f,-1.0f	  },
		{ -1.0f,-1.0f,1.0f	 },
		{ 1.0f,-1.0f,1.0f	  },
		{ -1.0f,1.0f,1.0f	 },
		{ 1.0f,1.0f,1.0f	 },
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
	RENDERER_THROW_NOINFO(hResult, device->CreateBuffer(&vertexBufferDesription, &vertexSourceData, &vertexBuffer));

	const UINT stride = sizeof(Vertex);
	const UINT offset = 0;
	deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

	const unsigned short indices[] =
	{
		0,2,1, 2,3,1,
		1,3,5, 3,7,5,
		2,6,3, 3,6,7,
		4,5,7, 4,7,6,
		0,4,2, 2,4,6,
		0,1,4, 1,5,4
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

	RENDERER_THROW_NOINFO(hResult, device->CreateBuffer(&indexBufferDesription, &indexSourceData, &indexBuffer));

	deviceContext->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R16_UINT, 0);

	struct ConstantData
	{
		DirectX::XMMATRIX transform;
		struct
		{
			float r;
			float g;
			float b;
			float a;
		} face_colors[6];
	};
	const ConstantData constantData = {
		DirectX::XMMatrixTranspose(
			DirectX::XMMatrixRotationZ(angle) *
			DirectX::XMMatrixRotationX(angle) *
			DirectX::XMMatrixTranslation(x, y, 4.0f) *
			DirectX::XMMatrixPerspectiveLH(1.0f, 3.0f / 4.0f, 0.5f, 10.f)
		),
		{
			{1.0f,0.0f,1.0f},
			{1.0f,0.0f,0.0f},
			{0.0f,1.0f,0.0f},
			{0.0f,0.0f,1.0f},
			{1.0f,1.0f,0.0f},
			{0.0f,1.0f,1.0f},
		}
	};

	Microsoft::WRL::ComPtr<ID3D11Buffer> constantBuffer;

	D3D11_BUFFER_DESC constantBufferDesription = {};
	constantBufferDesription.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	constantBufferDesription.Usage = D3D11_USAGE_DYNAMIC;
	constantBufferDesription.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	constantBufferDesription.MiscFlags = 0;
	constantBufferDesription.ByteWidth = sizeof(constantData);
	constantBufferDesription.StructureByteStride = sizeof(ConstantData);

	D3D11_SUBRESOURCE_DATA constantSourceData = {};
	constantSourceData.pSysMem = &constantData;

	RENDERER_THROW_NOINFO(hResult, device->CreateBuffer(&constantBufferDesription, &constantSourceData, &constantBuffer));

	deviceContext->VSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());
	deviceContext->PSSetConstantBuffers(0, 1, constantBuffer.GetAddressOf());

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
		{"Position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
	};
	device->CreateInputLayout(inputElementDesc, (UINT)std::size(inputElementDesc), blob->GetBufferPointer(), blob->GetBufferSize(), &inputLayout);

	deviceContext->IASetInputLayout(inputLayout.Get());
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	D3D11_VIEWPORT viewport;
	viewport.Width = 800;
	viewport.Height = 600;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	deviceContext->RSSetViewports(1, &viewport);

	CHECK_INFO_MESSAGES(deviceContext->DrawIndexed((UINT)std::size(indices), 0, 0));
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