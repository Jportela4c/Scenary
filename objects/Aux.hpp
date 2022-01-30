#include <eigen3/Eigen/Dense>
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>

using namespace std;

typedef Eigen::Vector3f Point;
typedef Eigen::Vector4f Vertex;
typedef Eigen::Matrix4f Matrix;

class Shape
{
    public:
        Shape();
};

class Material
{
    public:
        Point ka;
        Point kd;
        Point ks;
        float shininess;
        Material();
        Material(Point ka, Point kd, Point ks, float shininess);
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