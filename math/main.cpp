#include <iostream>

#include "math_engine.h"

int main()
{
    using namespace pickle::math;
    Vector<2, float> v2First({1, 1});
    Vector<2, float> v2Cpy = v2First;
    Vector<2, float> v2Second({-1, 0});
    Vector<2, float> v2Sum = v2First + v2Second;
    Vector<2, float> v2Sub = v2First - v2Second;
    Vector<2, float> v2Mul = v2First * 3;
    Vector<2, float> v2Div = v2Second / 2.0;
    Vector<2, float> v2Ref = reflect(v2Second, Vector<2, float>({1, 1}));
    float v2Dot = dot(v2First, v2Second);
    Vector<2, float> v2Norm = normalize(v2First);

    std::cout << "Vector2 - Cpy: (" << v2Cpy.data[0] << "," << v2Cpy.data[1] << ")" << std::endl;
    std::cout << "Vector2 - Sum: (" << v2Sum.data[0] << "," << v2Sum.data[1] << ")" << std::endl;
    std::cout << "Vector2 - Sub: (" << v2Sub.data[0] << "," << v2Sub.data[1] << ")" << std::endl;
    std::cout << "Vector2 - Mul: (" << v2Mul.data[0] << "," << v2Mul.data[1] << ")" << std::endl;
    std::cout << "Vector2 - Div: (" << v2Div.data[0] << "," << v2Div.data[1] << ")" << std::endl;
    std::cout << "Vector2 - Ref: (" << v2Ref.data[0] << "," << v2Ref.data[1] << ")" << std::endl;
    std::cout << "Vector2 - Dot: (" << v2Dot << ")" << std::endl;
    std::cout << "Vector2 - Len: (" << length(v2First) << ")" << std::endl;
    std::cout << "Vector2 - Norm: (" << v2Norm.data[0] << "," << v2Norm.data[1] << ")" << std::endl;

    Vector<3, float> v3First({4, -2, 5});
    Vector<3, float> v3Cpy = v3First;
    Vector<3, float> v3Second({-1, -1, -1});
    Vector<3, float> v3Sum = v3First + v3Second;
    Vector<3, float> v3Sub = v3First - v3Second;
    Vector<3, float> v3Mul = v3First * 4;
    Vector<3, float> v3Div = v3Second / 5;
    Vector<3, float> v3Ref = reflect(v3Second, Vector<3, float>({1, 0, 0}));
    float v3Dot = dot(v3First, v3Second);
    Vector<3, float> v3Cross = cross(v3First, v3Second);
    Vector<3, float> v3Norm = normalize(v3First);

    std::cout << "Vector3 - Cpy: (" << v3Cpy.data[0] << "," << v3Cpy.data[1] << "," << v3Cpy.data[2] << ")" << std::endl;
    std::cout << "Vector3 - Sum: (" << v3Sum.data[0] << "," << v3Sum.data[1] << "," << v3Sum.data[2] << ")" << std::endl;
    std::cout << "Vector3 - Sub: (" << v3Sub.data[0] << "," << v3Sub.data[1] << "," << v3Sub.data[2] << ")" << std::endl;
    std::cout << "Vector3 - Mul: (" << v3Mul.data[0] << "," << v3Mul.data[1] << "," << v3Mul.data[2] << ")" << std::endl;
    std::cout << "Vector3 - Div: (" << v3Div.data[0] << "," << v3Div.data[1] << "," << v3Div.data[2] << ")" << std::endl;
    std::cout << "Vector3 - Ref: (" << v3Ref.data[0] << "," << v3Ref.data[1] << "," << v3Ref.data[2] << ")" << std::endl;
    std::cout << "Vector3 - Dot: (" << v3Dot << ")" << std::endl;
    std::cout << "Vector3 - Crs: (" << v3Cross.data[0] << "," << v3Cross.data[1] << "," << v3Cross.data[2] << ")" << std::endl;
    std::cout << "Vector3 - Len: (" << length(v3First) << ")" << std::endl;
    std::cout << "Vector3 - Norm: (" << v3Norm.data[0] << "," << v3Norm.data[1] << "," << v3Norm.data[2] << ")" << std::endl;

    Matrix<2, 2, float> matrixFirst({0.5f, 3.0f, 0.0f, -1.4f});
    Matrix<2, 2, float> matrixCpy = matrixFirst;
    Matrix<2, 2, float> matrixSecond({1.0f, 2.0f, 3.0f, 4.0f});
    Matrix<2, 2, float> matrixSum = matrixSecond + matrixFirst;
    Matrix<2, 2, float> matrixSub = matrixSecond - matrixFirst;
    Matrix<2, 2, float> matrixMul = matrixFirst * 2;
    Matrix<2, 2, float> matrixDiv = matrixSecond / 2;

    std::cout << "Matrix - Cpy: \n"
              << matrixCpy.data[0] << ", " << matrixCpy.data[1] << "\n"
              << matrixCpy.data[2] << ", " << matrixCpy.data[3] << "\n"
              << std::endl;
    std::cout << "Matrix - Sum: \n"
              << matrixSum.data[0] << ", " << matrixSum.data[1] << "\n"
              << matrixSum.data[2] << ", " << matrixSum.data[3] << "\n"
              << std::endl;
    std::cout << "Matrix - Sub: \n"
              << matrixSub.data[0] << ", " << matrixSub.data[1] << "\n"
              << matrixSub.data[2] << ", " << matrixSub.data[3] << "\n"
              << std::endl;
    std::cout << "Matrix - Mul: \n"
              << matrixMul.data[0] << ", " << matrixMul.data[1] << "\n"
              << matrixMul.data[2] << ", " << matrixMul.data[3] << "\n"
              << std::endl;
    std::cout << "Matrix - Div: \n"
              << matrixDiv.data[0] << ", " << matrixDiv.data[1] << "\n"
              << matrixDiv.data[2] << ", " << matrixDiv.data[3] << "\n"
              << std::endl;

    Matrix<3, 2, float> matrixMulFirst({2, 3, 2, 1, 5, 3});
    Matrix<2, 3, float> matrixMulSecond({5, 3, 2, 2, 1, 4});
    Matrix<3, 3, float> matrixMMul = matrixMulFirst * matrixMulSecond;

    std::cout << "Matrix - Mml: \n"
              << matrixMMul.data[0] << ", " << matrixMMul.data[1] << ", " << matrixMMul.data[2] << "\n"
              << matrixMMul.data[3] << ", " << matrixMMul.data[4] << ", " << matrixMMul.data[5] << "\n"
              << matrixMMul.data[6] << ", " << matrixMMul.data[7] << ", " << matrixMMul.data[8] << "\n"
              << std::endl;

    Matrix<3, 3, float> matrixIdn = identity<3, float>();
    std::cout << "Matrix - Idn: \n"
              << matrixIdn.data[0] << ", " << matrixIdn.data[1] << ", " << matrixIdn.data[2] << "\n"
              << matrixIdn.data[3] << ", " << matrixIdn.data[4] << ", " << matrixIdn.data[5] << "\n"
              << matrixIdn.data[6] << ", " << matrixIdn.data[7] << ", " << matrixIdn.data[8] << "\n"
              << std::endl;

    Matrix<3, 3, float> matrixIdMul = matrixMMul * matrixIdn;
    std::cout << "Matrix - Idn mul: \n"
              << matrixIdMul.data[0] << ", " << matrixIdMul.data[1] << ", " << matrixIdMul.data[2] << "\n"
              << matrixIdMul.data[3] << ", " << matrixIdMul.data[4] << ", " << matrixIdMul.data[5] << "\n"
              << matrixIdMul.data[6] << ", " << matrixIdMul.data[7] << ", " << matrixIdMul.data[8] << "\n"
              << std::endl;

    Matrix<3, 2, float> matrixTrn = transpose(Matrix<2, 3, float>({2, 1, 4, 3, 5, 1}));
    std::cout << "Matrix - Trn: \n"
              << matrixTrn.data[0] << ", " << matrixTrn.data[1] << "\n"
              << matrixTrn.data[2] << ", " << matrixTrn.data[3] << "\n"
              << matrixTrn.data[4] << ", " << matrixTrn.data[5] << "\n"
              << std::endl;

    Vector<3, float> matrixVecMul = Matrix<3, 2, float>({1, 2, 3, 4, 5, 6}) * Vector<2, float>({7, 8});
    std::cout << "Matrix - Vec mul: \n"
              << matrixVecMul.data[0] << ", " << matrixVecMul.data[1] << ", " << matrixVecMul.data[2] << "\n"
              << std::endl;

    Matrix<4, 4, float> matrixTst = translate(identity<4, float>(), Vector<3, float>({1, 2, 3}));
    std::cout << "Matrix - Tst: \n"
              << matrixTst.data[0] << ", " << matrixTst.data[1] << ", " << matrixTst.data[2] << ", " << matrixTst.data[3] << "\n"
              << matrixTst.data[4] << ", " << matrixTst.data[5] << ", " << matrixTst.data[6] << ", " << matrixTst.data[7] << "\n"
              << matrixTst.data[8] << ", " << matrixTst.data[9] << ", " << matrixTst.data[10] << ", " << matrixTst.data[11] << "\n"
              << matrixTst.data[12] << ", " << matrixTst.data[13] << ", " << matrixTst.data[14] << ", " << matrixTst.data[15] << "\n"
              << std::endl;

    Matrix<4, 4, float> matrixScl = scale(matrixTst, Vector<3, float>({2, 2, 2}));
    std::cout << "Matrix - Scl + tst: \n"
              << matrixScl.data[0] << ", " << matrixScl.data[1] << ", " << matrixScl.data[2] << ", " << matrixScl.data[3] << "\n"
              << matrixScl.data[4] << ", " << matrixScl.data[5] << ", " << matrixScl.data[6] << ", " << matrixScl.data[7] << "\n"
              << matrixScl.data[8] << ", " << matrixScl.data[9] << ", " << matrixScl.data[10] << ", " << matrixScl.data[11] << "\n"
              << matrixScl.data[12] << ", " << matrixScl.data[13] << ", " << matrixScl.data[14] << ", " << matrixScl.data[15] << "\n"
              << std::endl;

    Vector<4, float> posVector = Vector<4, float>({4, 3, 2, 1});
    Vector<4, float> transformedVector = matrixScl * posVector;
    std::cout << "Transformed vector: \n"
              << transformedVector.data[0] << ", " << transformedVector.data[1] << ", " << transformedVector.data[2] << ", " << transformedVector.data[3] << "\n"
              << std::endl;

    Matrix<4, 4, float> matrixDet = Matrix<4, 4, float>({24, 20, 3, 40, 15, 3, 5, 11, 21, 24, 1, -8, 5, -3, 16, -10});
    float det = determinant(matrixDet);
    std::cout << "Matrix det: " << det << std::endl;
}