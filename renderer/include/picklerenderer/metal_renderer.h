#ifndef PICKLE_METAL_RENDERER
#define PICKLE_METAL_RENDERER

#include "renderer.h"

namespace pickle
{
    namespace renderer
    {
        class MetalRenderer : public Renderer
        {
        public:
            MetalRenderer();

            void render() const override;
        };
    }
}

#endif