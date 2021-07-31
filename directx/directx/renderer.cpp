#include <sstream>

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

	HRESULT hResult;

	if (FAILED(hResult = D3D11CreateDeviceAndSwapChain(
		nullptr,
		D3D_DRIVER_TYPE_HARDWARE,
		nullptr,
		0,
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

const char* Renderer::HrException::getType() const noexcept
{
	return "Renderer exception";
}

const char* Renderer::DeviceRemovedException::getType() const noexcept
{
	return "Renderer exception [Device Removed] (DXGI_ERROR_DEVICE_REMOVED)";
}