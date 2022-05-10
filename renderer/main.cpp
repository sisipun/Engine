#include <SDL.h>

#include <fstream>
#include <iostream>
#include <sstream>
#include <cmath>

#include "model.h"

#define SCREEN_WIDTH 600.0f
#define SCREEN_HEIGHT 600.0f

void drawLine(SDL_Renderer *renderer, float x1, float y1, float x2, float y2, bool horizontalFlip = true)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);

    int screenX1 = static_cast<int>((x1 + 1) / 2 * SCREEN_WIDTH);
    int screenX2 = static_cast<int>((x2 + 1) / 2 * SCREEN_WIDTH);
    int screenY1 = static_cast<int>((y1 + 1) / 2 * SCREEN_HEIGHT);
    int screenY2 = static_cast<int>((y2 + 1) / 2 * SCREEN_HEIGHT);

    if (horizontalFlip)
    {
        screenY1 = SCREEN_HEIGHT - screenY1;
        screenY2 = SCREEN_HEIGHT - screenY2;
    }

    bool steep = false;
    if (std::abs(screenX2 - screenX1) < std::abs(screenY2 - screenY1))
    {
        std::swap(screenX1, screenY1);
        std::swap(screenX2, screenY2);
        steep = true;
    }

    if (screenX1 > screenX2)
    {
        std::swap(screenX1, screenX2);
        std::swap(screenY1, screenY2);
    }

    int dx = std::abs(screenX2 - screenX1);
    int dy = std::abs(screenY2 - screenY1);
    int derror = dy;
    int error = 0;
    int directionY = screenY2 > screenY1 ? 1 : -1;

    int y = screenY1;
    for (int x = screenX1; x <= screenX2; x++)
    {
        error += derror;

        if (error > dx)
        {
            y += directionY;
            error -= dx;
        }

        int finX = x;
        int finY = y;
        if (steep)
        {
            std::swap(finX, finY);
        }

        SDL_Rect rect = {finX, finY, 1, 1};
        SDL_RenderFillRect(renderer, &rect);
    }
}

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

    Model model("../resources/head.obj");

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(renderer);
    for (int i = 0; i < model.getFacesCount(); i++)
    {
        std::vector<int> face = model.getFace(i);
        for (int j = 0; j < 3; j++)
        {
            std::vector<float> vertex1 = model.getVertex(face[j]);
            std::vector<float> vertex2 = model.getVertex(face[(j + 1) % 3]);
            drawLine(renderer, vertex1[0], vertex1[1], vertex2[0], vertex2[1]);
        }
    }

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