#define CATCH_CONFIG_MAIN

#include <iostream>

#include <catch2/catch.hpp>
#include <picklemath/math_engine.h>

using namespace pickle::math;

TEST_CASE("Vector Copy", "[vector]")
{
    Vector<2, float> vector({1, 1});
    Vector<2, float> copy = vector;
    REQUIRE(copy.data[0] == 1);
    REQUIRE(copy.data[1] == 1);
}

TEST_CASE("Vector Sum", "[vector]")
{
    Vector<2, float> sum = Vector<2, float>({1, 1}) + Vector<2, float>({-1, 0});
    REQUIRE(sum.data[0] == 0.0f);
    REQUIRE(sum.data[1] == 1.0f);
}

TEST_CASE("Vector Sub", "[vector]")
{
    Vector<3, float> sub = Vector<3, float>({1, 1, 2}) - Vector<3, float>({-1, 0, 4});
    REQUIRE(sub.data[0] == 2.0f);
    REQUIRE(sub.data[1] == 1.0f);
    REQUIRE(sub.data[2] == -2.0f);
}

TEST_CASE("Vector Scalar Mul", "[vector]")
{
    Vector<2, int> mul = Vector<2, int>({2, 4}) * 3;
    REQUIRE(mul.data[0] == 6);
    REQUIRE(mul.data[1] == 12);
}

TEST_CASE("Vector Scalar Div", "[vector]")
{
    Vector<3, float> div = Vector<3, float>({5, -3, 2}) / 2;
    REQUIRE(div.data[0] == 2.5f);
    REQUIRE(div.data[1] == -1.5f);
    REQUIRE(div.data[2] == 1.0f);
}

TEST_CASE("Vector Length", "[vector]")
{
    float len = length(Vector<3, float>({3, 4, 0}));
    REQUIRE(len == 5.0f);
}

TEST_CASE("Vector Normalization", "[vector]")
{
    Vector<3, float> normalized = normalize(Vector<3, float>({8, 0, 6}));
    REQUIRE(normalized.data[0] == 0.8f);
    REQUIRE(normalized.data[1] == 0.0f);
    REQUIRE(normalized.data[2] == 0.6f);
}

TEST_CASE("Vector Dot", "[vector]")
{
    float dotProduct = dot(Vector<3, float>({2, -1, 3}), Vector<3, float>({1, 2, -1}));
    REQUIRE(dotProduct == -3.0f);
}

TEST_CASE("Vector Cross", "[vector]")
{
    Vector<3, float> crossProduct = cross(Vector<3, float>({1, 0, 0}), Vector<3, float>({0, 1, 0}));
    REQUIRE(crossProduct.data[0] == 0.0f);
    REQUIRE(crossProduct.data[1] == 0.0f);
    REQUIRE(crossProduct.data[2] == 1.0f);
}

TEST_CASE("Vector Reflect", "[vector]")
{
    Vector<3, int> ref = reflect(Vector<3, int>({-1, -1, -1}), Vector<3, int>({1, 0, 0}));
    REQUIRE(ref.data[0] == 1);
    REQUIRE(ref.data[1] == -1);
    REQUIRE(ref.data[2] == -1);
}

TEST_CASE("Matrix Copy", "[matrix]")
{
    Matrix<2, 3, int> matrix({1, 2, -3, 1, -2, 4});
    Matrix<2, 3, int> copy = matrix;
    REQUIRE(copy.data[0] == 1);
    REQUIRE(copy.data[1] == 2);
    REQUIRE(copy.data[2] == -3);
    REQUIRE(copy.data[3] == 1);
    REQUIRE(copy.data[4] == -2);
    REQUIRE(copy.data[5] == 4);
}

TEST_CASE("Matrix Sum", "[matrix]")
{
    Matrix<2, 3, int> sum = Matrix<2, 3, int>({1, 2, -3, 1, -2, 4}) + Matrix<2, 3, int>({2, 1, 2, -1, 4, 5});
    REQUIRE(sum.data[0] == 3);
    REQUIRE(sum.data[1] == 3);
    REQUIRE(sum.data[2] == -1);
    REQUIRE(sum.data[3] == 0);
    REQUIRE(sum.data[4] == 2);
    REQUIRE(sum.data[5] == 9);
}

TEST_CASE("Matrix Sub", "[matrix]")
{
    Matrix<2, 3, float> sub = Matrix<2, 3, float>({1, 2, -3, 1, -2, 4}) - Matrix<2, 3, float>({2, 1, 2, -1, 4, 5});
    REQUIRE(sub.data[0] == -1.0f);
    REQUIRE(sub.data[1] == 1.0f);
    REQUIRE(sub.data[2] == -5.0f);
    REQUIRE(sub.data[3] == 2.0f);
    REQUIRE(sub.data[4] == -6.0f);
    REQUIRE(sub.data[5] == -1.0f);
}

TEST_CASE("Matrix Scalar Mul", "[matrix]")
{
    Matrix<2, 2, float> mul = Matrix<2, 2, float>({1, -1, 2, -1}) * 3;
    REQUIRE(mul.data[0] == 3.0f);
    REQUIRE(mul.data[1] == -3.0f);
    REQUIRE(mul.data[2] == 6.0f);
    REQUIRE(mul.data[3] == -3.0f);
}

TEST_CASE("Matrix Scalar Div", "[matrix]")
{
    Matrix<3, 3, float> div = Matrix<3, 3, float>({1, -1.2, 2, -1, 4, 2, 1, -5.2, 2.2}) / 2;
    REQUIRE(div.data[0] == 0.5f);
    REQUIRE(div.data[1] == -0.6f);
    REQUIRE(div.data[2] == 1.0f);
    REQUIRE(div.data[3] == -0.5f);
    REQUIRE(div.data[4] == 2.0f);
    REQUIRE(div.data[5] == 1.0f);
    REQUIRE(div.data[6] == 0.5f);
    REQUIRE(div.data[7] == -2.6f);
    REQUIRE(div.data[8] == 1.1f);
}

TEST_CASE("Matrix Mul", "[matrix]")
{
    Matrix<3, 3, float> mul = Matrix<3, 2, float>({2, 3, 2, 1, 5, 3}) * Matrix<2, 3, float>({5, 3, 2, 2, 1, 4});
    REQUIRE(mul.data[0] == 16.0f);
    REQUIRE(mul.data[1] == 9.0f);
    REQUIRE(mul.data[2] == 16.0f);
    REQUIRE(mul.data[3] == 12.0f);
    REQUIRE(mul.data[4] == 7.0f);
    REQUIRE(mul.data[5] == 8.0f);
    REQUIRE(mul.data[6] == 31.0f);
    REQUIRE(mul.data[7] == 18.0f);
    REQUIRE(mul.data[8] == 22.0f);
}

TEST_CASE("Matrix Identity", "[matrix]")
{
    Matrix<3, 3, float> idn = identity<3, float>();
    REQUIRE(idn.data[0] == 1.0f);
    REQUIRE(idn.data[1] == 0.0f);
    REQUIRE(idn.data[2] == 0.0f);
    REQUIRE(idn.data[3] == 0.0f);
    REQUIRE(idn.data[4] == 1.0f);
    REQUIRE(idn.data[5] == 0.0f);
    REQUIRE(idn.data[6] == 0.0f);
    REQUIRE(idn.data[7] == 0.0f);
    REQUIRE(idn.data[8] == 1.0f);
}

TEST_CASE("Matrix Identity Mul", "[matrix]")
{
    Matrix<3, 3, float> mul = Matrix<3, 3, float>({2, 3, -2, 1, 5.3, -3, 4, 5, 8.1}) * identity<3, float>();
    REQUIRE(mul.data[0] == 2.0f);
    REQUIRE(mul.data[1] == 3.0f);
    REQUIRE(mul.data[2] == -2.0f);
    REQUIRE(mul.data[3] == 1.0f);
    REQUIRE(mul.data[4] == 5.3f);
    REQUIRE(mul.data[5] == -3.0f);
    REQUIRE(mul.data[6] == 4.0f);
    REQUIRE(mul.data[7] == 5.0f);
    REQUIRE(mul.data[8] == 8.1f);
}

TEST_CASE("Matrix Transpose", "[matrix]")
{
    Matrix<2, 3, float> trn = transpose(Matrix<3, 2, float>({2, 3, 2, 1, 5, 3}));
    REQUIRE(trn.data[0] == 2.0f);
    REQUIRE(trn.data[1] == 2.0f);
    REQUIRE(trn.data[2] == 5.0f);
    REQUIRE(trn.data[3] == 3.0f);
    REQUIRE(trn.data[4] == 1.0f);
    REQUIRE(trn.data[5] == 3.0f);
}

TEST_CASE("Matrix Determinant", "[matrix]")
{
    float det = determinant(Matrix<4, 4, float>({24, 20, 3, 40, 15, 3, 5, 11, 21, 24, 1, -8, 5, -3, 16, -10}));
    REQUIRE(det == -155145.0f);
}

TEST_CASE("Matrix Inverse", "[matrix]")
{
    Matrix<3, 3, float> inv = inverse(Matrix<3, 3, float>({3, 0, 2, 2, 0, -2, 0, 1, 1}));
    REQUIRE(inv.data[0] == 0.2f);
    REQUIRE(inv.data[1] == 0.2f);
    REQUIRE(inv.data[2] == 0.0f);
    REQUIRE(inv.data[3] == -0.2f);
    REQUIRE(inv.data[4] == 0.3f);
    REQUIRE(inv.data[5] == 1.0f);
    REQUIRE(inv.data[6] == 0.2f);
    REQUIRE(inv.data[7] == -0.3f);
    REQUIRE(inv.data[8] == 0.0f);
}

TEST_CASE("Matrix Inverse Mul", "[matrix]")
{
    Matrix<3, 3, float> invBase = Matrix<3, 3, float>({3, 0, 2, 2, 0, -2, 0, 1, 1});
    Matrix<3, 3, float> inv = inverse(invBase);
    Matrix<3, 3, float> mul = inv * invBase;
    REQUIRE(mul.data[0] == 1.0f);
    REQUIRE(mul.data[1] == 0.0f);
    REQUIRE(mul.data[2] == 0.0f);
    REQUIRE(mul.data[3] == 0.0f);
    REQUIRE(mul.data[4] == 1.0f);
    REQUIRE(mul.data[5] == 0.0f);
    REQUIRE(mul.data[6] == 0.0f);
    REQUIRE(mul.data[7] == 0.0f);
    REQUIRE(mul.data[8] == 1.0f);
}

TEST_CASE("Matrix Vector Mul", "[matrix][vector]")
{
    Vector<3, int> mul = Matrix<3, 2, int>({1, 2, 3, 4, 5, 6}) * Vector<2, int>({7, 8});
    REQUIRE(mul.data[0] == 23);
    REQUIRE(mul.data[1] == 53);
    REQUIRE(mul.data[2] == 83);
}

TEST_CASE("Translation", "[matrix][vector][transformation]")
{
    Matrix<4, 4, float> tst = translate(identity<4, float>(), Vector<3, float>({1, 2, 3}));
    REQUIRE(tst.data[0] == 1.0f);
    REQUIRE(tst.data[1] == 0.0f);
    REQUIRE(tst.data[2] == 0.0f);
    REQUIRE(tst.data[3] == 1.0f);
    REQUIRE(tst.data[4] == 0.0f);
    REQUIRE(tst.data[5] == 1.0f);
    REQUIRE(tst.data[6] == 0.0f);
    REQUIRE(tst.data[7] == 2.0f);
    REQUIRE(tst.data[8] == 0.0f);
    REQUIRE(tst.data[9] == 0.0f);
    REQUIRE(tst.data[10] == 1.0f);
    REQUIRE(tst.data[11] == 3.0f);
    REQUIRE(tst.data[12] == 0.0f);
    REQUIRE(tst.data[13] == 0.0f);
    REQUIRE(tst.data[14] == 0.0f);
    REQUIRE(tst.data[15] == 1.0f);
}

TEST_CASE("Scale", "[matrix][vector][transformation]")
{
    Matrix<4, 4, float> scl = scale(identity<4, float>(), Vector<3, float>({1, 2, 4}));
    REQUIRE(scl.data[0] == 1.0f);
    REQUIRE(scl.data[1] == 0.0f);
    REQUIRE(scl.data[2] == 0.0f);
    REQUIRE(scl.data[3] == 0.0f);
    REQUIRE(scl.data[4] == 0.0f);
    REQUIRE(scl.data[5] == 2.0f);
    REQUIRE(scl.data[6] == 0.0f);
    REQUIRE(scl.data[7] == 0.0f);
    REQUIRE(scl.data[8] == 0.0f);
    REQUIRE(scl.data[9] == 0.0f);
    REQUIRE(scl.data[10] == 4.0f);
    REQUIRE(scl.data[11] == 0.0f);
    REQUIRE(scl.data[12] == 0.0f);
    REQUIRE(scl.data[13] == 0.0f);
    REQUIRE(scl.data[14] == 0.0f);
    REQUIRE(scl.data[15] == 1.0f);
}

TEST_CASE("Combine transformations", "[matrix][vector][transformation]")
{
    Matrix<4, 4, float> combine = scale(translate(identity<4, float>(), Vector<3, float>({1, 2, 3})), Vector<3, float>({1, 2, 4}));
    REQUIRE(combine.data[0] == 1.0f);
    REQUIRE(combine.data[1] == 0.0f);
    REQUIRE(combine.data[2] == 0.0f);
    REQUIRE(combine.data[3] == 1.0f);
    REQUIRE(combine.data[4] == 0.0f);
    REQUIRE(combine.data[5] == 2.0f);
    REQUIRE(combine.data[6] == 0.0f);
    REQUIRE(combine.data[7] == 2.0f);
    REQUIRE(combine.data[8] == 0.0f);
    REQUIRE(combine.data[9] == 0.0f);
    REQUIRE(combine.data[10] == 4.0f);
    REQUIRE(combine.data[11] == 3.0f);
    REQUIRE(combine.data[12] == 0.0f);
    REQUIRE(combine.data[13] == 0.0f);
    REQUIRE(combine.data[14] == 0.0f);
    REQUIRE(combine.data[15] == 1.0f);
}