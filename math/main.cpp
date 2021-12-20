#include <iostream>

#include "vector/vector2.h"

int main()
{
    pickle::math::Vector2<int> v1(1, 1);
    pickle::math::Vector2<int> v2(2, 2);
    pickle::math::Vector2<int> sum = v1 + v2;
    pickle::math::Vector2<int> div = v1 - v2;
    
    std::cout << "Sum: (" << sum.x << "," << sum.y << ")" << std::endl;
    std::cout << "Div: (" << div.x << "," << div.y << ")" << std::endl;
}