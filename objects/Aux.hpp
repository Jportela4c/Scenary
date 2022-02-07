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
        Point rayIntercect(Point rayOrigin, Point rayDirection);
        Point normal(Point point);
        Point Bounds();
        Shape();
};

class Face {
    public:
    Face();
    Face(Point v1, Point v2, Point v3);
    Point v1;
    Point v2;
    Point v1v2;
    Point v1v3;
    Point v2v3;
    Point v3v1;
    Point v3;
    Point normal;
    Point planeIntersection(Point rayOrigin, Point rayDirection);
    Point rayIntersection(Point rayOrigin, Point rayDirection);
    Point getNormal();
};

class Cluster
{
    public:
    vector<Shape> shapes;
};