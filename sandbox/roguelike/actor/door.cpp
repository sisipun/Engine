#include "door.h"

void Door::renderActor(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0x00, 0xFF);
    SDL_Rect rect = {
        static_cast<int>(body.x),
        static_cast<int>(body.y),
        static_cast<int>(body.width),
        static_cast<int>(body.height)};
    SDL_RenderFillRect(renderer, &rect);
}