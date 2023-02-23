#ifndef PICKLE_RENDERER_DIRECTX
#define PICKLE_RENDERER_DIRECTX

#include <pickle/renderer.h>

#include <windows.h>
#include <d3d11.h>
#include <d3dx11.h>

namespace pickle
{
    namespace renderer
    {
        class DirectXRenderer : public Renderer
        {
        public:
            DirectXRenderer(HWND hWnd, int width, int height);
            ~DirectXRenderer() override;

            DirectXRenderer(const DirectXRenderer &renderer) = delete;
            DirectXRenderer &operator=(const DirectXRenderer &renderer) = delete;

            void render() const override;

        private:
            ID3D11Device *device;
            ID3D11DeviceContext *deviceContext;
            IDXGISwapChain *swapChain;
            ID3D11RenderTargetView *backBuffer;
            ID3D11VertexShader *vertexSharer;
            ID3D11PixelShader *pixelShader;
            ID3D11InputLayout *inputLayout;
            ID3D11Buffer *vertexBuffer;
        };
    }
}

#endif