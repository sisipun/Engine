#include <pickle/opengl_renderer.h>

#include <iostream>

#include <glad/glad.h>

namespace pickle
{
    namespace renderer
    {
        OpenGLRenderer::OpenGLRenderer()
        {
            if (SDL_Init(SDL_INIT_VIDEO) < 0)
            {
                // Todo use logger
                std::cout << "Can't load SDL module" << std::endl;
            }

            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
            SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

            SDL_Window *window = SDL_CreateWindow("OpenGL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_OPENGL);
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
        }

        OpenGLRenderer::~OpenGLRenderer()
        {
            SDL_GL_DeleteContext(context);
            SDL_Quit();
        }

        void OpenGLRenderer::render() const
        {
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
            std::cout << "Render OpenGL" << std::endl;
        }
    }
}