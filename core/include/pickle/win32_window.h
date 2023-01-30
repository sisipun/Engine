#ifndef PICKLE_SDL_WINDOW
#define PICKLE_SDL_WINDOW

#include <windows.h>

#include <pickle/window.h>

namespace pickle
{
    class Win32Window : public Window
    {
    public:
        Win32Window(int width, int height);
        ~Win32Window() override;

        Win32Window(const Win32Window &window) = delete;
        Win32Window &operator=(const Win32Window &window) = delete;

        void update() override;
    };
}

#endif