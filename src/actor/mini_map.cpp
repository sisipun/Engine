#include "mini_map.h"

void MiniMap::renderActor(SDL_Renderer *renderer)
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

bool MiniMap::moveLeft()
{
    if (currentX - 1 >= 0 && *(this->map + ((currentX - 1) * height) + currentY) == 0)
    {
        currentX--;
        return true;
    }

    return false;
}

bool MiniMap::moveRight()
{
    if (currentX + 1 < width && *(this->map + ((currentX + 1) * height) + currentY) == 0)
    {
        currentX++;
        return true;
    }

    return false;
}

bool MiniMap::moveUp()
{
    if (currentY - 1 >= 0 && *(this->map + (currentX * height) + currentY - 1) == 0)
    {
        currentY--;
        return true;
    }

    return false;
}

bool MiniMap::moveDown()
{
    if (currentY + 1 < height && *(this->map + (currentX * height) + currentY + 1) == 0)
    {
        currentY++;
        return true;
    }

    return false;
}

void MiniMap::handleActorEvent(Event event)
{
    if (event.getType() == "heroUp")
    {
        moveUp();
    }
    else if (event.getType() == "heroDown")
    {
        moveDown();
    }
    else if (event.getType() == "heroLeft")
    {
        moveLeft();
    }
    else if (event.getType() == "heroRight")
    {
        moveRight();
    }
}