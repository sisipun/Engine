#include <SDL.h>

#include "scene/examples/base_box_scene.h"
#include "scene/examples/monkey_scene.h"
#include "scene/examples/backpack_scene.h"
#include "renderer.h"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

int main(int argc, char *argv[])
{
    bool quit = false;

    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    BackpackScene scene = BackpackScene();

    SDL_Event event;
    while (!quit)
    {
        if (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            } else {
                scene.update(event);
            }
        }
        renderer.render(scene);
    }

    return 0;
}