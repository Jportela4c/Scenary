#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;

int main()
{
    Vector4f v1 = Vector4f(1, 2, 3, 1);
    Vector4f v2 = Vector4f(4, 5, 6, 1);

    std::cout << "Prod: " << v1.normalized() << std::endl;
}