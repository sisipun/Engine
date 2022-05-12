#ifndef PICKLE_RENDERER_H
#define PICKLE_RENDERER_H

#include <SDL.h>

#include <pickle/math.h>

#include "color.h"

namespace pickle
{
    namespace renderer
    {
        class Renderer
        {
        public:
            Renderer(SDL_Renderer *renderer, float width, float height);

            void drawPoint(float x, float y, Color color);

            void drawLine(float x1, float y1, float x2, float y2, Color color);

            void drawTriangle(math::Vector<3, float> p1, math::Vector<3, float> p2, math::Vector<3, float> p3, Color color);

        private:
            SDL_Renderer *renderer;
            float width;
            float height;
        };
    }
}

#endif