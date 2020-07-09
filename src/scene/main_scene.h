#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include "../engine/scene/scene.h"

class MainScene : public Scene
{
public:
    MainScene() : Scene() {}

protected:
    void render(SDL_Renderer* renderer) override;

    void update(float delta) override;

    void handleInput(SDL_Event *event) override;
};

#endif