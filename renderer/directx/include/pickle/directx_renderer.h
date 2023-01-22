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

            DirectXRenderer(const DirectXRenderer &renderer) = delete;
            DirectXRenderer &operator=(const DirectXRenderer &renderer) = delete;

            void render() const override;
        };
    }
}

#endif