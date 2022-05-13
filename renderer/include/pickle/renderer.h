#ifndef PICKLE_RENDERER_H
#define PICKLE_RENDERER_H

#include <SDL.h>

#include <pickle/math.h>
#include <array>

#include "color.h"

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

            void drawLine(float x1, float y1, float x2, float y2, Color color);

            void drawTriangle(math::Vector<3, float> p1, math::Vector<3, float> p2, math::Vector<3, float> p3, Color color);

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