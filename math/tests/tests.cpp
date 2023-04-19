#define CATCH_CONFIG_MAIN
#define PI 3.14159265f

#include <catch2/catch_all.hpp>
#include <pickle/math.h>

using namespace pickle::math;

template <typename T>
T roundTwoDigets(T value)
{
    return static_cast<T>(round(value * 100.0) / 100.0);
}

TEST_CASE("Vector Copy", "[vector]")
{
    Vector<2, float> vector({1, 1});
    Vector<2, float> result = vector;
    REQUIRE(result.data[0] == 1.0f);
    REQUIRE(result.data[1] == 1.0f);
}

TEST_CASE("Vector Sum", "[vector]")
{
    Vector<2, float> result = Vector<2, float>({1, 1}) + Vector<2, float>({-1, 0});
    REQUIRE(result.data[0] == 0.0f);
    REQUIRE(result.data[1] == 1.0f);
}

TEST_CASE("Vector Sub", "[vector]")
{
    Vector<3, float> result = Vector<3, float>({1, 1, 2}) - Vector<3, float>({-1, 0, 4});
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 1.0f);
    REQUIRE(result.data[2] == -2.0f);
}

TEST_CASE("Vector Scalar Mul", "[vector]")
{
    Vector<2, int> result = Vector<2, int>({2, 4}) * 3;
    REQUIRE(result.data[0] == 6);
    REQUIRE(result.data[1] == 12);
}

TEST_CASE("Vector Scalar Div", "[vector]")
{
    Vector<3, float> result = Vector<3, float>({5, -3, 2}) / 2;
    REQUIRE(result.data[0] == 2.5f);
    REQUIRE(result.data[1] == -1.5f);
    REQUIRE(result.data[2] == 1.0f);
}

TEST_CASE("Vector Equal", "[vector]")
{
    Vector<3, float> first = Vector<3, float>({5, -3, 2});
    Vector<3, float> second = Vector<3, float>({5, -3, 2});
    bool result = first == second;
    REQUIRE(result);
}

TEST_CASE("Vector Equal False", "[vector]")
{
    Vector<3, float> first = Vector<3, float>({5, -3, 3});
    Vector<3, float> second = Vector<3, float>({5, -3, 2});
    bool result = first == second;
    REQUIRE(!result);
}

TEST_CASE("Vector Not Equal", "[vector]")
{
    Vector<3, float> first = Vector<3, float>({10, -6, 4});
    Vector<3, float> second = Vector<3, float>({5, -3, 2});
    bool result = first != second;
    REQUIRE(result);
}

TEST_CASE("Vector Not Equal False", "[vector]")
{
    Vector<3, float> first = Vector<3, float>({5, -3, 2});
    Vector<3, float> second = Vector<3, float>({5, -3, 2});
    bool result = first != second;
    REQUIRE(!result);
}

TEST_CASE("Vector Cut Dimention Simple", "[vector]")
{
    Vector<2, float> result = Vector<3, float>({5, -3, 2}).cutDimension<1>();
    REQUIRE(result.data[0] == 5.0f);
    REQUIRE(result.data[1] == 2.0f);
}

TEST_CASE("Vector Cut Dimention", "[vector]")
{
    Vector<3, float> result = Vector<5, float>({5, -3, 2, 5, 1}).cutDimension<2, 2>();
    REQUIRE(result.data[0] == 5.0f);
    REQUIRE(result.data[1] == -3.0f);
    REQUIRE(result.data[2] == 1.0f);
}

TEST_CASE("Vector Extract", "[vector]")
{
    Vector<2, float> result = Vector<4, float>({5, -3, 2, -7}).extract<1, 2>();
    REQUIRE(result.data[0] == -3.0f);
    REQUIRE(result.data[1] == 2.0f);
}

TEST_CASE("Vector Add Dimension Simple", "[vector]")
{
    Vector<4, float> result = Vector<3, float>({5, -3, 2}).addDimension<1>(4);
    REQUIRE(result.data[0] == 5.0f);
    REQUIRE(result.data[1] == 4.0f);
    REQUIRE(result.data[2] == -3.0f);
    REQUIRE(result.data[3] == 2.0f);
}

TEST_CASE("Vector Add Dimension", "[vector]")
{
    Vector<6, float> result = Vector<3, float>({5, -3, 2}).addDimension<2, 3>(Vector<3, float>({1, 4, -8}));
    REQUIRE(result.data[0] == 5.0f);
    REQUIRE(result.data[1] == -3.0f);
    REQUIRE(result.data[2] == 1.0f);
    REQUIRE(result.data[3] == 4.0f);
    REQUIRE(result.data[4] == -8.0f);
    REQUIRE(result.data[5] == 2.0f);
}

TEST_CASE("Vector Add Dimension To End", "[vector]")
{
    Vector<4, float> result = Vector<3, float>({5, -3, 2}).addDimension<3>(4);
    REQUIRE(result.data[0] == 5.0f);
    REQUIRE(result.data[1] == -3.0f);
    REQUIRE(result.data[2] == 2.0f);
    REQUIRE(result.data[3] == 4.0f);
}

TEST_CASE("Vector Replace Simple", "[vector]")
{
    Vector<3, float> result = Vector<3, float>({5, -3, 2}).replace<1>(4);
    REQUIRE(result.data[0] == 5.0f);
    REQUIRE(result.data[1] == 4.0f);
    REQUIRE(result.data[2] == 2.0f);
}

TEST_CASE("Vector Replace", "[vector]")
{
    Vector<4, float> result = Vector<4, float>({5, -3, 2, -7}).replace<1, 2>(Vector<2, float>({1, 4}));
    REQUIRE(result.data[0] == 5.0f);
    REQUIRE(result.data[1] == 1.0f);
    REQUIRE(result.data[2] == 4.0f);
    REQUIRE(result.data[3] == -7.0f);
}

TEST_CASE("Vector Replace To Start", "[vector]")
{
    Vector<3, float> result = Vector<3, float>({5, -3, 2}).replace<0>(4);
    REQUIRE(result.data[0] == 4.0f);
    REQUIRE(result.data[1] == -3.0f);
    REQUIRE(result.data[2] == 2.0f);
}

TEST_CASE("Vector Length", "[vector]")
{
    float result = length(Vector<3, float>({3, 4, 0}));
    REQUIRE(result == 5.0f);
}

TEST_CASE("Vector Normalization", "[vector]")
{
    Vector<3, float> result = normalize(Vector<3, float>({8, 0, 6}));
    REQUIRE(result.data[0] == 0.8f);
    REQUIRE(result.data[1] == 0.0f);
    REQUIRE(result.data[2] == 0.6f);
}

TEST_CASE("Vector Dot", "[vector]")
{
    float result = dot(Vector<3, float>({2, -1, 3}), Vector<3, float>({1, 2, -1}));
    REQUIRE(result == -3.0f);
}

TEST_CASE("Vector Cross", "[vector]")
{
    Vector<3, float> result = cross(Vector<3, float>({1, 0, 0}), Vector<3, float>({0, 1, 0}));
    REQUIRE(result.data[0] == 0.0f);
    REQUIRE(result.data[1] == 0.0f);
    REQUIRE(result.data[2] == 1.0f);
}

TEST_CASE("Vector Reflect", "[vector]")
{
    Vector<3, int> result = reflect(Vector<3, int>({-1, -1, -1}), Vector<3, int>({1, 0, 0}));
    REQUIRE(result.data[0] == 1);
    REQUIRE(result.data[1] == -1);
    REQUIRE(result.data[2] == -1);
}

TEST_CASE("Vector To Quaternion", "[vector][quaternion]")
{
    Vector<4, float> vector = Vector<4, float>({1, 2, 3, 4});
    Quaternion<float> result = toQuaternion(vector);
    REQUIRE(result.w == 4.0f);
    REQUIRE(result.x == 1.0f);
    REQUIRE(result.y == 2.0f);
    REQUIRE(result.z == 3.0f);
}

TEST_CASE("Matrix Copy", "[matrix]")
{
    Matrix<2, 3, int> matrix({1, 2, -3, 1, -2, 4});
    Matrix<2, 3, int> result = matrix;
    REQUIRE(result.data[0] == 1);
    REQUIRE(result.data[1] == 2);
    REQUIRE(result.data[2] == -3);
    REQUIRE(result.data[3] == 1);
    REQUIRE(result.data[4] == -2);
    REQUIRE(result.data[5] == 4);
}

TEST_CASE("Matrix Sum", "[matrix]")
{
    Matrix<2, 3, int> result = Matrix<2, 3, int>({1, 2, -3, 1, -2, 4}) + Matrix<2, 3, int>({2, 1, 2, -1, 4, 5});
    REQUIRE(result.data[0] == 3);
    REQUIRE(result.data[1] == 3);
    REQUIRE(result.data[2] == -1);
    REQUIRE(result.data[3] == 0);
    REQUIRE(result.data[4] == 2);
    REQUIRE(result.data[5] == 9);
}

TEST_CASE("Matrix Sub", "[matrix]")
{
    Matrix<2, 3, float> result = Matrix<2, 3, float>({1, 2, -3, 1, -2, 4}) - Matrix<2, 3, float>({2, 1, 2, -1, 4, 5});
    REQUIRE(result.data[0] == -1.0f);
    REQUIRE(result.data[1] == 1.0f);
    REQUIRE(result.data[2] == -5.0f);
    REQUIRE(result.data[3] == 2.0f);
    REQUIRE(result.data[4] == -6.0f);
    REQUIRE(result.data[5] == -1.0f);
}

TEST_CASE("Matrix Scalar Mul", "[matrix]")
{
    Matrix<2, 2, float> result = Matrix<2, 2, float>({1, -1, 2, -1}) * 3;
    REQUIRE(result.data[0] == 3.0f);
    REQUIRE(result.data[1] == -3.0f);
    REQUIRE(result.data[2] == 6.0f);
    REQUIRE(result.data[3] == -3.0f);
}

TEST_CASE("Matrix Scalar Div", "[matrix]")
{
    Matrix<3, 3, float> result = Matrix<3, 3, float>({1, -1.2f, 2, -1, 4, 2, 1, -5.2f, 2.2f}) / 2;
    REQUIRE(result.data[0] == 0.5f);
    REQUIRE(result.data[1] == -0.6f);
    REQUIRE(result.data[2] == 1.0f);
    REQUIRE(result.data[3] == -0.5f);
    REQUIRE(result.data[4] == 2.0f);
    REQUIRE(result.data[5] == 1.0f);
    REQUIRE(result.data[6] == 0.5f);
    REQUIRE(result.data[7] == -2.6f);
    REQUIRE(result.data[8] == 1.1f);
}

TEST_CASE("Matrix Mul", "[matrix]")
{
    Matrix<3, 3, float> result = Matrix<3, 2, float>({2, 3, 2, 1, 5, 3}) * Matrix<2, 3, float>({5, 3, 2, 2, 1, 4});
    REQUIRE(result.data[0] == 16.0f);
    REQUIRE(result.data[1] == 9.0f);
    REQUIRE(result.data[2] == 16.0f);
    REQUIRE(result.data[3] == 12.0f);
    REQUIRE(result.data[4] == 7.0f);
    REQUIRE(result.data[5] == 8.0f);
    REQUIRE(result.data[6] == 31.0f);
    REQUIRE(result.data[7] == 18.0f);
    REQUIRE(result.data[8] == 22.0f);
}

TEST_CASE("Matrix Equal", "[matrix]")
{
    Matrix<3, 2, float> first = Matrix<3, 2, float>({2, 3, 2, 1, 5, 3});
    Matrix<3, 2, float> second = Matrix<3, 2, float>({2, 3, 2, 1, 5, 3});
    bool result = first == second;
    REQUIRE(result);
}

TEST_CASE("Matrix Equal False", "[matrix]")
{
    Matrix<2, 2, float> first = Matrix<2, 2, float>({2, -2, 4, -2});
    Matrix<2, 2, float> second = Matrix<2, 2, float>({1, -1, 2, -1});
    bool result = first == second;
    REQUIRE(!result);
}

TEST_CASE("Matrix Not Equal", "[matrix]")
{
    Matrix<2, 2, float> first = Matrix<2, 2, float>({1, -1, 2, -1});
    Matrix<2, 2, float> second = Matrix<2, 2, float>({2, -2, 4, -3});
    bool result = first != second;
    REQUIRE(result);
}

TEST_CASE("Matrix Not Equal False", "[matrix]")
{
    Matrix<2, 3, float> first = Matrix<2, 3, float>({2, 3, 2, 1, 5, 3});
    Matrix<2, 3, float> second = Matrix<2, 3, float>({2, 3, 2, 1, 5, 3});
    bool result = first != second;
    REQUIRE(!result);
}

TEST_CASE("Matrix Cut Row Dimention Simple", "[matrix]")
{
    Matrix<2, 3, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .cutRowDimension<1>();
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 3.0f);
    REQUIRE(result.data[2] == 2.0f);
    REQUIRE(result.data[3] == -2.0f);
    REQUIRE(result.data[4] == 1.0f);
    REQUIRE(result.data[5] == 4.0f);
}

TEST_CASE("Matrix Cut Row Dimention", "[matrix]")
{
    Matrix<1, 3, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .cutRowDimension<1, 2>();
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 3.0f);
    REQUIRE(result.data[2] == 2.0f);
}

TEST_CASE("Matrix Cut Column Dimention Simple", "[matrix]")
{
    Matrix<3, 2, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .cutColumnDimension<1>();
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 2.0f);
    REQUIRE(result.data[2] == 1.0f);
    REQUIRE(result.data[3] == 3.0f);
    REQUIRE(result.data[4] == -2.0f);
    REQUIRE(result.data[5] == 4.0f);
}

TEST_CASE("Matrix Cut Column Dimention", "[matrix]")
{
    Matrix<3, 1, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .cutColumnDimension<1, 2>();
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 1.0f);
    REQUIRE(result.data[2] == -2.0f);
}

TEST_CASE("Matrix Cut Dimention Simple", "[matrix]")
{
    Matrix<2, 2, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .cutDimension<1, 1>();
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 2.0f);
    REQUIRE(result.data[2] == -2.0f);
    REQUIRE(result.data[3] == 4.0f);
}

TEST_CASE("Matrix Cut Dimention Zero", "[matrix]")
{
    Matrix<2, 3, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .cutDimension<1, 1, 1, 0>();
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 3.0f);
    REQUIRE(result.data[2] == 2.0f);
    REQUIRE(result.data[3] == -2.0f);
    REQUIRE(result.data[4] == 1.0f);
    REQUIRE(result.data[5] == 4.0f);
}

TEST_CASE("Matrix Cut Dimention", "[matrix]")
{
    Matrix<3, 2, float> result = Matrix<4, 4, float>({2, 3, 2, 1,
                                                      5, 3, -2, 1,
                                                      4, 8, 2, -3,
                                                      6, 9, -5, 1})
                                     .cutDimension<1, 1, 2, 2>();
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 3.0f);
    REQUIRE(result.data[2] == 4.0f);
    REQUIRE(result.data[3] == 8.0f);
    REQUIRE(result.data[4] == 6.0f);
    REQUIRE(result.data[5] == 9.0f);
}

TEST_CASE("Matrix Extract Simple", "[matrix]")
{
    Matrix<1, 1, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .extract<1, 1, 1, 1>();
    REQUIRE(result.data[0] == 5.0f);
}

TEST_CASE("Matrix Extract", "[matrix]")
{
    Matrix<1, 2, float> result = Matrix<4, 4, float>({2, 3, 2, 1,
                                                      5, 3, -2, 1,
                                                      4, 8, 2, -3,
                                                      6, 9, -5, 1})
                                     .extract<1, 1, 2, 2>();
    REQUIRE(result.data[0] == -2.0f);
    REQUIRE(result.data[1] == 1.0f);
}

TEST_CASE("Matrix Replace Simple", "[matrix]")
{
    Matrix<3, 3, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .replace<1, 1>(10);
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 3.0f);
    REQUIRE(result.data[2] == 2.0f);
    REQUIRE(result.data[3] == 1.0f);
    REQUIRE(result.data[4] == 10.0f);
    REQUIRE(result.data[5] == 3.0f);
    REQUIRE(result.data[6] == -2.0f);
    REQUIRE(result.data[7] == 1.0f);
    REQUIRE(result.data[8] == 4.0f);
}

TEST_CASE("Matrix Replace", "[matrix]")
{
    Matrix<3, 3, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .replace<1, 2, 1, 1>(Matrix<2, 1, float>({7, 8}));
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 3.0f);
    REQUIRE(result.data[2] == 2.0f);
    REQUIRE(result.data[3] == 1.0f);
    REQUIRE(result.data[4] == 7.0f);
    REQUIRE(result.data[5] == 3.0f);
    REQUIRE(result.data[6] == -2.0f);
    REQUIRE(result.data[7] == 8.0f);
    REQUIRE(result.data[8] == 4.0f);
}

TEST_CASE("Matrix Add Row Dimension Simple", "[matrix]")
{
    Matrix<4, 3, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .addRowDimension<2>(Matrix<1, 3, float>({7, 8, 9}));
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 3.0f);
    REQUIRE(result.data[2] == 2.0f);
    REQUIRE(result.data[3] == 1.0f);
    REQUIRE(result.data[4] == 5.0f);
    REQUIRE(result.data[5] == 3.0f);
    REQUIRE(result.data[6] == 7.0f);
    REQUIRE(result.data[7] == 8.0f);
    REQUIRE(result.data[8] == 9.0f);
    REQUIRE(result.data[9] == -2.0f);
    REQUIRE(result.data[10] == 1.0f);
    REQUIRE(result.data[11] == 4.0f);
}

TEST_CASE("Matrix Add Row Dimension", "[matrix]")
{
    Matrix<5, 3, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .addRowDimension<1, 2>(Matrix<2, 3, float>({7, 8, 9, 10, 11, 12}));
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 3.0f);
    REQUIRE(result.data[2] == 2.0f);
    REQUIRE(result.data[3] == 7.0f);
    REQUIRE(result.data[4] == 8.0f);
    REQUIRE(result.data[5] == 9.0f);
    REQUIRE(result.data[6] == 10.0f);
    REQUIRE(result.data[7] == 11.0f);
    REQUIRE(result.data[8] == 12.0f);
    REQUIRE(result.data[9] == 1.0f);
    REQUIRE(result.data[10] == 5.0f);
    REQUIRE(result.data[11] == 3.0f);
    REQUIRE(result.data[12] == -2.0f);
    REQUIRE(result.data[13] == 1.0f);
    REQUIRE(result.data[14] == 4.0f);
}

TEST_CASE("Matrix Add Column Dimension Simple", "[matrix]")
{
    Matrix<3, 4, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .addColumnDimension<2>(Matrix<3, 1, float>({7, 8, 9}));
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 3.0f);
    REQUIRE(result.data[2] == 7.0f);
    REQUIRE(result.data[3] == 2.0f);
    REQUIRE(result.data[4] == 1.0f);
    REQUIRE(result.data[5] == 5.0f);
    REQUIRE(result.data[6] == 8.0f);
    REQUIRE(result.data[7] == 3.0f);
    REQUIRE(result.data[8] == -2.0f);
    REQUIRE(result.data[9] == 1.0f);
    REQUIRE(result.data[10] == 9.0f);
    REQUIRE(result.data[11] == 4.0f);
}

TEST_CASE("Matrix Add Column Dimension", "[matrix]")
{
    Matrix<3, 5, float> result = Matrix<3, 3, float>({2, 3, 2,
                                                      1, 5, 3,
                                                      -2, 1, 4})
                                     .addColumnDimension<1, 2>(Matrix<3, 2, float>({7, 8, 9, 10, 11, 12}));
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 7.0f);
    REQUIRE(result.data[2] == 8.0f);
    REQUIRE(result.data[3] == 3.0f);
    REQUIRE(result.data[4] == 2.0f);
    REQUIRE(result.data[5] == 1.0f);
    REQUIRE(result.data[6] == 9.0f);
    REQUIRE(result.data[7] == 10.0f);
    REQUIRE(result.data[8] == 5.0f);
    REQUIRE(result.data[9] == 3.0f);
    REQUIRE(result.data[10] == -2.0f);
    REQUIRE(result.data[11] == 11.0f);
    REQUIRE(result.data[12] == 12.0f);
    REQUIRE(result.data[13] == 1.0f);
    REQUIRE(result.data[14] == 4.0f);
}

TEST_CASE("Matrix Identity", "[matrix]")
{
    Matrix<3, 3, float> result = identity<3, float>();
    REQUIRE(result.data[0] == 1.0f);
    REQUIRE(result.data[1] == 0.0f);
    REQUIRE(result.data[2] == 0.0f);
    REQUIRE(result.data[3] == 0.0f);
    REQUIRE(result.data[4] == 1.0f);
    REQUIRE(result.data[5] == 0.0f);
    REQUIRE(result.data[6] == 0.0f);
    REQUIRE(result.data[7] == 0.0f);
    REQUIRE(result.data[8] == 1.0f);
}

TEST_CASE("Matrix Identity Mul", "[matrix]")
{
    Matrix<3, 3, float> result = Matrix<3, 3, float>({2, 3, -2, 1, 5.3f, -3, 4, 5, 8.1f}) * identity<3, float>();
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 3.0f);
    REQUIRE(result.data[2] == -2.0f);
    REQUIRE(result.data[3] == 1.0f);
    REQUIRE(result.data[4] == 5.3f);
    REQUIRE(result.data[5] == -3.0f);
    REQUIRE(result.data[6] == 4.0f);
    REQUIRE(result.data[7] == 5.0f);
    REQUIRE(result.data[8] == 8.1f);
}

TEST_CASE("Matrix Transpose", "[matrix]")
{
    Matrix<2, 3, float> result = transpose(Matrix<3, 2, float>({2, 3, 2, 1, 5, 3}));
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 2.0f);
    REQUIRE(result.data[2] == 5.0f);
    REQUIRE(result.data[3] == 3.0f);
    REQUIRE(result.data[4] == 1.0f);
    REQUIRE(result.data[5] == 3.0f);
}

TEST_CASE("Matrix Determinant", "[matrix]")
{
    float result = determinant(Matrix<4, 4, float>({24, 20, 3, 40, 15, 3, 5, 11, 21, 24, 1, -8, 5, -3, 16, -10}));
    REQUIRE(result == -155145.0f);
}

TEST_CASE("Matrix Inverse", "[matrix]")
{
    Matrix<3, 3, float> result = inverse(Matrix<3, 3, float>({3, 0, 2, 2, 0, -2, 0, 1, 1}));
    REQUIRE(result.data[0] == 0.2f);
    REQUIRE(result.data[1] == 0.2f);
    REQUIRE(result.data[2] == 0.0f);
    REQUIRE(result.data[3] == -0.2f);
    REQUIRE(result.data[4] == 0.3f);
    REQUIRE(result.data[5] == 1.0f);
    REQUIRE(result.data[6] == 0.2f);
    REQUIRE(result.data[7] == -0.3f);
    REQUIRE(result.data[8] == 0.0f);
}

TEST_CASE("Matrix Inverse Mul", "[matrix]")
{
    Matrix<3, 3, float> invBase = Matrix<3, 3, float>({3, 0, 2, 2, 0, -2, 0, 1, 1});
    Matrix<3, 3, float> inv = inverse(invBase);
    Matrix<3, 3, float> result = inv * invBase;
    REQUIRE(result.data[0] == 1.0f);
    REQUIRE(result.data[1] == 0.0f);
    REQUIRE(result.data[2] == 0.0f);
    REQUIRE(result.data[3] == 0.0f);
    REQUIRE(result.data[4] == 1.0f);
    REQUIRE(result.data[5] == 0.0f);
    REQUIRE(result.data[6] == 0.0f);
    REQUIRE(result.data[7] == 0.0f);
    REQUIRE(result.data[8] == 1.0f);
}

TEST_CASE("Matrix Vector Mul", "[matrix][vector]")
{
    Vector<3, int> result = Matrix<3, 2, int>({1, 2, 3, 4, 5, 6}) * Vector<2, int>({7, 8});
    REQUIRE(result.data[0] == 23);
    REQUIRE(result.data[1] == 53);
    REQUIRE(result.data[2] == 83);
}

TEST_CASE("Translation", "[matrix][vector][transformation]")
{
    Matrix<4, 4, float> result = translate(identity<4, float>(), Vector<3, float>({1, 2, 3}));
    REQUIRE(result.data[0] == 1.0f);
    REQUIRE(result.data[1] == 0.0f);
    REQUIRE(result.data[2] == 0.0f);
    REQUIRE(result.data[3] == 1.0f);
    REQUIRE(result.data[4] == 0.0f);
    REQUIRE(result.data[5] == 1.0f);
    REQUIRE(result.data[6] == 0.0f);
    REQUIRE(result.data[7] == 2.0f);
    REQUIRE(result.data[8] == 0.0f);
    REQUIRE(result.data[9] == 0.0f);
    REQUIRE(result.data[10] == 1.0f);
    REQUIRE(result.data[11] == 3.0f);
    REQUIRE(result.data[12] == 0.0f);
    REQUIRE(result.data[13] == 0.0f);
    REQUIRE(result.data[14] == 0.0f);
    REQUIRE(result.data[15] == 1.0f);
}

TEST_CASE("Scale", "[matrix][vector][transformation]")
{
    Matrix<4, 4, float> result = scale(identity<4, float>(), Vector<3, float>({1, 2, 4}));
    REQUIRE(result.data[0] == 1.0f);
    REQUIRE(result.data[1] == 0.0f);
    REQUIRE(result.data[2] == 0.0f);
    REQUIRE(result.data[3] == 0.0f);
    REQUIRE(result.data[4] == 0.0f);
    REQUIRE(result.data[5] == 2.0f);
    REQUIRE(result.data[6] == 0.0f);
    REQUIRE(result.data[7] == 0.0f);
    REQUIRE(result.data[8] == 0.0f);
    REQUIRE(result.data[9] == 0.0f);
    REQUIRE(result.data[10] == 4.0f);
    REQUIRE(result.data[11] == 0.0f);
    REQUIRE(result.data[12] == 0.0f);
    REQUIRE(result.data[13] == 0.0f);
    REQUIRE(result.data[14] == 0.0f);
    REQUIRE(result.data[15] == 1.0f);
}

TEST_CASE("Rotate X", "[matrix][vector][transformation]")
{
    Matrix<4, 4, float> result = rotate(identity<4, float>(), PI / 2.0f, Vector<3, float>({1, 0, 0}));
    REQUIRE(roundTwoDigets(result.data[0]) == 1.0f);
    REQUIRE(roundTwoDigets(result.data[1]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[2]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[3]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[4]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[5]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[6]) == -1.0f);
    REQUIRE(roundTwoDigets(result.data[7]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[8]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[9]) == 1.0f);
    REQUIRE(roundTwoDigets(result.data[10]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[11]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[12]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[13]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[14]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[15]) == 1.0f);
}

TEST_CASE("Rotate Y", "[matrix][vector][transformation]")
{
    Matrix<4, 4, float> result = rotate(identity<4, float>(), PI, Vector<3, float>({0, 1, 0}));
    REQUIRE(roundTwoDigets(result.data[0]) == -1.0f);
    REQUIRE(roundTwoDigets(result.data[1]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[2]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[3]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[4]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[5]) == 1.0f);
    REQUIRE(roundTwoDigets(result.data[6]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[7]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[8]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[9]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[10]) == -1.0f);
    REQUIRE(roundTwoDigets(result.data[11]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[12]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[13]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[14]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[15]) == 1.0f);
}

TEST_CASE("Rotate Z", "[matrix][vector][transformation]")
{
    Matrix<4, 4, float> result = rotate(identity<4, float>(), PI / 6.0f, Vector<3, float>({0, 0, 1}));
    REQUIRE(roundTwoDigets(result.data[0]) == 0.87f);
    REQUIRE(roundTwoDigets(result.data[1]) == -0.5f);
    REQUIRE(roundTwoDigets(result.data[2]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[3]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[4]) == 0.5f);
    REQUIRE(roundTwoDigets(result.data[5]) == 0.87f);
    REQUIRE(roundTwoDigets(result.data[6]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[7]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[8]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[9]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[10]) == 1.0f);
    REQUIRE(roundTwoDigets(result.data[11]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[12]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[13]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[14]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[15]) == 1.0f);
}

TEST_CASE("Rotate XYZ", "[matrix][vector][transformation]")
{
    Matrix<4, 4, float> result = rotate(identity<4, float>(), PI / 2.0f, Vector<3, float>({1, 1, 1}));
    REQUIRE(roundTwoDigets(result.data[0]) == 1.0f);
    REQUIRE(roundTwoDigets(result.data[1]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[2]) == 2.0f);
    REQUIRE(roundTwoDigets(result.data[3]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[4]) == 2.0f);
    REQUIRE(roundTwoDigets(result.data[5]) == 1.0f);
    REQUIRE(roundTwoDigets(result.data[6]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[7]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[8]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[9]) == 2.0f);
    REQUIRE(roundTwoDigets(result.data[10]) == 1.0f);
    REQUIRE(roundTwoDigets(result.data[11]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[12]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[13]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[14]) == 0.0f);
    REQUIRE(roundTwoDigets(result.data[15]) == 1.0f);
}

TEST_CASE("Rotate Vector Z", "[matrix][vector][transformation]")
{
    Vector<4, float> result = rotate(identity<4, float>(), PI / 6.0f, Vector<3, float>({0, 0, 1})) * Vector<4, float>({2, 1, 3});
    REQUIRE(roundTwoDigets(result.data[0]) == 1.23f);
    REQUIRE(roundTwoDigets(result.data[1]) == 1.87f);
    REQUIRE(roundTwoDigets(result.data[2]) == 3.0f);
}

TEST_CASE("Rotate Vector XYZ", "[matrix][vector][transformation]")
{
    Vector<4, float> result = rotate(identity<4, float>(), PI / 2.0f, Vector<3, float>({1, 1, 1})) * Vector<4, float>({2, 1, 3});
    REQUIRE(roundTwoDigets(result.data[0]) == 8.0f);
    REQUIRE(roundTwoDigets(result.data[1]) == 5.0f);
    REQUIRE(roundTwoDigets(result.data[2]) == 5.0f);
}

TEST_CASE("Combine transformations", "[matrix][vector][transformation]")
{
    Matrix<4, 4, float> result = scale(translate(identity<4, float>(), Vector<3, float>({1, 2, 3})), Vector<3, float>({1, 2, 4}));
    REQUIRE(result.data[0] == 1.0f);
    REQUIRE(result.data[1] == 0.0f);
    REQUIRE(result.data[2] == 0.0f);
    REQUIRE(result.data[3] == 1.0f);
    REQUIRE(result.data[4] == 0.0f);
    REQUIRE(result.data[5] == 2.0f);
    REQUIRE(result.data[6] == 0.0f);
    REQUIRE(result.data[7] == 2.0f);
    REQUIRE(result.data[8] == 0.0f);
    REQUIRE(result.data[9] == 0.0f);
    REQUIRE(result.data[10] == 4.0f);
    REQUIRE(result.data[11] == 3.0f);
    REQUIRE(result.data[12] == 0.0f);
    REQUIRE(result.data[13] == 0.0f);
    REQUIRE(result.data[14] == 0.0f);
    REQUIRE(result.data[15] == 1.0f);
}

TEST_CASE("Convert To Radians", "[angle][transformation]")
{
    REQUIRE(roundTwoDigets(radians(180.0)) == 3.14);
    REQUIRE(roundTwoDigets(radians(360.0f)) == 6.28f);
    REQUIRE(roundTwoDigets(radians(30.0)) == 0.52);
    REQUIRE(roundTwoDigets(radians(-30.0f)) == -0.52f);
    REQUIRE(roundTwoDigets(radians(-180.0)) == -3.14);
}

TEST_CASE("Look at", "[camera][matrix][vector][transformation]")
{
    Matrix<4, 4, float> result = lookAt(Vector<3, float>({0.0f, 0.0f, -3.0f}), Vector<3, float>({0.0f, 0.0f, 0.0f}), Vector<3, float>({0.0f, 1.0f, 0.0f}));
    REQUIRE(result.data[0] == -1.0f);
    REQUIRE(result.data[1] == 0.0f);
    REQUIRE(result.data[2] == 0.0f);
    REQUIRE(result.data[3] == 0.0f);
    REQUIRE(result.data[4] == 0.0f);
    REQUIRE(result.data[5] == 1.0f);
    REQUIRE(result.data[6] == 0.0f);
    REQUIRE(result.data[7] == 0.0f);
    REQUIRE(result.data[8] == 0.0f);
    REQUIRE(result.data[9] == 0.0f);
    REQUIRE(result.data[10] == -1.0f);
    REQUIRE(result.data[11] == -3.0f);
    REQUIRE(result.data[12] == 0.0f);
    REQUIRE(result.data[13] == 0.0f);
    REQUIRE(result.data[14] == 0.0f);
    REQUIRE(result.data[15] == 1.0f);
}

TEST_CASE("Quaternion Copy", "[quaternion]")
{
    Quaternion<float> quaternion({1, 1, 2, 3});
    Quaternion<float> result = quaternion;
    REQUIRE(result.w == 1.0f);
    REQUIRE(result.x == 1.0f);
    REQUIRE(result.y == 2.0f);
    REQUIRE(result.z == 3.0f);
}

TEST_CASE("Quaternion Sum", "[quaternion]")
{
    Quaternion<float> result = Quaternion<float>({1, 1, 3, 2}) + Quaternion<float>({-1, 0, -2, 1});
    REQUIRE(result.w == 0.0f);
    REQUIRE(result.x == 1.0f);
    REQUIRE(result.y == 1.0f);
    REQUIRE(result.z == 3.0f);
}

TEST_CASE("Quaternion Sub", "[quaternion]")
{
    Quaternion<float> result = Quaternion<float>({1, 2, 4, 0}) - Quaternion<float>({-1, 2, 3, 1});
    REQUIRE(result.w == 2.0f);
    REQUIRE(result.x == 0.0f);
    REQUIRE(result.y == 1.0f);
    REQUIRE(result.z == -1.0f);
}

TEST_CASE("Quaternion Scalar Mul", "[quaternion]")
{
    Quaternion<int> result = Quaternion<int>({2, 4, 5, -1}) * 3;
    REQUIRE(result.w == 6);
    REQUIRE(result.x == 12);
    REQUIRE(result.y == 15);
    REQUIRE(result.z == -3);
}

TEST_CASE("Quaternion Scalar Div", "[quaternion]")
{
    Quaternion<float> result = Quaternion<float>({5, -3, 2, -4}) / 2;
    REQUIRE(result.w == 2.5f);
    REQUIRE(result.x == -1.5f);
    REQUIRE(result.y == 1.0f);
    REQUIRE(result.z == -2.0f);
}

TEST_CASE("Quaternion Equal", "[quaternion]")
{
    Quaternion<float> first = Quaternion<float>({2, 4, 5, -1});
    Quaternion<float> second = Quaternion<float>({2, 4, 5, -1});
    bool result = first == second;
    REQUIRE(result);
}

TEST_CASE("Quaternion Equal False", "[quaternion]")
{
    Quaternion<float> first = Quaternion<float>({2, 4, 5, -1});
    Quaternion<float> second = Quaternion<float>({4, 8, 10, -2});
    bool result = first == second;
    REQUIRE(!result);
}

TEST_CASE("Quaternion Not Equal", "[quaternion]")
{
    Quaternion<float> first = Quaternion<float>({2, 4, 5, -1});
    Quaternion<float> second = Quaternion<float>({4, 8, 10, -1});
    bool result = first != second;
    REQUIRE(result);
}

TEST_CASE("Quaternion Not Equal False", "[quaternion]")
{
    Quaternion<float> first = Quaternion<float>({2, 4, 5, -1});
    Quaternion<float> second = Quaternion<float>({2, 4, 5, -1});
    bool result = first != second;
    REQUIRE(!result);
}

TEST_CASE("Quaternion Length", "[quaternion]")
{
    Quaternion<float> quaternion = Quaternion<float>({4, 0, 3, 0});
    float result = quaternion.length();
    REQUIRE(result == 5.0f);
}

TEST_CASE("Quaternion Square Length", "[quaternion]")
{
    Quaternion<float> quaternion = Quaternion<float>({4, 2, 3, 1});
    float result = quaternion.squareLength();
    REQUIRE(result == 30.0f);
}

TEST_CASE("Quaternion Square Length Equal Length Sqare", "[quaternion]")
{
    Quaternion<float> quaternion = Quaternion<float>({4, 2, 3, 1});
    bool result = roundTwoDigets(quaternion.squareLength()) == roundTwoDigets(quaternion.length() * quaternion.length());
    REQUIRE(result);
}

TEST_CASE("Quaternion Dot", "[quaternion]")
{
    Quaternion<float> first = Quaternion<float>({1, 2, 1, -1});
    Quaternion<float> second = Quaternion<float>({3, 0, 2, 2});
    float result = dot(first, second);
    REQUIRE(result == 3.0f);
}

TEST_CASE("Quaternion Conjugate", "[quaternion]")
{
    Quaternion<float> quaternion = Quaternion<float>({4, 2, 3, 1});
    Quaternion<float> result = conjugate(quaternion);
    REQUIRE(result.w == 4.0f);
    REQUIRE(result.x == -2.0f);
    REQUIRE(result.y == -3.0f);
    REQUIRE(result.z == -1.0f);
}

TEST_CASE("Quaternion Inverse", "[quaternion]")
{
    Quaternion<float> quaternion = Quaternion<float>({4, 2, 3, 1});
    Quaternion<float> result = inverse(quaternion);
    REQUIRE(roundTwoDigets(result.w) == 0.13f);
    REQUIRE(roundTwoDigets(result.x) == -0.07f);
    REQUIRE(roundTwoDigets(result.y) == -0.1f);
    REQUIRE(roundTwoDigets(result.z) == -0.03f);
}

TEST_CASE("Quaternion To Vector", "[quaternion][vector]")
{
    Quaternion<float> quaternion = Quaternion<float>({4, 2, 3, 1});
    Vector<4, float> result = toVector(quaternion);
    REQUIRE(result.data[0] == 2.0f);
    REQUIRE(result.data[1] == 3.0f);
    REQUIRE(result.data[2] == 1.0f);
    REQUIRE(result.data[3] == 4.0f);
}