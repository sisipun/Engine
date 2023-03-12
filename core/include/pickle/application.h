#ifndef PICKLE_APPLICATION
#define PICKLE_APPLICATION

#include <pickle/window.h>

namespace pickle
{
    class Application
    {
    public:
        Application(renderer::RendererType type);
        ~Application();

        Application(const Application &application) = delete;
        Application &operator=(const Application &application) = delete;

        Window &getWindow() const;
        renderer::Renderer &getRenderer() const;
        void start();

    private:
        std::unique_ptr<Window> window;
        std::unique_ptr<renderer::Renderer> renderer;
    };
}

#endif
