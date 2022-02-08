#include <eigen3/Eigen/Dense>
#include <iostream>
#include <cmath>
#include <vector>
#include <numeric>
#include <limits>

#define HEIGHT 500
#define WIDTH 500
#define BG Point(0, 0, 0)

#define MAXFLOAT 1000000.f

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
    virtual void setCameraCoordinates(Matrix worldToCamera) = 0;
    virtual void setWorldCoordinates(Matrix cameraToWorld) = 0;
    virtual Point rayIntersect(Point rayOrigin, Point rayDirection) = 0;
    virtual Point normal(Point point) = 0;
    virtual Point Bounds() = 0;
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