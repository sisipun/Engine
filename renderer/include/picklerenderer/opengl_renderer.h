#ifndef PICKLE_OPENGL_RENDERER
#define PICKLE_OPENGL_RENDERER

#include "renderer.h"

namespace pickle
{
    namespace renderer
    {
        class OpenGLRenderer : public Renderer
        {
        public:
            OpenGLRenderer();

            void render() const override;
        };
    }
}

#endif