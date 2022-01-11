#include <picklerenderer/metal_renderer.h>

#include <iostream>

namespace pickle
{
    namespace renderer
    {
        MetalRenderer::MetalRenderer()
        {
            std::cout << "Init Metal" << std::endl;
        }

        void MetalRenderer::render() const
        {
            std::cout << "Render Metal" << std::endl;
        }
    }
}