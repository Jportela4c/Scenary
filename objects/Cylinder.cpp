#include "Cylinder.hpp"

Cylinder::Cylinder(){};
Cylinder::Cylinder(float radius, float height, Vertex center_base, Vertex axis, Material mat)
{
    this->radius = radius;
    this->height = height;
    this->center_base = center_base;
    this->center_top = center_base + axis * height;
    this->axis = axis;
    this->mat = mat;
};

void Cylinder::applyTransform(Matrix transform)
{
    this->center_base = transform * this->center_base;
    this->axis = transform * this->axis;
};

void Cylinder::setCameraCoordinates(Matrix worldToCamera)
{
    this->center_base = worldToCamera * this->center_base;
    this->axis = worldToCamera * this->axis;
};

void Cylinder::setWorldCoordinates(Matrix cameraToWorld)
{
    this->center_base = cameraToWorld * this->center_base;
    this->axis = cameraToWorld * this->axis;
};

Vertex Cylinder::planeIntersectBase(Vertex rayOrigin, Vertex rayDirection)
{
    Vertex v = this->center_base - rayOrigin;
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

Vertex Cylinder::planeIntersectTop(Vertex rayOrigin, Vertex rayDirection)
{
    Vertex v = this->center_top - rayOrigin;
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

//double check
Vertex Cylinder::rayIntersect(Vertex rayOrigin, Vertex rayDirection)
{

    Vertex intersection_top = planeIntersectTop(rayOrigin, rayDirection);
    Vertex intersection_base = planeIntersectBase(rayOrigin, rayDirection);

    Vertex v = (rayOrigin - this->center_base) - (rayOrigin - this->center_base).dot(this->axis) * this->axis;
    Vertex w = rayDirection - rayDirection.dot(this->axis) * this->axis;

    float a = w.dot(w);
    float b = w.dot(v);
    float c = v.dot(v) - this->radius * this->radius;

    float delta  = b*b - a*c;

    if (delta < 0){
        if(intersection_base[3] == -1 && intersection_top[3] == -1){
            return Vertex(0, 0, 0, -1);
        }
        else if(intersection_base[3] == -1){
            return intersection_top;
        }
        else if(intersection_top[3] == -1){
            return intersection_base;
        }
        else{
            return Vertex(0, 0, 0, -1);
        }
    }
    else{

        //Base intersections
        float distance1,distance2;
        float distanceC1,distanceC2;
        distanceC1 = MAXFLOAT;
        distanceC2 = MAXFLOAT;
        distance1 = MAXFLOAT;
        distance2 = MAXFLOAT;
        if (intersection_base[3] != -1)
        {
            distance1 = sqrt(pow(intersection_base[0] - rayOrigin[0], 2) + pow(intersection_base[1] - rayOrigin[1], 2) + pow(intersection_base[2] - rayOrigin[2], 2));
            distanceC1 = sqrt(pow(intersection_base[0] - this->center_base[0], 2) + pow(intersection_base[1] - this->center_base[1], 2) + pow(intersection_base[2] - this->center_base[2], 2));
        }
        if (intersection_top[3] != -1)
        {
            distance2 = sqrt(pow(intersection_top[0] - rayOrigin[0], 2) + pow(intersection_top[1] - rayOrigin[1], 2) + pow(intersection_top[2] - rayOrigin[2], 2));
            distanceC2 = sqrt(pow(intersection_top[0] - this->center_top[0], 2) + pow(intersection_top[1] - this->center_top[1], 2) + pow(intersection_top[2] - this->center_top[2], 2));
        }
        Vertex closest_base_intersection = Vertex(0, 0, 0, -1);
        float closest_distanceB = MAXFLOAT;

        if (distanceC1 <= this->radius && distanceC2 <= this->radius)
        {
            closest_base_intersection  = distance1 < distance2 ? intersection_base : intersection_top;
            closest_distanceB = distance1 < distance2 ? distance1 : distance2;
        }
        else if (distanceC1 <= this->radius)
        {
            closest_base_intersection = intersection_base;
            closest_distanceB = distance1;
        }
        else if (distanceC2 <= this->radius)
        {
            closest_base_intersection = intersection_top;
            closest_distanceB = distance2;
        }
        
        float t1 = (-b - sqrt(delta)) / a;
        float t2 = (-b + sqrt(delta)) / a;
        float distance3 = MAXFLOAT;
        float distance4 = MAXFLOAT;

        Vertex intersection1 = rayOrigin + rayDirection * t1;
        float val1 = (intersection1 - this->center_base).dot(this->axis);
        distance3 = sqrt(pow(intersection1[0] - rayOrigin[0], 2) + pow(intersection1[1] - rayOrigin[1], 2) + pow(intersection1[2] - rayOrigin[2], 2));
        
        Vertex intersection2 = rayOrigin + rayDirection * t2;
        float val2 = (intersection2 - this->center_base).dot(this->axis);
        distance4 = sqrt(pow(intersection2[0] - rayOrigin[0], 2) + pow(intersection2[1] - rayOrigin[1], 2) + pow(intersection2[2] - rayOrigin[2], 2));
        
        Vertex closest_cylindrical_intersection;
        float closest_distanceC = MAXFLOAT;
        if ((val1 >= 0 && val1 <= this->height) && (val2 >= 0 && val2 <= this->height))
        {
            closest_cylindrical_intersection = distance3 < distance4 ? intersection1 : intersection2;
            closest_distanceC = distance3 < distance4 ? distance3 : distance4;
        }
        else if(val1 >= 0 && val1 <= this->height)
        {
            closest_cylindrical_intersection =  intersection1;
            closest_distanceC = distance3;
        }
        else if(val2 >= 0 && val2 <= this->height)
        {
            closest_cylindrical_intersection =  intersection2;
            closest_distanceC = distance4;
        }
        else
        {
            return closest_base_intersection;
        }
        Vertex closest_intersection;
        closest_intersection = closest_distanceB < closest_distanceC ? closest_base_intersection : closest_cylindrical_intersection;

        return closest_intersection;
    }
};

Vertex Cylinder::normal(Vertex point)
{
    Vertex pointToCenter = point - this->center_base;
    float val = pointToCenter.dot(this->axis);
    Vertex a = this->axis * val;

    Vertex v = this->center_base + a;
    Vertex normal = point - v;
    normal = normal/this->radius;

    return normal;
}