#include <SDL.h>

#include <pickle/math.h>

#include <rasterization/renderer.h>
#include <rasterization/camera.h>
#include <rasterization/model.h>
#include <rasterization/model_instance.h>

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

    Camera camera(pickle::math::Vector<3, float>({0.0f, 0.0f, 0.0f}), pickle::math::Vector<3, float>({0.0f, 0.0f, 1.0f}));
    Renderer renderer(width, height, 1.0f, 1.0f, 1.0f, 10.0f, camera, pickle::math::Vector<3, float>({0.0f, -1.0f, 1.0f}));

    SDL_SetRenderDrawColor(sdlRenderer, 0x00, 0x00, 0x00, 0x00);
    SDL_RenderClear(sdlRenderer);

    // Render
    std::vector<pickle::math::Vector<6, float>> vertices;
    vertices.push_back(pickle::math::Vector<6, float>({1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, 1.0f, 1.0f, 1.0f, 0.0f, 0.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 0.0f}));

    vertices.push_back(pickle::math::Vector<6, float>({1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 0.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({1.0f, -1.0f, -1.0f, 0.0f, 1.0f, 0.0f}));

    vertices.push_back(pickle::math::Vector<6, float>({1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({1.0f, 1.0f, 1.0f, 0.0f, 0.0f, 1.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({1.0f, -1.0f, 1.0f, 0.0f, 0.0f, 1.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({1.0f, -1.0f, -1.0f, 0.0f, 0.0f, 1.0f}));

    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, 1.0f, 1.0f, 1.0f, 1.0f, 0.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, 1.0f, -1.0f, 1.0f, 1.0f, 0.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, -1.0f, -1.0f, 1.0f, 1.0f, 0.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, -1.0f, 1.0f, 1.0f, 1.0f, 0.0f}));

    vertices.push_back(pickle::math::Vector<6, float>({1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, 1.0f, -1.0f, 0.0f, 1.0f, 1.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({1.0f, 1.0f, 1.0f, 0.0f, 1.0f, 1.0f}));

    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({-1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({1.0f, -1.0f, -1.0f, 1.0f, 0.0f, 1.0f}));
    vertices.push_back(pickle::math::Vector<6, float>({1.0f, -1.0f, 1.0f, 1.0f, 0.0f, 1.0f}));

    std::vector<pickle::math::Vector<3, int>> triangles;
    triangles.push_back(pickle::math::Vector<3, int>({0, 1, 2}));
    triangles.push_back(pickle::math::Vector<3, int>({0, 2, 3}));

    triangles.push_back(pickle::math::Vector<3, int>({5, 4, 7}));
    triangles.push_back(pickle::math::Vector<3, int>({5, 7, 6}));

    triangles.push_back(pickle::math::Vector<3, int>({8, 9, 10}));
    triangles.push_back(pickle::math::Vector<3, int>({8, 10, 11}));

    triangles.push_back(pickle::math::Vector<3, int>({12, 13, 14}));
    triangles.push_back(pickle::math::Vector<3, int>({12, 14, 15}));

    triangles.push_back(pickle::math::Vector<3, int>({16, 17, 18}));
    triangles.push_back(pickle::math::Vector<3, int>({16, 18, 19}));

    triangles.push_back(pickle::math::Vector<3, int>({20, 21, 22}));
    triangles.push_back(pickle::math::Vector<3, int>({20, 22, 23}));

    Model box{vertices, triangles};

    pickle::math::Matrix<4, 4, float> transformBox1 = pickle::math::translate(
        pickle::math::identity<4, float>(),
        pickle::math::Vector<3, float>({-1.5f, 0.0f, 4.0f}));

    pickle::math::Matrix<4, 4, float> transformBox2 = pickle::math::rotate(
        pickle::math::translate(
            pickle::math::identity<4, float>(),
            pickle::math::Vector<3, float>({1.25f, 2.0f, 4.5f})),
        pickle::math::radians(195.0f),
        pickle::math::Vector<3, float>({0.0f, 1.0f, 0.0f}));

    ModelInstance box1{box, transformBox1};
    ModelInstance box2{box, transformBox2};
    renderer.drawModelInstance(box1);
    renderer.drawModelInstance(box2);

    renderer.present(sdlRenderer);

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