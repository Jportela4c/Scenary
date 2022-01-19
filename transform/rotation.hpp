#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

Matrix4f rotateX(float theta);
Matrix4f rotateY(float theta);
Matrix4f rotateZ(float theta);
Matrix4f rotate(Vector3f axis, float theta);