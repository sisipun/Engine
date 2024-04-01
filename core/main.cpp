#include <pickle/application.h>

#include <string>

#include <pickle/renderer.h>

int main(int argc, char *argv[])
{
    pickle::renderer::RendererType rendererType = pickle::renderer::RendererType::OPEN_GL;
    for (int i = 1; i < argc; i++)
    {
        const char *key = argv[i];
        if (i + 1 < argc && (strcmp(key, "-r") == 0 || strcmp(key, "--renderer") == 0))
        {
            const char *value = argv[i + 1];
            if (strcmp(value, "o") == 0 || strcmp(value, "opengl") == 0)
            {
                rendererType = pickle::renderer::RendererType::OPEN_GL;
            }
#ifdef __APPLE__
            else if (strcmp(value, "m") == 0 || strcmp(value, "metal") == 0)
            {
                rendererType = pickle::renderer::RendererType::METAL;
            }
#endif
#ifdef _WIN32
            else if (strcmp(value, "d") == 0 || strcmp(value, "directx") == 0)
            {
                rendererType = pickle::renderer::RendererType::DIRECT_X;
            }
#endif
        }
    }

    pickle::Application(rendererType).start();
}