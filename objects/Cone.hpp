#include "Aux.hpp"

class Cone: public Shape 
{
    public:
        float radius;
        float height;
        float angle;
        Material mat;
        Vertex center;
        Vertex axis;
        Vertex origin;
        Cone();
        Cone(float radius, float height, float angle, Vertex center, Vertex axis, Material mat);
        void applyTransform(Matrix transform);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
        Vertex rayIntersect(Vertex rayOrigin, Vertex rayDirection);
        Vertex planeIntersectBase(Vertex rayOrigin, Vertex rayDirection);
};