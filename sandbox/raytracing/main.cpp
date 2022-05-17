#include "geometry.h"
#include "raytracing.h"

int main(int argc, char *argv[])
{
    const int width = 800;
    const int height = 600;
    const int fov = M_PI / 2;

    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
    {
        return -1;
    }

    SDL_Window *window = SDL_CreateWindow("Engine", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height,
                                          SDL_WINDOW_SHOWN);
    if (window == nullptr)
    {
        return -1;
    }

    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (renderer == nullptr)
    {
        return -1;
    }

    SDL_Event *event = new SDL_Event();

    bool quit = false;
    Raytracing raycasting;

    std::vector<Sphere> spheres;
    spheres.push_back(Sphere(Vec3f(-3, 0, -16), 2));
    spheres.push_back(Sphere(Vec3f(-1.0, -1.5, -12), 2));
    spheres.push_back(Sphere(Vec3f(7, 5, -18), 4));

    while (!quit)
    {
        SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x00);
        SDL_RenderClear(renderer);
        raycasting.render(renderer, Vec3f(0, 0, 0), spheres, width, height, fov);
        SDL_RenderPresent(renderer);
        if (SDL_PollEvent(event) != 0)
        {
            if (event->type == SDL_QUIT)
            {
                quit = true;
            }
        }
    }
    return 0;
}