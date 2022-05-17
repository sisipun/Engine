#ifndef PICKLE_WINDOW
#define PICKLE_WINDOW

#include <memory>
#include <pickle/renderer.h>

namespace pickle
{
    class Window
    {
    public:
        Window(int width, int height);
        ~Window();

        Window(const Window &window) = delete;
        Window &operator=(const Window &window) = delete;

        renderer::Renderer &getRenderer() const;
        bool isClosed() const;

    private:
        std::unique_ptr<renderer::Renderer> renderer;
    };
}

#endif
