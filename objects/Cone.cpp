#include "Cone.hpp"

Cone::Cone(){};
Cone::Cone(float radius, float height, float angle, Vertex center, Vertex axis, Material mat)
{
    this->radius = radius;
    this->height = height;
    this->angle = angle;
    this->center = center;
    this->axis = axis;
    this->origin = center + axis * height;
    this->mat = mat;
};

void Cone::applyTransform(Matrix transform)
{
    this->center = transform * this->center;
    this->axis = transform * this->axis;
};

void Cone::setCameraCoordinates(Matrix worldToCamera)
{
    this->center = worldToCamera * this->center;
    this->axis = worldToCamera * this->axis;
};

void Cone::setWorldCoordinates(Matrix cameraToWorld)
{
    this->center = cameraToWorld * this->center;
    this->axis = cameraToWorld * this->axis;
};

Vertex Cone::planeIntersectBase(Vertex rayOrigin, Vertex rayDirection)
{
    Vertex v = this->center - rayOrigin;
    float p = this->axis.dot(v);
    float t = this->axis.dot(rayDirection);

    if (t == 0)
    {
        return Vertex(0, 0, 0, -1);
    }
    else
    {
        float s = p / t;
        Vertex intersection = rayOrigin + rayDirection * s;
        intersection[3] = 1;
        return intersection;
    }
};

Vertex Cone::rayIntersect(Vertex rayOrigin, Vertex rayDirection)
{
    Vertex base_intersection = this->planeIntersectBase(rayOrigin, rayDirection);
    float distance_base_intersection  = sqrt(pow(base_intersection[0] - rayOrigin[0], 2) + pow(base_intersection[1] - rayOrigin[1], 2) + pow(base_intersection[2] - rayOrigin[2], 2));
    
    Vertex v = this->origin - rayOrigin;
    v[3] = 1;
    
    float a = pow(rayDirection.dot(this->axis), 2) - rayDirection.dot(rayDirection) * pow(cos(this->angle), 2);
    float b = v.dot(rayDirection) * pow(cos(this->angle), 2) - v.dot(this->axis) * rayDirection.dot(this->axis);
    float c = pow(v.dot(this->axis), 2) - v.dot(v) * pow(cos(this->angle), 2);

    float delta = pow(b, 2) - a * c;

    if(base_intersection[3] != -1)
    {
        if (delta < 0)
        {
            return base_intersection;
        }
        else
        {
            float s1 = a != 0 ? (-b + sqrt(delta)) / a : -c / 2*b;
            float s2 = a != 0 ? (-b + sqrt(delta)) / a : -c / 2*b;

            if (s1 == s2)
            {
                Vertex cone_intersection = rayOrigin + rayDirection * s1;
                float val = (this->origin - cone_intersection).dot(this->axis);
                float distance_cone_intersection = sqrt(pow(cone_intersection[0] - rayOrigin[0], 2) + pow(cone_intersection[1] - rayOrigin[1], 2) + pow(cone_intersection[2] - rayOrigin[2], 2));
                if (this->height >= val >= 0)
                {
                    Vertex intersection = distance_base_intersection < distance_cone_intersection ? base_intersection : cone_intersection;
                    intersection[3] = 1;
                    return intersection;
                }
                else
                {
                    base_intersection[3] = 1;
                    return base_intersection;
                }
            }
            else
            {
                Vertex cone_intersection1 = rayOrigin + rayDirection * s1;
                Vertex cone_intersection2 = rayOrigin + rayDirection * s2;
                float val1 = (this->origin - cone_intersection1).dot(this->axis);
                float val2 = (this->origin - cone_intersection2).dot(this->axis);
                float distance_cone_intersection1 = sqrt(pow(cone_intersection1[0] - rayOrigin[0], 2) + pow(cone_intersection1[1] - rayOrigin[1], 2) + pow(cone_intersection1[2] - rayOrigin[2], 2));
                float distance_cone_intersection2 = sqrt(pow(cone_intersection2[0] - rayOrigin[0], 2) + pow(cone_intersection2[1] - rayOrigin[1], 2) + pow(cone_intersection2[2] - rayOrigin[2], 2));
                if (this->height >= val1 >= 0 && this->height >= val2 >= 0)
                {
                    float distance_cone_intersection = distance_cone_intersection1 < distance_cone_intersection2 ? distance_cone_intersection1 : distance_cone_intersection2;
                    Vertex cone_intersection = distance_cone_intersection1 < distance_cone_intersection2 ? cone_intersection1 : cone_intersection2;
                    Vertex intersection = distance_base_intersection < distance_cone_intersection ? base_intersection : cone_intersection;
                    intersection[3] = 1;
                    return intersection;
                }
                else if (this->height >= val1 >= 0)
                {
                    Vertex intersection = distance_base_intersection < distance_cone_intersection1 ? base_intersection : cone_intersection1;
                    intersection[3] = 1;
                    return intersection;
                }
                else if (this->height >= val2 >= 0)
                {
                    Vertex intersection = distance_base_intersection < distance_cone_intersection2 ? base_intersection : cone_intersection2;
                    intersection[3] = 1;
                    return intersection;
                }
                else
                {
                    base_intersection[3] = 1;
                    return base_intersection;
                }
            }
        }
    }
    else
        {
            if (delta < 0)
            {
                return Vertex(0, 0, 0, -1);
            }
            else
            {
                float s1 = a != 0 ? (-b + sqrt(delta)) / a : -c / 2*b;
                float s2 = a != 0 ? (-b + sqrt(delta)) / a : -c / 2*b;
                if (s1 == s2)
                {
                    Vertex cone_intersection = rayOrigin + rayDirection * s1;
                    float val = (this->origin - cone_intersection).dot(this->axis);
                    float distance_cone_intersection = sqrt(pow(cone_intersection[0] - rayOrigin[0], 2) + pow(cone_intersection[1] - rayOrigin[1], 2) + pow(cone_intersection[2] - rayOrigin[2], 2));
                    if (this->height >= val >= 0)
                    {
                        cone_intersection[3] = 1;
                        return cone_intersection;
                    }
                    else
                    {
                        return Vertex(0, 0, 0, -1);
                    }
                }
                else
                {
                    Vertex cone_intersection1 = rayOrigin + rayDirection * s1;
                    Vertex cone_intersection2 = rayOrigin + rayDirection * s2;
                    float val1 = (this->origin - cone_intersection1).dot(this->axis);
                    float val2 = (this->origin - cone_intersection2).dot(this->axis);
                    float distance_cone_intersection1 = sqrt(pow(cone_intersection1[0] - rayOrigin[0], 2) + pow(cone_intersection1[1] - rayOrigin[1], 2) + pow(cone_intersection1[2] - rayOrigin[2], 2));
                    float distance_cone_intersection2 = sqrt(pow(cone_intersection2[0] - rayOrigin[0], 2) + pow(cone_intersection2[1] - rayOrigin[1], 2) + pow(cone_intersection2[2] - rayOrigin[2], 2));
                    if (this->height >= val1 >= 0 && this->height >= val2 >= 0)
                    {
                        Vertex cone_intersection = distance_cone_intersection1 < distance_cone_intersection2 ? cone_intersection1 : cone_intersection2;
                        cone_intersection[3] = 1;
                        return cone_intersection;
                    }
                    else if (this->height >= val1 >= 0)
                    {
                        cone_intersection1[3] = 1;
                        return cone_intersection1;
                    }
                    else if (this->height >= val2 >= 0)
                    {
                        cone_intersection2[3] = 1;
                        return cone_intersection2;
                    }
                    else
                    {
                        return Vertex(0, 0, 0, -1);
                    }
                }
            }
        }
};

Vertex Cone::normal(Vertex point)
{
    Vertex v= this->height * this->axis;
    Vertex n  = this->center + v;
    Vertex a = point - this->center;

    float f = a.dot(this->axis);
    Vertex p = this->center + f * this->axis;

    Vertex a2 = point - p;
    Vertex a3 = n - point;

    Point a2n = Point(a2[0], a2[1], a2[2]);
    Point a3n = Point(a3[0], a3[1], a3[2]);

    Point Tn = a2n.cross(a3n);
    Point Nn = a3n.cross(Tn);

    Vertex N = Vertex(Nn[0], Nn[1], Nn[2], 1.0);

    return N.normalized();

};