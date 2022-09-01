#include <SDL.h>

#include <pickle/math.h>

#include <rasterization/renderer.h>

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

    SDL_Event *event = new SDL_Event();

    bool quit = false;

    Renderer renderer(width, height, 1.0f, 1.0f, 1.0f);

    SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(sdlRenderer);

    // Render
    pickle::math::Vector<6, float> va = pickle::math::Vector({-2.0f, -0.5f, 5.0f, 1.0f, 0.0f, 0.0f});
    pickle::math::Vector<6, float> vb = pickle::math::Vector({-2.0f, 0.5f, 5.0f, 0.0f, 1.0f, 0.0f});
    pickle::math::Vector<6, float> vc = pickle::math::Vector({-1.0f, 0.5f, 5.0f, 0.0f, 0.0f, 1.0f});
    pickle::math::Vector<6, float> vd = pickle::math::Vector({-1.0f, -0.5f, 5.0f, 1.0f, 1.0f, 1.0f});

    pickle::math::Vector<6, float> vab = pickle::math::Vector({-2.0f, -0.5f, 6.0f, 0.0f, 1.0f, 1.0f});
    pickle::math::Vector<6, float> vbb = pickle::math::Vector({-2.0f, 0.5f, 6.0f, 1.0f, 0.0f, 1.0f});
    pickle::math::Vector<6, float> vcb = pickle::math::Vector({-1.0f, 0.5f, 6.0f, 1.0f, 1.0f, 0.0f});
    pickle::math::Vector<6, float> vdb = pickle::math::Vector({-1.0f, -0.5f, 6.0f, 0.5f, 0.5f, 0.5f});

    renderer.drawLine(sdlRenderer, renderer.projectVertex(va), renderer.projectVertex(vb));
    renderer.drawLine(sdlRenderer, renderer.projectVertex(vb), renderer.projectVertex(vc));
    renderer.drawLine(sdlRenderer, renderer.projectVertex(vc), renderer.projectVertex(vd));
    renderer.drawLine(sdlRenderer, renderer.projectVertex(vd), renderer.projectVertex(va));

    renderer.drawLine(sdlRenderer, renderer.projectVertex(vab), renderer.projectVertex(vbb));
    renderer.drawLine(sdlRenderer, renderer.projectVertex(vbb), renderer.projectVertex(vcb));
    renderer.drawLine(sdlRenderer, renderer.projectVertex(vcb), renderer.projectVertex(vdb));
    renderer.drawLine(sdlRenderer, renderer.projectVertex(vdb), renderer.projectVertex(vab));

    renderer.drawLine(sdlRenderer, renderer.projectVertex(va), renderer.projectVertex(vab));
    renderer.drawLine(sdlRenderer, renderer.projectVertex(vb), renderer.projectVertex(vbb));
    renderer.drawLine(sdlRenderer, renderer.projectVertex(vc), renderer.projectVertex(vcb));
    renderer.drawLine(sdlRenderer, renderer.projectVertex(vd), renderer.projectVertex(vdb));

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