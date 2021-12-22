#include <iostream>

#include "vector/vector2.h"
#include "vector/vector3.h"

int main()
{
    using namespace pickle::math;
    Vector2 v2First(1, 1);
    Vector2 v2Second(2, 2);
    Vector2 v2Sum = v2First + v2Second;
    Vector2 v2Sub = v2First - v2Second;
    Vector2 v2Mul = v2First * 3;
    Vector2 v2Div = v2Second / 2.0;
    
    std::cout << "Vector2 - Sum: (" << v2Sum.x << "," << v2Sum.y << ")" << std::endl;
    std::cout << "Vector2 - Sub: (" << v2Sub.x << "," << v2Sub.y << ")" << std::endl;
    std::cout << "Vector2 - Mul: (" << v2Mul.x << "," << v2Mul.y << ")" << std::endl;
    std::cout << "Vector2 - Div: (" << v2Div.x << "," << v2Div.y << ")" << std::endl;
    std::cout << "Vector2 - Len: (" << v2First.length() << ")" << std::endl;

    v2First.normalize();
    std::cout << "Vector2 - Norm: (" << v2First.x << "," << v2First.y << ")" << std::endl;

    Vector3 v3First(2, 2, 3);
    Vector3 v3Second(5, 10, 3);
    Vector3 v3Sum = v3First + v3Second;
    Vector3 v3Sub = v3First - v3Second;
    Vector3 v3Mul = v3First * 4;
    Vector3 v3Div = v3Second / 5;
    
    std::cout << "Vector3 - Sum: (" << v3Sum.x << "," << v3Sum.y << "," << v3Sum.z << ")" << std::endl;
    std::cout << "Vector3 - Sub: (" << v3Sub.x << "," << v3Sub.y << "," << v3Sub.z << ")" << std::endl;
    std::cout << "Vector3 - Mul: (" << v3Mul.x << "," << v3Mul.y << "," << v3Mul.z << ")" << std::endl;
    std::cout << "Vector3 - Div: (" << v3Div.x << "," << v3Div.y << "," << v3Div.z << ")" << std::endl;
    std::cout << "Vector3 - Len: (" << v3First.length() << ")" << std::endl;

    v3First.normalize();
    std::cout << "Vector3 - Norm: (" << v3First.x << "," << v3First.y << "," << v3First.z << ")" << std::endl;
}