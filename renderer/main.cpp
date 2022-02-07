#if defined(_WIN32)
#include <pickle/directx_renderer.h>
#endif

#include <pickle/opengl_renderer.h>

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return -1;
    }

    pickle::renderer::Renderer *renderer = nullptr;
    char *key = argv[1];

#if defined(_WIN32)
    if (strcmp(key, "-d") == 0)
    {
        renderer = new pickle::renderer::DirectXRenderer();
    }
#endif

    if (strcmp(key, "-o") == 0)
    {
        renderer = new pickle::renderer::OpenGLRenderer();
    }

    if (renderer == nullptr)
    {
        return -1;
    }

    renderer->render();
}