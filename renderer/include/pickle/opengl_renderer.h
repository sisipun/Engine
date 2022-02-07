#ifndef PICKLE_OPENGL_RENDERER
#define PICKLE_OPENGL_RENDERER

#include "renderer.h"

#include <SDL.h>

namespace pickle
{
    class OpenGLRenderer : public Renderer
    {
    public:
        OpenGLRenderer();

        ~OpenGLRenderer();

        void render() const override;

    private:
        SDL_GLContext context;
    };
}

#endif