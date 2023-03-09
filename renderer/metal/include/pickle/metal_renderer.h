#ifndef PICKLE_RENDERER_METAL
#define PICKLE_RENDERER_METAL

#include <pickle/renderer.h>

namespace pickle
{
    namespace renderer
    {
        class MetalRenderer : public Renderer
        {
        public:
            MetalRenderer(int width, int height);
            ~MetalRenderer() override;

            MetalRenderer(const MetalRenderer &renderer) = delete;
            MetalRenderer &operator=(const MetalRenderer &renderer) = delete;

            void render() const override;
        };
    }
}

#endif