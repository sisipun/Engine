#include <picklerenderer/opengl_renderer.h>

#include <iostream>

namespace pickle
{
    namespace renderer
    {
        OpenGLRenderer::OpenGLRenderer()
        {
            std::cout << "Init OpenGL" << std::endl;
        }

        void OpenGLRenderer::render() const
        {
            std::cout << "Render OpenGL" << std::endl;
        }
    }
}