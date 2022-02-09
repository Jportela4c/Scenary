#include "Aux.hpp"

class Sphere : public Shape {
public:
    float radius;
    Point center;
    Material mat;
    Sphere();
    Sphere(float radius, Point center, Material mat);
    void applyTransform(Matrix transform);
    void setCameraCoordinates(Matrix worldToCamera);
    void setWorldCoordinates(Matrix cameraToWorld);
    Point rayIntersect(Point rayOrigin, Point rayDirection);
    Point normal(Point point);
    Point* Bounds();
};