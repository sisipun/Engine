#include <pickle/opengl_renderer.h>

#include <glad/glad.h>

#include <pickle/logger.h>

pickle::renderer::OpenGLRenderer::OpenGLRenderer(SDL_Window *window)
{
    context = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        LOG_ERROR("Can't load glad module");
    }
}

pickle::renderer::OpenGLRenderer::~OpenGLRenderer()
{
    SDL_GL_DeleteContext(context);
}

void pickle::renderer::OpenGLRenderer::render() const
{
    LOG_DEBUG("OpenGL");
    LOG_INFO("OpenGL");
    LOG_WARNING("OpenGL");
    LOG_ERROR("OpenGL");
}