#ifndef PICKLE_SDL_WINDOW
#define PICKLE_SDL_WINDOW

#include <pickle/window.h>

namespace pickle
{
    class SdlWindow : public Window
    {
    public:
        SdlWindow(int width, int height);
        ~SdlWindow() override;

        SdlWindow(const SdlWindow &window) = delete;
        SdlWindow &operator=(const SdlWindow &window) = delete;

        bool isClosed() const override;
    };
}

#endif