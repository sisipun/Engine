#include <iostream>

#include <glad/glad.h>
#include <stbimage/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>

#include "shader.h"
#include "camera.h"
#include "model.h"
#include "light.h"

static const int SCREEN_WIDTH = 800;
static const int SCREEN_HEIGHT = 600;

int main(int argc, char *argv[])
{
    bool quit = false;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        return -1;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                                          SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        return -1;
    }

    SDL_GLContext context = SDL_GL_CreateContext(window);
    SDL_Event *event = new SDL_Event();

    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        return -1;
    }

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);

    Shader shader("../shader.vert", "../shader.frag");
    Camera camera(glm::vec3(0.0, 3.0, 3.0f), glm::vec3(0.0f, 0.1f, 0.0f), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 100.0f, 0.0f, -90.0f, 0.0f, 90.0f);
    Light light(glm::vec3(0.0f, 3.0f, -3.0f), glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f));
    // Model ourModel("../backpack/backpack.obj");
    Model ourModel("../donut/donut.obj");

    while (!quit)
    {
        if (SDL_PollEvent(event) != 0)
        {
            if (event->type == SDL_QUIT)
            {
                quit = true;
            }
            if (event->type == SDL_KEYDOWN)
            {
                glm::vec3 currPos = camera.getPosition();
                switch (event->key.keysym.sym)
                {
                case SDLK_RIGHT:
                    camera.setYaw(camera.getYaw() + 3.0f);
                    break;
                case SDLK_LEFT:
                    camera.setYaw(camera.getYaw() - 3.0f);
                    break;
                case SDLK_UP:
                    camera.setPitch(camera.getPitch() + 3.0f);
                    break;
                case SDLK_DOWN:
                    camera.setPitch(camera.getPitch() - 3.0f);
                    break;
                case SDLK_w:
                    currPos.z -= 0.2;
                    camera.setPosition(currPos);
                    break;
                case SDLK_s:
                    currPos.z += 0.2;
                    camera.setPosition(currPos);
                    break;
                case SDLK_a:
                    currPos.x -= 0.2;
                    camera.setPosition(currPos);
                    break;
                case SDLK_d:
                    currPos.x += 0.2;
                    camera.setPosition(currPos);
                    break;
                case SDLK_q:
                    currPos.y += 0.2;
                    camera.setPosition(currPos);
                    break;
                case SDLK_z:
                    currPos.y -= 0.2;
                    camera.setPosition(currPos);
                    break;
                }
            }
        }
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        shader.use();
        camera.draw(shader);
        light.draw(shader);
        ourModel.draw(shader);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}