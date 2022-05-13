#include <SDL.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#include <pickle/color.h>
#include <pickle/model.h>
#include <pickle/texture.h>
#include <pickle/math.h>
#include <pickle/renderer.h>

#define SCREEN_WIDTH 600
#define SCREEN_HEIGHT 600

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
    pickle::renderer::Texture texture("../resources/diffuse.tga");

    pickle::math::Vector<3, float> ligthDir({0.0f, 0.0f, -1.0f});

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    for (int i = 0; i < model.getFacesCount(); i++)
    {
        pickle::math::Vector<9, int> face = model.getFace(i);
        pickle::math::Vector<3, float> vertex1 = model.getVertex(face.data[0]);
        pickle::math::Vector<3, float> textCoord1 = model.getTextureCoord(face.data[1]);
        pickle::math::Vector<3, float> vertex2 = model.getVertex(face.data[3]);
        pickle::math::Vector<3, float> textCoord2 = model.getTextureCoord(face.data[4]);
        pickle::math::Vector<3, float> vertex3 = model.getVertex(face.data[6]);
        pickle::math::Vector<3, float> textCoord3 = model.getTextureCoord(face.data[7]);

        pickle::math::Vector<3, float> norm = cross(vertex3 - vertex1, vertex2 - vertex1);
        norm = normalize(norm);
        float intensity = dot(norm, ligthDir);

        if (intensity > 0)
        {
            render.drawTriangle(
                vertex1,
                textCoord1,
                vertex2,
                textCoord2,
                vertex3,
                textCoord3,
                intensity,
                texture);
        }
    }

    render.present();
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