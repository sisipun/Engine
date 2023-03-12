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

        int getWidth() const;
        int getHeight() const;
        virtual void show();
        virtual void update() = 0;
        virtual bool isClosed() const;

    protected:
        int width;
        int height;
        bool closed = false;
    };
}

#endif
