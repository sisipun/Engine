#include "collision.h"

bool checkCollision(Body first, Body second) {
    int leftFirst, leftSecond;
    int rightFirst, rightSecond;
    int topFirst, topSecond;
    int bottomFirst, bottomSecond;

    leftFirst = first.x;
    rightFirst = first.x + first.width;
    topFirst = first.y;
    bottomFirst = first.y + first.height;

    leftSecond = second.x;
    rightSecond = second.x + second.width;
    topSecond = second.y;
    bottomSecond = second.y + second.height;

    if (bottomFirst <= topSecond) { return false; }
    if (topFirst >= bottomSecond) { return false; }
    if (rightFirst <= leftSecond) { return false; }
    if (leftFirst >= rightSecond) { return false; }

    return true;
}