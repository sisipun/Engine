#include <iostream>
#include "engine/engine.h"

int main(int argc, char *argv[]) {
    Engine engine;
    if (!engine.init()) {
        printf("Failed to initialize!\n");
        return -1;
    }
    if (!engine.loadMedia()) {
        printf("Failed to load media!\n");
        return -1;
    }
    while (!engine.isQuit()) {
        engine.update();
        engine.handleInput();
    }
    engine.close();
    return 0;
}