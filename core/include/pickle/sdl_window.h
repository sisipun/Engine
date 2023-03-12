#ifndef PICKLE_SDL_WINDOW
#define PICKLE_SDL_WINDOW

#include <pickle/window.h>

#include <SDL.h>

namespace pickle
{
    class SdlWindow : public Window
    {
    public:
        SdlWindow(int width, int height);
        ~SdlWindow() override;

        SdlWindow(const SdlWindow &window) = delete;
        SdlWindow &operator=(const SdlWindow &window) = delete;

        SDL_Window* getWindow() const;
        void update() override;

    private:
        SDL_Window *window;
    };
}

#endif