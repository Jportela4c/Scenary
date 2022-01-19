#include "mirroring.hpp"

// Returns a mirroring matrix over the YZ plane

Matrix4f mirrorX() {
    Matrix4f mirror;
    mirror << -1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;
    return mirror;
}

//Returns a mirroring matrix over the XZ plane

Matrix4f mirrorY() {
    Matrix4f mirror;
    mirror << 1, 0, 0, 0,
            0, -1, 0, 0,
            0, 0, 1, 0,
            0, 0, 0, 1;
    return mirror;
}

//Returns a mirroring matrix over the YX plane

Matrix4f mirrorZ(){
    Matrix4f mirror;
    mirror << 1, 0, 0, 0,
            0, 1, 0, 0,
            0, 0, -1, 0,
            0, 0, 0, 1;
    return mirror;
}

//Returns a mirroring matrix over an arbitrary plane

Matrix4f mirror(float a, float b, float c, float d)
{
    Matrix4f mirror;
    mirror << 1 - 2*a*a, -2*a*b, -2*a*c, -2*a*d,
            -2*a*b, 1 - 2*b*b, -2*b*c, -2*b*d,
            -2*a*c, -2*b*c, 1 - 2*c*c, -2*c*d,
            -2*a*d, -2*b*d, -2*c*d, 1 - 2*d*d;
    return mirror;
}