#ifndef PICKLE_WIN32_WINDOW
#define PICKLE_WIN32_WINDOW

#include <pickle/window.h>

#include <windows.h>

namespace pickle
{
    class Win32Window : public Window
    {
    public:
        Win32Window(int width, int height);
        ~Win32Window() override;

        Win32Window(const Win32Window &window) = delete;
        Win32Window &operator=(const Win32Window &window) = delete;

        HWND getWindow() const;
        void show() override;
        void update() override;

    private:
        static const char *BASE_WINNDOW_CLASS;

        HWND hWindow;
    };
}

#endif