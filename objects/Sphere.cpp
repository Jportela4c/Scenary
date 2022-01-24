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
