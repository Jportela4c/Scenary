#include <eigen3/Eigen/Dense>
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <limits>

#define HEIGHT 500
#define WIDTH 500
#define BG Point(0, 0, 0)


using namespace std;

typedef Eigen::Vector3f Point;
typedef Eigen::Vector4f Vertex;
typedef Eigen::Matrix4f Matrix;
typedef Eigen::Matrix<Point, HEIGHT, WIDTH> Grid;

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

class Shape
{
    public:
        Material mat;
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
        Vertex rayIntercect(Vertex rayOrigin, Vertex rayDirection);
        Vertex normal(Vertex point);
        Vertex Bounds();
        Shape();
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
    Vertex getNormal();
};

class Cluster
{
    public:
    vector<Shape> shapes;
};