#include "Aux.hpp"

class Cube: public Shape
{
    public:
        Cube();
        Cube(float side, Vertex  center, Material mat);
        float s;
        Material mat;
        Vertex c;
        Vertex v1;
        Vertex v2;
        Vertex v3;
        Vertex v4;
        Vertex v5;
        Vertex v6;
        Vertex v7;
        Vertex v8;
        Vertex vertices[8];
        Face faces[12];
        Vertex normal_intersect;
        void applyTransform(Matrix transform);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
        Vertex rayIntersect(Vertex rayOrigin, Vertex rayDirection);
        void setNormal(Vertex intersect);
        Vertex normal(Vertex point);
        Vertex Bounds();
};
