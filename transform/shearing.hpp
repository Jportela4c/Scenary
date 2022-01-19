#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

Matrix4f shearingXZtoX(float gamma);
Matrix4f sheringXZtoY(float gamma);
Matrix4f shearingXZtoZ(float gamma);
Matrix4f shearing(float gamma);