#ifndef PICKLE_RENDERER_DIRECTX
#define PICKLE_RENDERER_DIRECTX

#include <pickle/renderer.h>

namespace pickle
{
    namespace renderer
    {
        class DirectXRenderer : public Renderer
        {
        public:
            DirectXRenderer();

            ~DirectXRenderer() override;

            void render() const override;
        };
    }
}

#endif