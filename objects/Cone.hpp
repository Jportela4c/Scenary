#include "Aux.hpp"

class Cone: public Shape 
{
    public:
        float radius;
        float height;
        float angle;
        Material mat;
        Point center;
        Point axis;
        Point origin;
        Cone();
        Cone(float radius, float height, float angle, Point center, Point axis, Material mat);
        void applyTransform(Matrix transform);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
        Point rayIntersect(Point rayOrigin, Point rayDirection);
        Point planeIntersectBase(Point rayOrigin, Point rayDirection);
        Point normal(Point point);
};