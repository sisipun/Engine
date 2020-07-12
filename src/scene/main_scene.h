#ifndef MAIN_SCENE_H
#define MAIN_SCENE_H

#include "../engine/scene/scene.h"
#include "../actor/hero.h"

class MainScene : public Scene
{
public:
    MainScene() : Scene(), hero(nullptr) {}

protected:
    bool init(Storage *storage) override;

    void render(SDL_Renderer *renderer) override;

    void update(float delta) override;

    void handleInput(SDL_Event *event) override;

private:
    Actor *hero;
};

#endif