#include <pickle/directx_renderer.h>

#include <pickle/logger.h>

pickle::renderer::DirectXRenderer::DirectXRenderer(HWND hWnd, int width, int height)
{
    DXGI_SWAP_CHAIN_DESC scd;

    ZeroMemory(&scd, sizeof(DXGI_SWAP_CHAIN_DESC));

    scd.BufferCount = 1;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.OutputWindow = hWnd;
    scd.SampleDesc.Count = 4;
    scd.Windowed = TRUE;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

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

    ID3D11Texture2D *backBufferTexture;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID*) &backBufferTexture);

    device->CreateRenderTargetView(backBufferTexture, NULL, &backBuffer);
    backBufferTexture->Release();

    deviceContext->OMSetRenderTargets(1, &backBuffer, NULL);

    D3D11_VIEWPORT viewport;
    ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

    viewport.TopLeftX = 0;
    viewport.TopLeftY = 0;
    viewport.Width = width;
    viewport.Height = height;

    deviceContext->RSSetViewports(1, &viewport);
}

pickle::renderer::DirectXRenderer::~DirectXRenderer()
{
    swapChain->SetFullscreenState(FALSE, NULL);

    swapChain->Release();
    backBuffer->Release();
    device->Release();
    deviceContext->Release();
}

void pickle::renderer::DirectXRenderer::render() const
{
    float color[4] = { 0.0f, 0.2f, 0.4f, 1.0f };
    deviceContext->ClearRenderTargetView(backBuffer, color);
    swapChain->Present(0, 0);
}