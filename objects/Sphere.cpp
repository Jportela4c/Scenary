#include "Aux.hpp"
#include "Sphere.hpp"

Sphere::Sphere(){};

Sphere::Sphere(float radius, Vertex center)
{
    this->radius = radius;
    this->center = center;
};

void Sphere::applyTransform(Matrix transform)
{
    this->center = transform * this->center;
}

void Sphere::setCameraCoordinates(Matrix worldToCamera)
{
    this->center = worldToCamera * this->center;
}

void Sphere::setWorldCoordinates(Matrix cameraToWorld)
{
    this->center = cameraToWorld * this->center;
}

Vertex Sphere::rayIntersect(Vertex rayOrigin, Vertex rayDirection)
{
    Vertex rayOriginToCenter = rayOrigin - this->center;
    rayOriginToCenter[3] = 1;
    float a = rayDirection.dot(rayDirection);
    float b = rayDirection.dot(rayOriginToCenter);
    float c = rayOriginToCenter.dot(rayOriginToCenter) - this->radius * this->radius;
    float delta = b * b - a * c;
    if (delta < 0)
    {
        return Vertex(0, 0, 0, -1);
    }
    else
    {
        float t1 = (-b - (sqrt(delta) / a));
        float t2 = (-b + (sqrt(delta) /a));
        if (t1 == t2)
        {
            Vertex intersection = (rayOrigin + rayDirection * t1);
            intersection[3] = 1;
            return intersection;
        }
        //double check
        else
        {
            Vertex intersection = rayOrigin + rayDirection * (t1 < t2 ? t1 : t2);
            intersection[3] = 1;
            return intersection;
        }
    }
}