#include <pickle/window.h>

#include <pickle/opengl_renderer.h>

namespace pickle
{
    Window::Window(int width, int height)
    {
        renderer = std::make_unique<OpenGLRenderer>();
    }

    Window::~Window()
    {
    }
}