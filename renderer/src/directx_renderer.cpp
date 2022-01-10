#include <picklerenderer/directx_renderer.h>

#include <iostream>

namespace pickle
{
    namespace renderer
    {
        DirectXRenderer::DirectXRenderer()
        {
            std::cout << "Init DirectX" << std::endl;
        }

        void DirectXRenderer::render() const
        {
            std::cout << "Render DirectX" << std::endl;
        }
    }
}