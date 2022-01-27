#include "Aux.hpp"

class Sphere: public Shape
{
    public:
        float radius;
        Vertex center;
        Sphere();
        Sphere(float radius, Vertex center);
        void applyTransform(Matrix transform);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
        Vertex rayIntersect(Vertex rayOrigin, Vertex rayDirection);
};