#include "Aux.hpp"

class Cube : public Shape
{
public:
    Cube();
    Cube(float side, Point  center, Material mat);
    float side;
    Material mat;
    Point center;
    Point v1;
    Point v2;
    Point v3;
    Point v4;
    Point v5;
    Point v6;
    Point v7;
    Point v8;
    Point vertices[8];
    Face faces[12];
    Point normal_intersect;
    void applyTransform(Matrix transform);
    void setCameraCoordinates(Matrix worldToCamera);
    void setWorldCoordinates(Matrix cameraToWorld);
    Point rayIntersect(Point rayOrigin, Point rayDirection);
    void setNormal(Point intersect);
    Point normal(Point point);
    Point Bounds();
    void updateFaces();
};
