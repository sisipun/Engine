#include <pickle/opengl_renderer.h>

#include <iostream>

#include <glad/glad.h>

namespace pickle
{
    OpenGLRenderer::OpenGLRenderer(SDL_Window *window)
    {
        context = SDL_GL_CreateContext(window);
        if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
        {
            // Todo use logger
            std::cout << "Can't load glad module" << std::endl;
        }
    }

    OpenGLRenderer::~OpenGLRenderer()
    {
        SDL_GL_DeleteContext(context);
    }

    void OpenGLRenderer::render() const
    {
        // Todo use logger
        std::cout << "Render OpenGL" << std::endl;
    }
}