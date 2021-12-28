#include <iostream>

#include "vector/vector2.h"
#include "vector/vector3.h"
#include "matrix/matrix.h"

int main()
{
    using namespace pickle::math;
    Vector<2> v2First(1, 1);
    Vector<2> v2Cpy = v2First;
    Vector<2> v2Second(-1, 0);
    Vector<2> v2Sum = v2First + v2Second;
    Vector<2> v2Sub = v2First - v2Second;
    Vector<2> v2Mul = v2First * 3;
    Vector<2> v2Div = v2Second / 2.0;
    Vector<2> v2Ref = v2Second.reflect(Vector<2>(1, 1));
    float v2Dot = v2First.dot(v2Second);
    v2First.normalize();

    std::cout << "Vector2 - Cpy: (" << v2Cpy.x << "," << v2Cpy.y << ")" << std::endl;
    std::cout << "Vector2 - Sum: (" << v2Sum.x << "," << v2Sum.y << ")" << std::endl;
    std::cout << "Vector2 - Sub: (" << v2Sub.x << "," << v2Sub.y << ")" << std::endl;
    std::cout << "Vector2 - Mul: (" << v2Mul.x << "," << v2Mul.y << ")" << std::endl;
    std::cout << "Vector2 - Div: (" << v2Div.x << "," << v2Div.y << ")" << std::endl;
    std::cout << "Vector2 - Ref: (" << v2Ref.x << "," << v2Ref.y << ")" << std::endl;
    std::cout << "Vector2 - Dot: (" << v2Dot << ")" << std::endl;
    std::cout << "Vector2 - Len: (" << v2First.length() << ")" << std::endl;
    std::cout << "Vector2 - Norm: (" << v2First.x << "," << v2First.y << ")" << std::endl;

    Vector<3> v3First(4, -2, 5);
    Vector<3> v3Cpy = v3First;
    Vector<3> v3Second(-1, -1, -1);
    Vector<3> v3Sum = v3First + v3Second;
    Vector<3> v3Sub = v3First - v3Second;
    Vector<3> v3Mul = v3First * 4;
    Vector<3> v3Div = v3Second / 5;
    Vector<3> v3Ref = v3Second.reflect(Vector<3>(1, 0, 0));
    float v3Dot = v3First.dot(v3Second);
    Vector<3> v3Cross = v3First.cross(v3Second);
    v3First.normalize();

    std::cout << "Vector3 - Cpy: (" << v3Cpy.x << "," << v3Cpy.y << "," << v3Cpy.z << ")" << std::endl;
    std::cout << "Vector3 - Sum: (" << v3Sum.x << "," << v3Sum.y << "," << v3Sum.z << ")" << std::endl;
    std::cout << "Vector3 - Sub: (" << v3Sub.x << "," << v3Sub.y << "," << v3Sub.z << ")" << std::endl;
    std::cout << "Vector3 - Mul: (" << v3Mul.x << "," << v3Mul.y << "," << v3Mul.z << ")" << std::endl;
    std::cout << "Vector3 - Div: (" << v3Div.x << "," << v3Div.y << "," << v3Div.z << ")" << std::endl;
    std::cout << "Vector3 - Ref: (" << v3Ref.x << "," << v3Ref.y << "," << v3Ref.z << ")" << std::endl;
    std::cout << "Vector3 - Dot: (" << v3Dot << ")" << std::endl;
    std::cout << "Vector3 - Crs: (" << v3Cross.x << "," << v3Cross.y << "," << v3Cross.z << ")" << std::endl;
    std::cout << "Vector3 - Len: (" << v3First.length() << ")" << std::endl;
    std::cout << "Vector3 - Norm: (" << v3First.x << "," << v3First.y << "," << v3First.z << ")" << std::endl;

    Matrix<2, 2> matrixFirst({0.5f, 3.0f, 0.0f, -1.4f});
    Matrix<2, 2> matrixCpy = matrixFirst;
    Matrix<2, 2> matrixSecond({1.0f, 2.0f, 3.0f, 4.0f});
    Matrix<2, 2> matrixSum = matrixSecond + matrixFirst;
    Matrix<2, 2> matrixSub = matrixSecond - matrixFirst;
    Matrix<2, 2> matrixMul = matrixFirst * 2;
    Matrix<2, 2> matrixDiv = matrixSecond / 2;

    std::cout << "Matrix - Cpy: \n" << matrixCpy.data[0] << ", " << matrixCpy.data[1] << "\n" << matrixCpy.data[2] << ", " << matrixCpy.data[3] << "\n" << std::endl;
    std::cout << "Matrix - Sum: \n" << matrixSum.data[0] << ", " << matrixSum.data[1] << "\n" << matrixSum.data[2] << ", " << matrixSum.data[3] << "\n" << std::endl;
    std::cout << "Matrix - Sub: \n" << matrixSub.data[0] << ", " << matrixSub.data[1] << "\n" << matrixSub.data[2] << ", " << matrixSub.data[3] << "\n" << std::endl;
    std::cout << "Matrix - Mul: \n" << matrixMul.data[0] << ", " << matrixMul.data[1] << "\n" << matrixMul.data[2] << ", " << matrixMul.data[3] << "\n" << std::endl;
    std::cout << "Matrix - Div: \n" << matrixDiv.data[0] << ", " << matrixDiv.data[1] << "\n" << matrixDiv.data[2] << ", " << matrixDiv.data[3] << "\n" << std::endl;
}