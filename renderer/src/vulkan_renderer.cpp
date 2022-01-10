#include <picklerenderer/vulkan_renderer.h>

#include <iostream>

namespace pickle
{
    namespace renderer
    {
        VulkanRenderer::VulkanRenderer()
        {
            std::cout << "Init Vulkan" << std::endl;
        }

        void VulkanRenderer::render() const
        {
            std::cout << "Render Vulkan" << std::endl;
        }
    }
}