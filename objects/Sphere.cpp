#include "Sphere.hpp"

Sphere::Sphere(){};
Sphere::Sphere(float radius, Vertex center, Material mat)
{
    this->radius = radius;
    this->center = center;
    this->mat = mat;
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
        else
        {
            Vertex intersection1 = (rayOrigin + rayDirection * t1);
            Vertex intersection2 = (rayOrigin + rayDirection * t2);
            float distance1 = sqrt(pow(intersection1[0] - rayOrigin[0], 2) + pow(intersection1[1] - rayOrigin[1], 2) + pow(intersection1[2] - rayOrigin[2], 2));
            float distance2 = sqrt(pow(intersection2[0] - rayOrigin[0], 2) + pow(intersection2[1] - rayOrigin[1], 2) + pow(intersection2[2] - rayOrigin[2], 2));
            Vertex intersection = (distance1 < distance2) ? intersection1 : intersection2;
            intersection[3] = 1;
            return intersection;
        }
    }
};

Vertex Sphere::normal(Vertex point)
{
    Vertex normal = (point - this->center).normalized();
    return normal;
};
