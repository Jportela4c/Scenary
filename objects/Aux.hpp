#include <eigen3/Eigen/Dense>
#include <iostream>
#include <cmath>

typedef Eigen::Vector3f Point;
typedef Eigen::Vector4f Vertex;
typedef Eigen::Matrix4f Matrix;

class Shape
{

};
class Face {
    public:
    Face();
    Face(Vertex v1, Vertex v2, Vertex v3);
    Vertex v1;
    Vertex v2;
    Vertex v1v2;
    Vertex v1v3;
    Vertex v2v3;
    Vertex v3v1;
    Vertex v3;
    Vertex normal;
    Vertex planeIntersection(Vertex rayOrigin, Vertex rayDirection);
    Vertex rayIntersection(Vertex rayOrigin, Vertex rayDirection);
};