#include <pickle/window.h>

pickle::Window::Window(int width, int height) : width(width), height(height)
{
}

pickle::Window::~Window()
{
}

int pickle::Window::getWidth() const
{
    return width;
}

int pickle::Window::getHeight() const
{
    return height;
}

bool pickle::Window::isClosed() const
{
    return closed;
}

void pickle::Window::show()
{
}