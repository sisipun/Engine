#include <pickle/directx_renderer.h>

#include <xnamath.h>
#include <tchar.h>

#include <pickle/math.h>
#include <pickle/logger.h>

#include <iostream>

struct ConstantBuffer
{
    pickle::math::Matrix<4, 4, float> world;
    pickle::math::Matrix<4, 4, float> view;
    pickle::math::Matrix<4, 4, float> projection;
    pickle::math::Vector<4, float> lightDirection;
    pickle::math::Vector<4, float> cameraPosition;
};

pickle::renderer::DirectXRenderer::DirectXRenderer(HWND hWindow, int width, int height) : Renderer(width, height)
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

    ID3D11Texture2D *depthBufferTexture;
    D3D11_TEXTURE2D_DESC depthBufferTextureDesc;
    ZeroMemory(&depthBufferTextureDesc, sizeof(D3D11_TEXTURE2D_DESC));

    depthBufferTextureDesc.Width = width;
    depthBufferTextureDesc.Height = height;
    depthBufferTextureDesc.MipLevels = 1;
    depthBufferTextureDesc.ArraySize = 1;
    depthBufferTextureDesc.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
    depthBufferTextureDesc.SampleDesc.Count = 1;
    depthBufferTextureDesc.SampleDesc.Quality = 0;
    depthBufferTextureDesc.Usage = D3D11_USAGE_DEFAULT;
    depthBufferTextureDesc.BindFlags = D3D11_BIND_DEPTH_STENCIL;
    depthBufferTextureDesc.CPUAccessFlags = 0;
    depthBufferTextureDesc.MiscFlags = 0;
    device->CreateTexture2D(&depthBufferTextureDesc, NULL, &depthBufferTexture);

    D3D11_DEPTH_STENCIL_VIEW_DESC backBufferDesc;
    ZeroMemory(&backBufferDesc, sizeof(D3D11_DEPTH_STENCIL_VIEW_DESC));

    backBufferDesc.Format = depthBufferTextureDesc.Format;
    backBufferDesc.ViewDimension = D3D11_DSV_DIMENSION_TEXTURE2D;
    backBufferDesc.Texture2D.MipSlice = 0;

    device->CreateDepthStencilView(depthBufferTexture, &backBufferDesc, &depthBuffer);
    depthBufferTexture->Release();

    deviceContext->OMSetRenderTargets(1, &backBuffer, depthBuffer);

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

    D3D11_BUFFER_DESC constantBufferDesc;
    ZeroMemory(&constantBufferDesc, sizeof(D3D11_BUFFER_DESC));

    constantBufferDesc.Usage = D3D11_USAGE_DEFAULT;
    constantBufferDesc.ByteWidth = sizeof(ConstantBuffer);
    constantBufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
    constantBufferDesc.CPUAccessFlags = 0;

    device->CreateBuffer(&constantBufferDesc, NULL, &constantBuffer);
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
    depthBuffer->Release();
    backBuffer->Release();
    swapChain->Release();
    device->Release();
    deviceContext->Release();
}

void pickle::renderer::DirectXRenderer::render() const
{
    static int m = 0;
    float color[4] = {0.0f, 0.0f, 0.0f, 1.0f};
    deviceContext->ClearRenderTargetView(backBuffer, color);
    deviceContext->ClearDepthStencilView(depthBuffer, D3D11_CLEAR_DEPTH, 1.0f, 0);

    pickle::math::Vector<4, float> lightDirection = pickle::math::Vector<4, float>({1.0f, -1.0f, -1.0f, 0.0f});
    pickle::math::Vector<4, float> cameraPosition = pickle::math::Vector<4, float>({-1.0f, 1.0f, -1.0f, 0.0f});

    pickle::math::Matrix<4, 4, float> modelMatrix = pickle::math::Matrix<4, 4, float>({1.0f, 0.0f, 0.0f, 0.0f,
                                                                                       0.0f, 1.0f, 0.0f, 0.0f,
                                                                                       0.0f, 0.0f, 1.0f, 0.0f,
                                                                                       0.0f, 0.0f, 0.0f, 1.0f});
    pickle::math::Matrix<4, 4, float> viewMatix = pickle::math::lookAt(
        cameraPosition.cutDimension<3>(),
        pickle::math::Vector<3, float>({0.0f, 0.0f, 0.0f}),
        pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f}));
    pickle::math::Matrix<4, 4, float> projectionMatrix = pickle::math::perspective(
        pickle::math::radians(90.0f),
        width / (float)height,
        0.01f,
        100.0f);

    ConstantBuffer constantBufferData1{
        modelMatrix,
        viewMatix,
        projectionMatrix,
        lightDirection,
        cameraPosition};

    deviceContext->UpdateSubresource(constantBuffer, 0, NULL, &constantBufferData1, 0, 0);

    UINT stride = sizeof(float) * 9;
    UINT offset = 0;
    deviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
    deviceContext->VSSetConstantBuffers(0, 1, &constantBuffer);
    deviceContext->PSSetConstantBuffers(0, 1, &constantBuffer);
    deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
    deviceContext->Draw(36, 0);

    swapChain->Present(0, 0);
}