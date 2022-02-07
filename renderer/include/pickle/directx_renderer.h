#ifndef PICKLE_DIRECTX_RENDERER
#define PICKLE_DIRECTX_RENDERER

#include "renderer.h"

namespace pickle
{
    namespace renderer
    {
        class DirectXRenderer : public Renderer
        {
        public:
            DirectXRenderer();

            void render() const override;
        };
    }
}

#endif