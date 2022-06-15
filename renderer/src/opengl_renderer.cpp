#include <pickle/opengl_renderer.h>

#include <glad/glad.h>

#include <pickle/logger.h>

pickle::renderer::OpenGLRenderer::OpenGLRenderer(SDL_Window *window)
{
    context = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        Logger::log("Can't load glad module");
    }
}

pickle::renderer::OpenGLRenderer::~OpenGLRenderer()
{
    SDL_GL_DeleteContext(context);
}

void pickle::renderer::OpenGLRenderer::render() const
{
    Logger::log("Render OpenGL");
}