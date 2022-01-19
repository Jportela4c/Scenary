#include "rotation.hpp"

// Returns a rotation matrix over the X axis

Matrix4f rotateX(float theta) {
    Matrix4f rot;
    rot << 1, 0, 0, 0,
           0, cos(theta), -sin(theta), 0,
           0, sin(theta), cos(theta), 0,
           0, 0, 0, 1;
    return rot;
}

//Returns a rotation matrix over the Y axis

Matrix4f rotateY(float theta) {
    Matrix4f rot;
    rot << cos(theta), 0, sin(theta), 0,
           0, 1, 0, 0,
           -sin(theta), 0, cos(theta), 0,
           0, 0, 0, 1;
    return rot;
}

//Returns a rotation matrix over the Z axis

Matrix4f rotateZ(float theta) {
    Matrix4f rot;
    rot << cos(theta), -sin(theta), 0, 0,
           sin(theta), cos(theta), 0, 0,
           0, 0, 1, 0,
           0, 0, 0, 1;
    return rot;
}

//Returns a rotation matrix over an arbitrary axis

Matrix4f rotate(Vector3f axis, float theta) {
    Matrix4f rot;
    float c = cos(theta);
    float s = sin(theta);
    float t = 1 - c;
    float x = axis(0);
    float y = axis(1);
    float z = axis(2);
    rot << t*x*x + c, t*x*y - s*z, t*x*z + s*y, 0,
           t*x*y + s*z, t*y*y + c, t*y*z - s*x, 0,
           t*x*z - s*y, t*y*z + s*x, t*z*z + c, 0,
           0, 0, 0, 1;
    return rot;
}