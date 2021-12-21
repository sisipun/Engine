#include <iostream>

#include "vector/vector2.h"
#include "vector/vector3.h"

int main()
{
    pickle::math::Vector2<int> v1(1, 1);
    pickle::math::Vector2<int> v2(2, 2);
    pickle::math::Vector3<int> v3(2, 2, 3);
    pickle::math::Vector3<int> v4(1, 2, 3);
    pickle::math::Vector2<int> sum = v1 + v2;
    pickle::math::Vector2<int> div = v1 - v2;
    pickle::math::Vector3<int> sum1 = v3 + v4;
    pickle::math::Vector3<int> div1 = v3 - v4;
    
    std::cout << "Sum: (" << sum.x << "," << sum.y << ")" << std::endl;
    std::cout << "Div: (" << div.x << "," << div.y << ")" << std::endl;
    
    std::cout << "Sum: (" << sum1.x << "," << sum1.y << "," << sum1.z << ")" << std::endl;
    std::cout << "Div: (" << div1.x << "," << div1.y << "," << div1.z << ")" << std::endl;
}