#include <memory>

#include <raytracing/sphere.h>
#include <raytracing/renderer.h>

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

    SDL_Renderer *sdlRenderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (sdlRenderer == nullptr)
    {
        return -1;
    }

    std::vector<std::unique_ptr<Shape> > shapes;
    shapes.push_back(std::make_unique<Sphere>(pickle::math::Vector<3, float>({0.0f, -1.0f, 3.0f}), 1.0f, Color{0xFF, 0x00, 0x00, 0xFF}));
    Renderer renderer(width, height);

    SDL_Event *event = new SDL_Event();

    bool quit = false;

    SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(sdlRenderer);

    // Render
    renderer.render(sdlRenderer, shapes);

    SDL_RenderPresent(sdlRenderer);

    while (!quit)
    {
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