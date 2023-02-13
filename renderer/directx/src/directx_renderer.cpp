#include <pickle/directx_renderer.h>

#include <pickle/logger.h>

pickle::renderer::DirectXRenderer::DirectXRenderer(HWND hWnd)
{
    LOG_INFO("Inited DirectX");
    DXGI_SWAP_CHAIN_DESC scd;

    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 4;
    scd.Windowed = TRUE;

    D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &scd,
        &swapChain,
        &device,
        NULL,
        &deviceContext
    );
}

pickle::renderer::DirectXRenderer::~DirectXRenderer()
{
    swapChain->Release();
    device->Release();
    deviceContext->Release();
}

void pickle::renderer::DirectXRenderer::render() const
{
    LOG_INFO("Rendered DirectX");
}