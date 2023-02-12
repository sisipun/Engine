#ifndef PICKLE_WINDOW
#define PICKLE_WINDOW

#include <pickle/renderer.h>

#include <memory>

namespace pickle
{
    class Window
    {
    public:
        Window(int width, int height);
        virtual ~Window();

        Window(const Window &window) = delete;
        Window &operator=(const Window &window) = delete;

        virtual void update() = 0;
        renderer::Renderer &getRenderer() const;
        virtual bool isClosed() const;

    protected:
        int width;
        int height;
        std::unique_ptr<renderer::Renderer> renderer;
        bool closed = false;
    };
}

#endif
