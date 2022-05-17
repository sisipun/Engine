#include "mini_map.h"
#include "../utils/constants.h"
#include "door.h"

void MiniMap::renderActor(SDL_Renderer *renderer) const
{
    SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0x55);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (*(map + (i * height) + j) == 1)
            {
                SDL_Rect rect = {
                    static_cast<int>(body.x + (i + 1) * body.width),
                    static_cast<int>(body.y + (j + 1) * body.height),
                    static_cast<int>(body.width),
                    static_cast<int>(body.height)};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0x00, 0x00, 0x00, 0x55);
    for (int i = 0; i < width; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (*(map + (i * height) + j) == 0)
            {
                SDL_Rect rect = {
                    static_cast<int>(body.x + (i + 1) * body.width),
                    static_cast<int>(body.y + (j + 1) * body.height),
                    static_cast<int>(body.width),
                    static_cast<int>(body.height)};
                SDL_RenderFillRect(renderer, &rect);
            }
        }
    }

    SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x55);
    SDL_Rect rect = {
        static_cast<int>(body.x + (currentX + 1) * body.width),
        static_cast<int>(body.y + (currentY + 1) * body.height),
        static_cast<int>(body.width),
        static_cast<int>(body.height)};
    SDL_RenderFillRect(renderer, &rect);

    SDL_SetRenderDrawColor(renderer, 0x66, 0x66, 0x66, 0x66);
    SDL_Rect left = {
        static_cast<int>(body.x),
        static_cast<int>(body.y),
        static_cast<int>(body.width),
        static_cast<int>((height + 2) * body.height)};
    SDL_RenderFillRect(renderer, &left);
    SDL_Rect right = {
        static_cast<int>(body.x + ((body.width + 1) * width)),
        static_cast<int>(body.y),
        static_cast<int>(body.width),
        static_cast<int>((height + 2) * body.height)};
    SDL_RenderFillRect(renderer, &right);
    SDL_Rect top = {
        static_cast<int>(body.x),
        static_cast<int>(body.y),
        static_cast<int>((width + 2) * body.width),
        static_cast<int>(body.height)};
    SDL_RenderFillRect(renderer, &top);
    SDL_Rect bottom = {
        static_cast<int>(body.x),
        static_cast<int>(body.y + ((body.height + 1) * height)),
        static_cast<int>((width + 2) * body.width),
        static_cast<int>(body.height)};
    SDL_RenderFillRect(renderer, &bottom);
}

bool MiniMap::moveLeft()
{
    if (currentX - 1 >= 0 && *(map + ((currentX - 1) * height) + currentY) == 0)
    {
        currentX--;
        return true;
    }

    return false;
}

bool MiniMap::moveRight()
{
    if (currentX + 1 < width && *(map + ((currentX + 1) * height) + currentY) == 0)
    {
        currentX++;
        return true;
    }

    return false;
}

bool MiniMap::moveUp()
{
    if (currentY - 1 >= 0 && *(map + (currentX * height) + currentY - 1) == 0)
    {
        currentY--;
        return true;
    }

    return false;
}

bool MiniMap::moveDown()
{
    if (currentY + 1 < height && *(map + (currentX * height) + currentY + 1) == 0)
    {
        currentY++;
        return true;
    }

    return false;
}

void addDoor(Context *context, std::string name, Body body, std::vector<std::string> tags)
{
    Actor *door = context->getActor(name);
    if (door == nullptr)
    {
        context->storeActor(new Door(name, body, tags));
    }
}

void removeDoor(Context *context, std::string name)
{
    context->deleteActor(name);
}

void MiniMap::handleActorEvent(Event event)
{
    bool mapMoved = false;
    if (event.getType() == "heroUp")
    {
        moveUp();
        mapMoved = true;
    }
    else if (event.getType() == "heroDown")
    {
        moveDown();
        mapMoved = true;
    }
    else if (event.getType() == "heroLeft")
    {
        moveLeft();
        mapMoved = true;
    }
    else if (event.getType() == "heroRight")
    {
        moveRight();
        mapMoved = true;
    }

    if (mapMoved)
    {
        if (currentY - 1 >= 0 && *(map + (currentX * height) + currentY - 1) == 0)
        {
            addDoor(context, "northDoor", {(SCREEN_WIDTH / 2) - (DOOR_WIDTH / 2), 0, DOOR_WIDTH, DOOR_HEIGHT}, {"door", "north"});
        }
        else
        {
            removeDoor(context, "northDoor");
        }
        if (currentY + 1 < height && *(map + (currentX * height) + currentY + 1) == 0)
        {
            addDoor(context, "southDoor", {(SCREEN_WIDTH / 2) - (DOOR_WIDTH / 2), SCREEN_HEIGHT - DOOR_HEIGHT, DOOR_WIDTH, DOOR_HEIGHT}, {"door", "south"});
        }
        else
        {
            removeDoor(context, "southDoor");
        }
        if (currentX - 1 >= 0 && *(map + ((currentX - 1) * height) + currentY) == 0)
        {
            addDoor(context, "westDoor", {0, (SCREEN_HEIGHT / 2) - (DOOR_WIDTH / 2), DOOR_HEIGHT, DOOR_WIDTH}, {"door", "west"});
        }
        else
        {
            removeDoor(context, "westDoor");
        }
        if (currentX + 1 < width && *(map + ((currentX + 1) * height) + currentY) == 0)
        {
            addDoor(context, "eastDoor", {SCREEN_WIDTH - DOOR_HEIGHT, (SCREEN_HEIGHT / 2) - (DOOR_WIDTH / 2), DOOR_HEIGHT, DOOR_WIDTH}, {"door", "east"});
        }
        else
        {
            removeDoor(context, "eastDoor");
        }
    }
}