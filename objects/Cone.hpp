#include "Aux.hpp"

class Cone : public Shape
{
public:
    float radius;
    float height;
    Material mat;
    Point center;
    Point axis;
    Point origin;
    Cone();
    Cone(float radius, float height, Point center, Point axis, Material mat);
    void applyTransform(Matrix transform);
    void setCameraCoordinates(Matrix worldToCamera);
    void setWorldCoordinates(Matrix cameraToWorld);
    Point rayIntersect(Point rayOrigin, Point rayDirection);
    Point planeIntersectBase(Point rayOrigin, Point rayDirection);
    Point normal(Point point);
    bool validate(Point p, Point ray);
    Point base_intesection(Point rayOrigin, Point rayDirection);
    Point Bounds();
};