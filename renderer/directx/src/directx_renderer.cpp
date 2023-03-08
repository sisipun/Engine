#include <pickle/directx_renderer.h>

#include <xnamath.h>
#include <tchar.h>

#include <pickle/math.h>
#include <pickle/logger.h>

struct ConstantBuffer
{
    XMMATRIX world;
    XMMATRIX view;
    XMMATRIX projection;
};

pickle::renderer::DirectXRenderer::DirectXRenderer(HWND hWindow, int width, int height)
{
    DXGI_SWAP_CHAIN_DESC swapChainDesc;
    ZeroMemory(&swapChainDesc, sizeof(DXGI_SWAP_CHAIN_DESC));

    swapChainDesc.BufferCount = 1;
    swapChainDesc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDesc.BufferDesc.Width = width;
    swapChainDesc.BufferDesc.Height = height;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.OutputWindow = hWindow;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.Windowed = TRUE;
    swapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

    D3D11CreateDeviceAndSwapChain(
        NULL,
        D3D_DRIVER_TYPE_HARDWARE,
        NULL,
        NULL,
        NULL,
        NULL,
        D3D11_SDK_VERSION,
        &swapChainDesc,
        &swapChain,
        &device,
        NULL,
        &deviceContext);

    ID3D11Texture2D *backBufferTexture;
    swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), (LPVOID *)&backBufferTexture);

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

    ID3D10Blob *vertexBlob;
    ID3D10Blob *pixelBlob;
    D3DX11CompileFromFile(_T("resource/default_vertex.shader"), 0, 0, "main", "vs_4_0", 0, 0, 0, &vertexBlob, 0, 0);
    D3DX11CompileFromFile(_T("resource/default_pixel.shader"), 0, 0, "main", "ps_4_0", 0, 0, 0, &pixelBlob, 0, 0);

    device->CreateVertexShader(vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), NULL, &vertexSharer);
    device->CreatePixelShader(pixelBlob->GetBufferPointer(), pixelBlob->GetBufferSize(), NULL, &pixelShader);

    deviceContext->VSSetShader(vertexSharer, 0, 0);
    deviceContext->PSSetShader(pixelShader, 0, 0);

    D3D11_INPUT_ELEMENT_DESC inputElementDesc[] = {
        {"POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0},
        {"COLOR", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0}};

    device->CreateInputLayout(inputElementDesc, 3, vertexBlob->GetBufferPointer(), vertexBlob->GetBufferSize(), &inputLayout);

    deviceContext->IASetInputLayout(inputLayout);

    vertexBlob->Release();
    pixelBlob->Release();

    pickle::math::Vector<9, float> vertices[] = {
        pickle::math::Vector<9, float>({-0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f}),
        pickle::math::Vector<9, float>({-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f}),
        pickle::math::Vector<9, float>({0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f}),
        pickle::math::Vector<9, float>({-0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f}),
        pickle::math::Vector<9, float>({0.5f, 0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f}),
        pickle::math::Vector<9, float>({0.5f, -0.5f, -0.5f, 0.0f, 0.0f, -1.0f, 1.0f, 0.0f, 0.0f}),

        pickle::math::Vector<9, float>({-0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}),
        pickle::math::Vector<9, float>({0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}),
        pickle::math::Vector<9, float>({-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}),
        pickle::math::Vector<9, float>({-0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}),
        pickle::math::Vector<9, float>({0.5f, -0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}),
        pickle::math::Vector<9, float>({0.5f, 0.5f, 0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f, 0.0f}),

        pickle::math::Vector<9, float>({-0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}),
        pickle::math::Vector<9, float>({-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}),
        pickle::math::Vector<9, float>({0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}),
        pickle::math::Vector<9, float>({-0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}),
        pickle::math::Vector<9, float>({0.5f, 0.5f, 0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}),
        pickle::math::Vector<9, float>({0.5f, 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f}),

        pickle::math::Vector<9, float>({-0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f}),
        pickle::math::Vector<9, float>({0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f}),
        pickle::math::Vector<9, float>({-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f}),
        pickle::math::Vector<9, float>({-0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f}),
        pickle::math::Vector<9, float>({0.5f, -0.5f, -0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f}),
        pickle::math::Vector<9, float>({0.5f, -0.5f, 0.5f, 0.0f, -1.0f, 0.0f, 1.0f, 1.0f, 0.0f}),

        pickle::math::Vector<9, float>({-0.5f, -0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f}),
        pickle::math::Vector<9, float>({-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f}),
        pickle::math::Vector<9, float>({-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f}),
        pickle::math::Vector<9, float>({-0.5f, -0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f}),
        pickle::math::Vector<9, float>({-0.5f, 0.5f, 0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f}),
        pickle::math::Vector<9, float>({-0.5f, 0.5f, -0.5f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f}),

        pickle::math::Vector<9, float>({0.5f, -0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}),
        pickle::math::Vector<9, float>({0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}),
        pickle::math::Vector<9, float>({0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}),
        pickle::math::Vector<9, float>({0.5f, -0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}),
        pickle::math::Vector<9, float>({0.5f, 0.5f, -0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f}),
        pickle::math::Vector<9, float>({0.5f, 0.5f, 0.5f, 1.0f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f})};

    D3D11_BUFFER_DESC vertexBufferDesc;
    ZeroMemory(&vertexBufferDesc, sizeof(D3D11_BUFFER_DESC));

    vertexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    vertexBufferDesc.ByteWidth = sizeof(vertices);
    vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    vertexBufferDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA vertexBufferInitData;
    ZeroMemory(&vertexBufferInitData, sizeof(D3D11_SUBRESOURCE_DATA));

    vertexBufferInitData.pSysMem = vertices;

    device->CreateBuffer(&vertexBufferDesc, &vertexBufferInitData, &vertexBuffer);

    ConstantBuffer constantBufferData{
        XMMatrixTranspose(XMMatrixIdentity()),
        XMMatrixTranspose(XMMatrixLookAtLH(XMVectorSet( -1.0f, 1.0f, -1.0f, 0.0f), XMVectorSet(0.0f, 0.0f, 0.0f, 0.0f), XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f))),
        XMMatrixTranspose(XMMatrixPerspectiveFovLH(XM_PIDIV2, width / (FLOAT)height, 0.01f, 100.0f))
    };

    D3D11_BUFFER_DESC constantBufferDesc;
    ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));

    constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
    constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantBufferDesc.CPUAccessFlags = 0;

    D3D11_SUBRESOURCE_DATA constantBufferInitData;
    ZeroMemory(&constantBufferInitData, sizeof(D3D11_SUBRESOURCE_DATA));

    constantBufferInitData.pSysMem = &constantBufferData;

    device->CreateBuffer(&constantBufferDesc, &constantBufferInitData, &constantBuffer);
}

pickle::renderer::DirectXRenderer::~DirectXRenderer()
{
    swapChain->SetFullscreenState(FALSE, NULL);
    deviceContext->ClearState();

    constantBuffer->Release();
    vertexBuffer->Release();
    inputLayout->Release();
    vertexSharer->Release();
    pixelShader->Release();
    backBuffer->Release();
    swapChain->Release();
    device->Release();
    deviceContext->Release();
}

void pickle::renderer::DirectXRenderer::render() const
{
    float color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    deviceContext->ClearRenderTargetView(backBuffer, color);

    UINT stride = sizeof(float) * 9;
    UINT offset = 0;
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->Draw(36, 0);

    swapChain->Present(0, 0);
}