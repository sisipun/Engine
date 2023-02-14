#include <pickle/application.h>

#include <pickle/win32_window.h>

namespace pickle
{
    Application::Application()
    {
        window = std::make_unique<pickle::Win32Window>(2048, 1080);
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
            getWindow().update();
            getWindow().getRenderer().render();
        }
    }
}