#if defined(_WIN32)
#include <picklerenderer/directx_renderer.h>
#endif

#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__)
#include <picklerenderer/opengl_renderer.h>
#endif

#if defined(_WIN32) || defined(__linux__)
#include <picklerenderer/vulkan_renderer.h>
#endif

#if defined(__APPLE__)
#include <picklerenderer/metal_renderer.h>
#endif

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

#if defined(_WIN32) || defined(__APPLE__) || defined(__linux__)
    if (strcmp(key, "-o") == 0)
    {
        renderer = new pickle::renderer::OpenGLRenderer();
    }
#endif

#if defined(_WIN32) || defined(__linux__)
    if (strcmp(key, "-v") == 0)
    {
        renderer = new pickle::renderer::VulkanRenderer();
    }
#endif

#if defined(__APPLE__)
    if (strcmp(key, "-m") == 0)
    {
        renderer = new pickle::renderer::MetalRenderer();
    }
#endif

    if (renderer == nullptr)
    {
        return -1;
    }

    renderer->render();
}