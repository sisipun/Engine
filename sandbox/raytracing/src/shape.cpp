#include <raytracing/shape.h>

Shape::Shape(Color color) : color(color)
{
}

Shape::~Shape()
{
}

Color Shape::getColor() const
{
    return color;
}