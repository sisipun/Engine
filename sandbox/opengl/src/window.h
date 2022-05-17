#ifndef WINDOW_H
#define WINDOW_H

#include <vector>

#include "renderer.h"

class Window
{
public:
    Window(int screenWidth, int screeHeight);
    Window(const Window &window) = delete;
    Window &operator=(const Window &window) = delete;
    ~Window();

    Renderer& getRenderer() const
    {
        return *renderer;
    }

    std::unique_ptr<Renderer> renderer;

private:
    int screenWidth;
    int screenHeight;
};

#endif