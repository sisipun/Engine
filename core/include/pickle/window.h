#ifndef PICKLE_WINDOW
#define PICKLE_WINDOW

#include "renderer.h"

#include <memory>

namespace pickle
{
    class Window
    {
    public:
        Window(int width, int height);
        ~Window();

        Window(const Window &window) = delete;
        Window &operator=(const Window &window) = delete;

        Renderer &getRenderer() const;
        bool isClosed() const;

    private:
        std::unique_ptr<Renderer> renderer;
    };
}

#endif
