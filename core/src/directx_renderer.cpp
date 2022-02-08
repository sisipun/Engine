#include <pickle/directx_renderer.h>

#include <iostream>

namespace pickle
{
    DirectXRenderer::DirectXRenderer()
    {
        std::cout << "Init DirectX" << std::endl;
    }

    DirectXRenderer::~DirectXRenderer()
    {
    }

    void DirectXRenderer::render() const
    {
        std::cout << "Render DirectX" << std::endl;
    }
}