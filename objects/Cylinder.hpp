#include "Aux.hpp"

class Cylinder : public Shape
{
    public:
        float radius;
        float height;
        Material mat;
        Point center_base;
        Point center_top;
        Point axis;
        Cylinder();
        Cylinder(float radius, float height, Point center_base, Point axis, Material mat);
        void applyTransform(Matrix transform);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
        Point rayIntersect(Point rayOrigin, Point rayDirection);
        Point planeIntersectBase(Point rayOrigin, Point rayDirection);
        Point planeIntersectTop(Point rayOrigin, Point rayDirection);
        Point normal(Point point);
        bool validate(Point p);
        Point* Bounds();
};