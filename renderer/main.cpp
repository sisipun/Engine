#include <SDL.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#include <pickle/color.h>
#include <pickle/model.h>
#include <pickle/math.h>
#include <pickle/renderer.h>

#define SCREEN_WIDTH 600.0f
#define SCREEN_HEIGHT 600.0f

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        std::cout << "Can't load SDL module" << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_Window *window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        std::cout << "Can't create window" << std::endl;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        std::cout << "Renderer could not be created" << std::endl;
    }

    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    pickle::renderer::Renderer render(renderer, SCREEN_WIDTH, SCREEN_HEIGHT);
    pickle::renderer::Model model("../resources/head.obj");

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    // for (int i = 0; i < model.getFacesCount(); i++)
    // {
    //     pickle::math::Vector<3, int> face = model.getFace(i);
    //     for (int j = 0; j < 3; j++)
    //     {
    //         pickle::math::Vector<3, float> vertex1 = model.getVertex(face.data[j]);
    //         pickle::math::Vector<3, float> vertex2 = model.getVertex(face.data[(j + 1) % 3]);
    //         render.drawLine(vertex1.data[0], vertex1.data[1], vertex2.data[0], vertex2.data[1], {1.0, 1.0, 0.0, 1.0});
    //     }
    // }

    render.drawTriangle(
        pickle::math::Vector<2, float>({-0.9, -0.3}),
        pickle::math::Vector<2, float>({-0.5, 0.6}),
        pickle::math::Vector<2, float>({-0.3, -0.2}),
        {static_cast<float>(rand()) / static_cast<float>(RAND_MAX), static_cast<float>(rand()) / static_cast<float>(RAND_MAX), static_cast<float>(rand()) / static_cast<float>(RAND_MAX), 1.0});
    render.drawTriangle(
        pickle::math::Vector<2, float>({0.8, -0.5}),
        pickle::math::Vector<2, float>({0.5, -1.0}),
        pickle::math::Vector<2, float>({-0.3, 0.8}),
        {static_cast<float>(rand()) / static_cast<float>(RAND_MAX), static_cast<float>(rand()) / static_cast<float>(RAND_MAX), static_cast<float>(rand()) / static_cast<float>(RAND_MAX), 1.0});
    render.drawTriangle(
        pickle::math::Vector<2, float>({0.8, 0.5}),
        pickle::math::Vector<2, float>({0.2, 0.6}),
        pickle::math::Vector<2, float>({0.3, 0.8}),
        {static_cast<float>(rand()) / static_cast<float>(RAND_MAX), static_cast<float>(rand()) / static_cast<float>(RAND_MAX), static_cast<float>(rand()) / static_cast<float>(RAND_MAX), 1.0});

    SDL_RenderPresent(renderer);

    bool quit = false;
    SDL_Event event;
    while (!quit)
    {
        if (SDL_PollEvent(&event) != 0)
        {
            if (event.type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}