#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;
using namespace std;

Matrix4f mirrorX();
Matrix4f mirrorY();
Matrix4f mirrorZ();
Matrix4f mirror(float a, float b, float c, float d);