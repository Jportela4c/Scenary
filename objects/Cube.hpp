#include <eigen3/Eigen/Dense>
#include "Aux.hpp"

class Cube {
    Cube();
    Cube(float side, Vertex  center);
    float s;
    Vertex c;
    Vertex v1;
    Vertex v2;
    Vertex v3;
    Vertex v4;
    Vertex v5;
    Vertex v6;
    Vertex v7;
    Vertex v8;
    Vertex vertices[8];
    Face faces[12];
    void applyTransform(const Eigen::Matrix4f &transform);
};