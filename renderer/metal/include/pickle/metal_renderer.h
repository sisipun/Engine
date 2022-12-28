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
            MetalRenderer();

            ~MetalRenderer() override;

            void render() const override;
        };
    }
}

#endif