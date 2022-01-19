#include "shearing.hpp"

//Returns a shearing matrix on the XZ plane in X direction

Matrix4f shearingXZtoX(float gamma)
{
    Matrix4f shear;
    shear << 1, tan(gamma), 0, 0,
             0, 1, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 1;
}

//Returns a shearing matrix on the XZ plane in Y direction

Matrix4f sheringXZtoY(float gamma)
{
    Matrix4f shear;
    shear << 1, 0, 0, 0,
             tan(gamma), 1, 0, 0,
             0, 0, 1, 0,
             0, 0, 0, 1;
}

//Returns a shearing matrix on the XZ plane in Z direction

Matrix4f shearingXZtoZ(float gamma)
{
    Matrix4f shear;
    shear << 1, 0, 0, 0,
             0, 1, 0, 0,
             0, tan(gamma), 1, 0,
             0, 0, 0, 1;
}

Matrix4f shearing(float gamma)
{
    Matrix4f shear;
    shear << 1, 0, 0, 0,
             0, 1, tan(gamma), 0,
             0, 0, 1, 0,
             0, 0, 0, 1;
}