#ifndef PICKLE_RENDERER_H
#define PICKLE_RENDERER_H

#include <SDL.h>

#include <pickle/math.h>
#include <array>

#include "color.h"
#include "texture.h"

namespace pickle
{
    namespace renderer
    {
        class Renderer
        {
        public:
            Renderer(SDL_Renderer *renderer, int width, int height);

            ~Renderer();

            void drawPoint(math::Vector<3, float> p, Color color);

            void drawTriangle(math::Vector<3, float> p1, math::Vector<3, float> p2, math::Vector<3, float> p3, Color color);

            void drawTriangle(
                math::Vector<3, float> p1,
                math::Vector<3, float> tc1,
                math::Vector<3, float> p2,
                math::Vector<3, float> tc2,
                math::Vector<3, float> p3,
                math::Vector<3, float> tc3,
                float intensity,
                const Texture &texture);

            void present();

        private:
            SDL_Renderer *renderer;
            int width;
            int height;
            int depth;
            Color *buffer;
            int *zBuffer;
        };
    }
}

#endif