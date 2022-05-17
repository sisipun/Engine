#ifndef PICKLE_RENDERER_OPENGL
#define PICKLE_RENDERER_OPENGL

#include "renderer.h"

#include <SDL.h>

namespace pickle
{
    namespace renderer
    {
        class OpenGLRenderer : public Renderer
        {
        public:
            OpenGLRenderer(SDL_Window *window);

            ~OpenGLRenderer() override;

            void render() const override;

        private:
            SDL_GLContext context;
        };
    }
}

#endif