#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

Matrix4f translate(float t_x, float t_y, float t_z)
{
    Matrix4f T;
    T << 1, 0, 0, t_x,
         0, 1, 0, t_y,
         0, 0, 1, t_z,
         0, 0, 0, 1;
    return T;
}