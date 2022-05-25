#include <memory>

#include <raytracing/sphere.h>
#include <raytracing/point_light.h>
#include <raytracing/direct_light.h>
#include <raytracing/ambient_light.h>
#include <raytracing/renderer.h>

int main(int argc, char *argv[])
{
    const int width = 600;
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
    shapes.push_back(std::make_unique<Sphere>(pickle::math::Vector<3, float>({0.0f, -1.0f, 3.0f}), 1.0f, Color{0xFF, 0x00, 0x00, 0xFF}, 500.0f, 0.2f));
    shapes.push_back(std::make_unique<Sphere>(pickle::math::Vector<3, float>({-2.0f, 0.0f, 4.0f}), 1.0f, Color{0x00, 0xFF, 0x00, 0xFF}, 10.0f, 0.3f));
    shapes.push_back(std::make_unique<Sphere>(pickle::math::Vector<3, float>({2.0f, 0.0f, 4.0f}), 1.0f, Color{0x00, 0x00, 0xFF, 0xFF}, 500.0f, 0.4f));
    shapes.push_back(std::make_unique<Sphere>(pickle::math::Vector<3, float>({0.0f, -5001.0f, 0.0f}), 5000.0f, Color{0xFF, 0xFF, 0x00, 0xFF}, 1000.0f, 0.5f));
    std::vector<std::unique_ptr<Light> > lights;
    lights.push_back(std::make_unique<AmbientLight>(0.2));
    lights.push_back(std::make_unique<PointLight>(0.6, pickle::math::Vector<3, float>({2.0, 1.0, 0.0})));
    lights.push_back(std::make_unique<DirectLight>(0.2, pickle::math::Vector<3, float>({-1.0, -4.0, -4.0})));

    Renderer renderer(width, height, {0x00, 0x00, 0x00, 0x00}, 3);
    renderer.setViewport(1.0f, 1.0f, 1.0f);

    SDL_Event *event = new SDL_Event();

    bool quit = false;

    SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(sdlRenderer);

    // Render
    renderer.render(sdlRenderer, shapes, lights);

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