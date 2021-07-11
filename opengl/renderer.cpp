#include "renderer.h"

#include <iostream>

#include <glad/glad.h>
#include <stbimage/stb_image.h>

Renderer::Renderer(int screenWidth, int screeHeight) : screenWidth(screenWidth), screeHeight(screeHeight), shader(Shader("../shader.vert", "../shader.geom", "../shader.frag")), camera(Camera(glm::vec3(0.0, 3.0, 3.0f), glm::vec3(0.0f, 0.1f, 0.0f), float(screenWidth) / float(screeHeight), 100.0f, 0.0f, -90.0f, 0.0f, 90.0f)), light(Light(glm::vec3(0.0f, 3.0f, -3.0f), glm::vec3(0.2f), glm::vec3(1.0f), glm::vec3(1.0f)))
{
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        // Todo use logger
        std::cout << "Can't load SDL module" << std::endl;
    }

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screeHeight, SDL_WINDOW_OPENGL);
    if (window == nullptr)
    {
        // Todo use logger
        std::cout << "Can't create window" << std::endl;
    }

    context = SDL_GL_CreateContext(window);
    if (!gladLoadGLLoader((GLADloadproc)SDL_GL_GetProcAddress))
    {
        // Todo use logger
        std::cout << "Can't load glad module" << std::endl;
    }

    stbi_set_flip_vertically_on_load(true);
    glEnable(GL_DEPTH_TEST);

    shader.load();
}

Renderer::~Renderer()
{
    SDL_GL_DeleteContext(context);
    SDL_Quit();
}

void Renderer::draw(std::vector<Model> models) const
{
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    shader.use();
    camera.draw(shader);
    light.draw(shader);

    for (int i = 0; i < models.size(); i++)
    {
        models[i].draw(shader);
    }

    SDL_GL_SwapWindow(window);
}