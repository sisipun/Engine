#include <iostream>

#include "vector/vector2.h"
#include "vector/vector3.h"

int main()
{
    using namespace pickle::math;
    Vector<2> v2First(1, 1);
    Vector<2> v2Second(-1, 0);
    Vector<2> v2Sum = v2First + v2Second;
    Vector<2> v2Sub = v2First - v2Second;
    Vector<2> v2Mul = v2First * 3;
    Vector<2> v2Div = v2Second / 2.0;
    Vector<2> v2Ref = v2Second.reflect(Vector<2>(1, 1));
    float v2Dot = v2First.dot(v2Second);

    std::cout << "Vector2 - Sum: (" << v2Sum.x << "," << v2Sum.y << ")" << std::endl;
    std::cout << "Vector2 - Sub: (" << v2Sub.x << "," << v2Sub.y << ")" << std::endl;
    std::cout << "Vector2 - Mul: (" << v2Mul.x << "," << v2Mul.y << ")" << std::endl;
    std::cout << "Vector2 - Div: (" << v2Div.x << "," << v2Div.y << ")" << std::endl;
    std::cout << "Vector2 - Ref: (" << v2Ref.x << "," << v2Ref.y << ")" << std::endl;
    std::cout << "Vector2 - Dot: (" << v2Dot << ")" << std::endl;
    std::cout << "Vector2 - Len: (" << v2First.length() << ")" << std::endl;

    v2First.normalize();
    std::cout << "Vector2 - Norm: (" << v2First.x << "," << v2First.y << ")" << std::endl;

    Vector<3> v3First(4, -2, 5);
    Vector<3> v3Second(-1, -1, -1);
    Vector<3> v3Sum = v3First + v3Second;
    Vector<3> v3Sub = v3First - v3Second;
    Vector<3> v3Mul = v3First * 4;
    Vector<3> v3Div = v3Second / 5;
    Vector<3> v3Ref = v3Second.reflect(Vector<3>(1, 0, 0));
    float v3Dot = v3First.dot(v3Second);
    Vector<3> v3Cross = v3First.cross(v3Second);

    std::cout << "Vector3 - Sum: (" << v3Sum.x << "," << v3Sum.y << "," << v3Sum.z << ")" << std::endl;
    std::cout << "Vector3 - Sub: (" << v3Sub.x << "," << v3Sub.y << "," << v3Sub.z << ")" << std::endl;
    std::cout << "Vector3 - Mul: (" << v3Mul.x << "," << v3Mul.y << "," << v3Mul.z << ")" << std::endl;
    std::cout << "Vector3 - Div: (" << v3Div.x << "," << v3Div.y << "," << v3Div.z << ")" << std::endl;
    std::cout << "Vector3 - Ref: (" << v3Ref.x << "," << v3Ref.y << "," << v3Ref.z << ")" << std::endl;
    std::cout << "Vector3 - Dot: (" << v3Dot << ")" << std::endl;
    std::cout << "Vector3 - Crs: (" << v3Cross.x << "," << v3Cross.y << "," << v3Cross.z << ")" << std::endl;
    std::cout << "Vector3 - Len: (" << v3First.length() << ")" << std::endl;

    v3First.normalize();
    std::cout << "Vector3 - Norm: (" << v3First.x << "," << v3First.y << "," << v3First.z << ")" << std::endl;
}