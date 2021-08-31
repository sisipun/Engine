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
		&context
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
	context->OMSetDepthStencilState(depthStencilState.Get(), 1);

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

	context->OMSetRenderTargets(1, renderTarget.GetAddressOf(), depthStencilView.Get());

	D3D11_VIEWPORT viewport;
	viewport.Width = 800;
	viewport.Height = 600;
	viewport.MinDepth = 0;
	viewport.MaxDepth = 1;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	context->RSSetViewports(1, &viewport);
}

void Renderer::endFrame()
{
	HRESULT hResult;
	RENDERER_THROW_NOINFO(hResult, swapChain->Present(1u, 0u));
}

void Renderer::clearBuffer(float red, float green, float blue) noexcept
{
	const float color[] = { red, green, blue };
	context->ClearRenderTargetView(renderTarget.Get(), color);
	context->ClearDepthStencilView(depthStencilView.Get(), D3D11_CLEAR_DEPTH, 1.0f, 0);
}

void Renderer::drawIndexed(UINT count) const
{
	CHECK_INFO_MESSAGES(context->DrawIndexed(count, 0, 0));
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

ID3D11Device* Renderer::getDevice() const noexcept
{
	return device.Get();
}

ID3D11DeviceContext* Renderer::getContext() const noexcept
{
	return context.Get();
}

DirectX::XMMATRIX Renderer::getProjection() const noexcept
{
	return projection;
}

void Renderer::setProjection(DirectX::XMMATRIX projection) noexcept
{
	this->projection = projection;
}

#ifndef NDEBUG
DxgiInfoManager& Renderer::getInfoManager() noexcept
{
	return infoManager;
}
#endif

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