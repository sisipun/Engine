#ifndef PICKLE_VULKAN_RENDERER
#define PICKLE_VULKAN_RENDERER

#include "renderer.h"

namespace pickle
{
    namespace renderer
    {
        class VulkanRenderer : public Renderer
        {
        public:
            VulkanRenderer();

            void render() const override;
        };
    }
}

#endif