#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

//Returns a scaling matrix

Matrix4f scaling(float sx, float sy, float sz) {
    Matrix4f scale;
    scale << sx, 0, 0, 0,
            0, sy, 0, 0,
            0, 0, sz, 0,
            0, 0, 0, 1;
    return scale;
}