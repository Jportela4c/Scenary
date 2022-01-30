#include "Aux.hpp"

class Cylinder : public Shape
{
    public:
        float radius;
        float height;
        Material mat;
        Vertex center_base;
        Vertex center_top;
        Vertex axis;
        Cylinder();
        Cylinder(float radius, float height, Vertex center_base, Vertex axis, Material mat);
        void applyTransform(Matrix transform);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
        Vertex rayIntersect(Vertex rayOrigin, Vertex rayDirection);
        Vertex planeIntersectBase(Vertex rayOrigin, Vertex rayDirection);
        Vertex planeIntersectTop(Vertex rayOrigin, Vertex rayDirection);
};