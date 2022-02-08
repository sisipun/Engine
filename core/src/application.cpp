#include <pickle/application.h>

namespace pickle
{
    Application::Application() : window(800, 600)
    {
    }

    Application::~Application()
    {
    }

    void Application::start()
    {
        while (!window.isClosed())
        {
            window.getRenderer().render();
        }
    }
}