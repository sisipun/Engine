#include <picklerenderer/directx_renderer.h>
#include <picklerenderer/opengl_renderer.h>
#include <picklerenderer/vulkan_renderer.h>

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        return -1;
    }

    pickle::renderer::Renderer *renderer = nullptr;
    char *key = argv[1];
    if (strcmp(key, "-d") == 0)
    {
        renderer = new pickle::renderer::DirectXRenderer();
    }
    else if (strcmp(key, "-o") == 0)
    {
        renderer = new pickle::renderer::OpenGLRenderer();
    }
    else if (strcmp(key, "-v") == 0)
    {
        renderer = new pickle::renderer::VulkanRenderer();
    }

    if (renderer == nullptr)
    {
        return -1;
    }

    renderer->render();
}