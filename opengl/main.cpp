#include <iostream>

#include <SDL.h>

#include "model.h"
#include "renderer.h"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

int main(int argc, char *argv[])
{
    bool quit = false;

    
    SDL_Event *event = new SDL_Event();
    Renderer renderer(SCREEN_WIDTH, SCREEN_HEIGHT);
    std::vector<Model> models;
    Model ourModel("../backpack/backpack.obj");
    models.push_back(ourModel);
    // Model ourModel("../donut/donut.obj");

    while (!quit)
    {
        if (SDL_PollEvent(event) != 0)
        {
            if (event->type == SDL_QUIT)
            {
                quit = true;
            }
            // if (event->type == SDL_KEYDOWN)
            // {
            //     glm::vec3 currPos = camera.getPosition();
            //     switch (event->key.keysym.sym)
            //     {
            //     case SDLK_RIGHT:
            //         camera.setYaw(camera.getYaw() + 3.0f);
            //         break;
            //     case SDLK_LEFT:
            //         camera.setYaw(camera.getYaw() - 3.0f);
            //         break;
            //     case SDLK_UP:
            //         camera.setPitch(camera.getPitch() + 3.0f);
            //         break;
            //     case SDLK_DOWN:
            //         camera.setPitch(camera.getPitch() - 3.0f);
            //         break;
            //     case SDLK_w:
            //         currPos.z -= 0.2;
            //         camera.setPosition(currPos);
            //         break;
            //     case SDLK_s:
            //         currPos.z += 0.2;
            //         camera.setPosition(currPos);
            //         break;
            //     case SDLK_a:
            //         currPos.x -= 0.2;
            //         camera.setPosition(currPos);
            //         break;
            //     case SDLK_d:
            //         currPos.x += 0.2;
            //         camera.setPosition(currPos);
            //         break;
            //     case SDLK_q:
            //         currPos.y += 0.2;
            //         camera.setPosition(currPos);
            //         break;
            //     case SDLK_z:
            //         currPos.y -= 0.2;
            //         camera.setPosition(currPos);
            //         break;
            //     }
            // }
        }

        renderer.draw(models);
    }

    return 0;
}