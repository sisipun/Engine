#include <iostream>

#include <glad/glad.h>
#include <stbimage/stb_image.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <SDL.h>

#include "shader.h"
#include "camera.h"
#include "model.h"

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
    Camera camera(glm::vec3(1.0, 0.0, 1.0f), glm::vec3(0.0f, 0.1f, 0.0f), 0.0f, -90.0f, 0.0f, 90.0f);
    Model ourModel("../donut/backpack.obj");
    // glm::vec3 lightPos = glm::vec3(1.0f, 2.0f, 1.0f);
    // glm::vec3 lightColor = glm::vec3(1.0f, 1.0f, 1.0f);

    shader.use();
    // shader.setVec3("lightColor", lightColor);
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
                }
            }
        }
        glClearColor(0, 0, 0, 1);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // glm::vec3 lightPos = glm::vec3(sin(SDL_GetTicks() / 1000.0f), 2.0f, cos(SDL_GetTicks() / 1000.0f));
        // shader.setVec3("lightPos", lightPos);
        // glm::vec3 cameraPos = camera.getPosition();
        // camera.setYaw(0.0f + (sin(SDL_GetTicks() / 10000.0f) * 360.0f));
        // camera.setPosition(glm::vec3(-3.0f + (sin(SDL_GetTicks() / 1000.0f) - 0.5f), cameraPos.y, cameraPos.z));

        glm::mat4 model = glm::mat4(1.0f);
        glm::mat4 view = camera.getViewMatrix();
        glm::mat4 projection = glm::perspective(glm::radians(camera.getFov()), float(SCREEN_WIDTH) / float(SCREEN_HEIGHT), 0.1f, 100.0f);

        shader.use();
        shader.setMat4("model", model);
        shader.setMat4("view", view);
        shader.setMat4("projection", projection);

        ourModel.draw(shader);

        SDL_GL_SwapWindow(window);
    }

    SDL_GL_DeleteContext(context);
    SDL_Quit();
    return 0;
}