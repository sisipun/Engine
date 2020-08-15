#include "mini_map.h"

void MiniMap::render(SDL_Renderer *renderer)
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (*(this->map + (i * height) + j) == 1)
            {
                SDL_Rect rect = {
                    static_cast<int>(body.x + i * body.width),
                    static_cast<int>(body.y + j * body.height),
                    static_cast<int>(body.width),
                    static_cast<int>(body.height)};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0xFF);
    SDL_Rect rect = {
        static_cast<int>(body.x + currentX * body.width),
        static_cast<int>(body.y + currentY * body.height),
        static_cast<int>(body.width),
        static_cast<int>(body.height)};
    SDL_RenderFillRect(renderer, &rect);
}