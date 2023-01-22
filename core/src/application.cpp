#include <pickle/application.h>

#include <pickle/sdl_window.h>

namespace pickle
{
    Application::Application()
    {
        window = std::make_unique<pickle::SdlWindow>(800, 600);
    }

    Application::~Application()
    {
    }

    Window &Application::getWindow() const
    {
        return *window;
    }

    void Application::start()
    {
        while (!getWindow().isClosed())
        {
            getWindow().getRenderer().render();
        }
    }
}