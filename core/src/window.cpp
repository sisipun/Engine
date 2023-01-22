#include <pickle/window.h>

pickle::Window::Window(int width, int height) : width(width), height(height)
{
}

pickle::Window::~Window()
{
}

pickle::renderer::Renderer &pickle::Window::getRenderer() const
{
    return *renderer;
}