#include <sstream>
#include <cmath>
#include <d3dcompiler.h>
#include <DirectXMath.h>

#include "renderer.h"
#include "renderer_throw_macros.h"

Renderer::Renderer(HWND hWnd)
{
	DXGI_SWAP_CHAIN_DESC swapChainDescription = {};
	swapChainDescription.BufferDesc.Width = 0;
	swapChainDescription.BufferDesc.Height = 0;
	swapChainDescription.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	swapChainDescription.BufferDesc.RefreshRate.Numerator = 0;
	swapChainDescription.BufferDesc.RefreshRate.Denominator = 0;
	swapChainDescription.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	swapChainDescription.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	swapChainDescription.SampleDesc.Count = 1;
	swapChainDescription.SampleDesc.Quality = 0;
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.BufferCount = 1;
	swapChainDescription.OutputWindow = hWnd;
	swapChainDescription.Windowed = TRUE;
	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
	swapChainDescription.Flags = 0;

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
		&swapChainDescription,
		&swapChain,
		&device,
		nullptr,
		&context
	));

	Microsoft::WRL::ComPtr<ID3D11Resource> backBuffer;
	RENDERER_THROW_NOINFO(hResult, swapChain->GetBuffer(0, __uuidof(ID3D11Resource), &backBuffer));
	RENDERER_THROW_NOINFO(hResult, device->CreateRenderTargetView(backBuffer.Get(), nullptr, &renderTarget));

	D3D11_DEPTH_STENCIL_DESC depthStencilDescription = {};
	depthStencilDescription.DepthEnable = TRUE;
	depthStencilDescription.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDescription.DepthFunc = D3D11_COMPARISON_LESS;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> depthStencilState;

	RENDERER_THROW_NOINFO(hResult, device->CreateDepthStencilState(&depthStencilDescription, &depthStencilState));
	context->OMSetDepthStencilState(depthStencilState.Get(), 1);

	Microsoft::WRL::ComPtr<ID3D11Texture2D> depthStencilTexture;
	D3D11_TEXTURE2D_DESC depthStencilTextureDescription = {};
	depthStencilTextureDescription.Width = 800;
	depthStencilTextureDescription.Height = 600;
	depthStencilTextureDescription.MipLevels = 1;
	depthStencilTextureDescription.ArraySize = 1;
	depthStencilTextureDescription.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilTextureDescription.SampleDesc.Count = 1;
	depthStencilTextureDescription.SampleDesc.Quality = 0;
	depthStencilTextureDescription.Usage = D3D11_USAGE_DEFAULT;
	depthStencilTextureDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	RENDERER_THROW_NOINFO(hResult, device->CreateTexture2D(&depthStencilTextureDescription, nullptr, &depthStencilTexture));

	D3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDescription = {};
	depthStencilViewDescription.Format = DXGI_FORMAT_D32_FLOAT;
	depthStencilViewDescription.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
	depthStencilViewDescription.Texture2D.MipSlice = 0;
	RENDERER_THROW_NOINFO(hResult, device->CreateDepthStencilView(depthStencilTexture.Get(), &depthStencilViewDescription, &depthStencilView));

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
DxgiInfoManager& Renderer::getInfoManager() const noexcept
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