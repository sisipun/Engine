#include <pickle/application.h>

#ifdef _WIN32
    #include <pickle/win32_window.h>
#endif
#include <pickle/sdl_window.h>
#include <pickle/opengl_renderer.h>
#ifdef __APPLE__
#include <pickle/metal_renderer.h>
#endif
#ifdef _WIN32
    #include <pickle/directx_renderer.h>
#endif

pickle::Application::Application(pickle::renderer::RendererType type)
{
    float width = 2048;
    float height = 1080;

    switch (type)
    {
#ifdef _WIN32
    case pickle::renderer::RendererType::DIRECT_X:
        window = std::make_unique<pickle::Win32Window>(width, height);
        renderer = std::make_unique<pickle::renderer::DirectXRenderer>(static_cast<pickle::Win32Window *>(window.get())->getWindow(), window->getWidth(), window->getHeight());
        break;
#endif
    case pickle::renderer::RendererType::OPEN_GL:
        window = std::make_unique<pickle::SdlWindow>(width, height);
        renderer = std::make_unique<pickle::renderer::OpenGLRenderer>(static_cast<pickle::SdlWindow *>(window.get())->getWindow(), window->getWidth(), window->getHeight());
        break;
#ifdef __APPLE__        
    case pickle::renderer::RendererType::METAL:
        window = std::make_unique<pickle::SdlWindow>(width, height);
        renderer = std::make_unique<pickle::renderer::MetalRenderer>(window->getWidth(), window->getHeight());
        break;
#endif        
    }
}

pickle::Application::~Application()
{
}

pickle::Window &pickle::Application::getWindow() const
{
    return *window;
}

pickle::renderer::Renderer &pickle::Application::getRenderer() const
{
    return *renderer;
}

void pickle::Application::start()
{
    getWindow().show();
    while (!getWindow().isClosed())
    {
        getWindow().update();
        getRenderer().render();
    }
}