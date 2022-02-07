#include "Sphere.hpp"

Sphere::Sphere(){};
Sphere::Sphere(float radius, Point center, Material mat)
{
    this->radius = radius;
    this->center = center;
    this->mat = mat;
};

//Utilizar Vertex
void Sphere::applyTransform(Matrix transform)
{
    this->center = transform * this->center;
}
//Utilizar Vertex
void Sphere::setCameraCoordinates(Matrix worldToCamera)
{
    this->center = worldToCamera * this->center;
}
//Utilizar Vertex
void Sphere::setWorldCoordinates(Matrix cameraToWorld)
{
    this->center = cameraToWorld * this->center;
}

Point Sphere::rayIntersect(Point rayOrigin, Point rayDirection)
{
    Point rayOriginToCenter = this->center - rayOrigin;
    float a = rayDirection.dot(rayDirection);
    float b = rayDirection.dot(rayOriginToCenter);
    float c = rayOriginToCenter.dot(rayOriginToCenter) - this->radius * this->radius;
    float delta = b * b - a * c;
    if (delta < 0)
    {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
    else
    {
        float t1 = (-b - (sqrt(delta) / a));
        float t2 = (-b + (sqrt(delta) /a));
        if (t1 == t2)
        {
            Point intersection = (rayOrigin + rayDirection * t1);
            return intersection;
        }
        else
        {
            Point intersection1 = (rayOrigin + rayDirection * t1);
            Point intersection2 = (rayOrigin + rayDirection * t2);
            float distance1 = sqrt(pow(intersection1[0] - rayOrigin[0], 2) + pow(intersection1[1] - rayOrigin[1], 2) + pow(intersection1[2] - rayOrigin[2], 2));
            float distance2 = sqrt(pow(intersection2[0] - rayOrigin[0], 2) + pow(intersection2[1] - rayOrigin[1], 2) + pow(intersection2[2] - rayOrigin[2], 2));
            Point intersection = (distance1 < distance2) ? intersection1 : intersection2;
            return intersection;
        }
    }
};

Point Sphere::normal(Point point)
{
    Point normal = (point - this->center).normalized();
    return normal;
};
