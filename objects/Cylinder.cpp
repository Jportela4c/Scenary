#include "Cylinder.hpp"

Cylinder::Cylinder(){};
Cylinder::Cylinder(float radius, float height, Point center_base, Point axis, Material mat)
{
    this->radius = radius;
    this->height = height;
    this->center_base = center_base;
    this->center_top = center_base + axis * height;
    this->axis = axis;
    this->mat = mat;
};

/*Adicionar VERTEX*/
void Cylinder::applyTransform(Matrix transform)
{
    Vertex cb = Vertex(this->center_base[0], this->center_base[1], this->center_base[2], 1);
    cb = transform * cb;
    this->center_base = Point(cb[0], cb[1], cb[2]);

    Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    axisv = transform * axisv;

    this->axis = Point(axisv[0], axisv[1], axisv[2]);
    this->center_top = this->center_base + this->axis * this->height;
};
/*Adicionar VERTEX*/
void Cylinder::setCameraCoordinates(Matrix worldToCamera)
{
    Vertex cb = Vertex(this->center_base[0], this->center_base[1], this->center_base[2], 1);
    cb = worldToCamera * cb;
    this->center_base = Point(cb[0], cb[1], cb[2]);

    Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    axisv = worldToCamera * axisv;

    this->axis = Point(axisv[0], axisv[1], axisv[2]);
    this->center_top = this->center_base + this->axis * this->height;
};
/*Adicionar VERTEX*/
void Cylinder::setWorldCoordinates(Matrix cameraToWorld)
{
    Vertex cb = Vertex(this->center_base[0], this->center_base[1], this->center_base[2], 1);
    cb = cameraToWorld * cb;
    this->center_base = Point(cb[0], cb[1], cb[2]);

    Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    axisv = cameraToWorld * axisv;

    this->axis = Point(axisv[0], axisv[1], axisv[2]);
    this->center_top = this->center_base + this->axis * this->height;
};

Point Cylinder::planeIntersectBase(Point rayOrigin, Point rayDirection)
{
    Point v = this->center_base - rayOrigin;
    float p = this->axis.dot(v);
    float t = this->axis.dot(rayDirection);

    if (t == 0)
    {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
    else
    {
        float s = p / t;
        Point intersection = rayOrigin + rayDirection * s;
        return intersection;
    }
};

Point Cylinder::planeIntersectTop(Point rayOrigin, Point rayDirection)
{
    Point v = this->center_top - rayOrigin;
    float p = this->axis.dot(v);
    float t = this->axis.dot(rayDirection);

    if (t == 0)
    {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
    else
    {
        float s = p / t;
        Point intersection = rayOrigin + rayDirection * s;

        return intersection;
    }
};

//double check
// Point Cylinder::rayIntersect(Point rayOrigin, Point rayDirection)
// {

//     Point intersection_top = planeIntersectTop(rayOrigin, rayDirection);
//     Point intersection_base = planeIntersectBase(rayOrigin, rayDirection);

//     Point v = (rayOrigin - this->center_base) - (rayOrigin - this->center_base).dot(this->axis) * this->axis;
//     Point w = rayDirection.normalized() - (rayDirection.normalized()).dot(this->axis) * this->axis;

//     float a = w.dot(w);
//     float b = w.dot(v);
//     float c = v.dot(v) - this->radius * this->radius;

//     float delta  = b*b - a*c;

//     if (delta < 0){
//         if(!(intersection_base[0] < MAXFLOAT) && !(intersection_top[0] < MAXFLOAT)){
//             return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
//         }
//         else if(intersection_base[0] < MAXFLOAT){
//             return intersection_top;
//         }
//         else if(intersection_top[0] < MAXFLOAT){
//             return intersection_base;
//         }
//         else{
//             return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
//         }
//     }
//     else{

//         //Base intersections
//         float distance1,distance2;
//         float distanceC1,distanceC2;
//         distanceC1 = MAXFLOAT;
//         distanceC2 = MAXFLOAT;
//         distance1 = MAXFLOAT;
//         distance2 = MAXFLOAT;
//         if (intersection_base[0] < MAXFLOAT)
//         {
//             distance1 = sqrt(pow(intersection_base[0] - rayOrigin[0], 2) + pow(intersection_base[1] - rayOrigin[1], 2) + pow(intersection_base[2] - rayOrigin[2], 2));
//             distanceC1 = sqrt(pow(intersection_base[0] - this->center_base[0], 2) + pow(intersection_base[1] - this->center_base[1], 2) + pow(intersection_base[2] - this->center_base[2], 2));
//         }
//         if (intersection_top[0] < MAXFLOAT)
//         {
//             distance2 = sqrt(pow(intersection_top[0] - rayOrigin[0], 2) + pow(intersection_top[1] - rayOrigin[1], 2) + pow(intersection_top[2] - rayOrigin[2], 2));
//             distanceC2 = sqrt(pow(intersection_top[0] - this->center_top[0], 2) + pow(intersection_top[1] - this->center_top[1], 2) + pow(intersection_top[2] - this->center_top[2], 2));
//         }
//         Point closest_base_intersection = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
//         float closest_distanceB = MAXFLOAT;

//         if (distanceC1 <= this->radius && distanceC2 <= this->radius)
//         {
//             closest_base_intersection  = distance1 < distance2 ? intersection_base : intersection_top;
//             closest_distanceB = distance1 < distance2 ? distance1 : distance2;
//         }
//         else if (distanceC1 <= this->radius)
//         {
//             closest_base_intersection = intersection_base;
//             closest_distanceB = distance1;
//         }
//         else if (distanceC2 <= this->radius)
//         {
//             closest_base_intersection = intersection_top;
//             closest_distanceB = distance2;
//         }
        
//         float t1 = (-b - sqrt(delta)) / a;
//         float t2 = (-b + sqrt(delta)) / a;
//         float distance3 = MAXFLOAT;
//         float distance4 = MAXFLOAT;

//         Point intersection1 = rayOrigin + rayDirection.normalized() * t1;
//         float val1 = (intersection1 - this->center_base).dot(this->axis);
//         distance3 = sqrt(pow(intersection1[0] - rayOrigin[0], 2) + pow(intersection1[1] - rayOrigin[1], 2) + pow(intersection1[2] - rayOrigin[2], 2));
        
//         Point intersection2 = rayOrigin + rayDirection.normalized() * t2;
//         float val2 = (intersection2 - this->center_base).dot(this->axis);
//         distance4 = sqrt(pow(intersection2[0] - rayOrigin[0], 2) + pow(intersection2[1] - rayOrigin[1], 2) + pow(intersection2[2] - rayOrigin[2], 2));
        
//         Point closest_cylindrical_intersection;
//         float closest_distanceC = MAXFLOAT;
//         if ((val1 >= 0 && val1 <= this->height) && (val2 >= 0 && val2 <= this->height))
//         {
//             closest_cylindrical_intersection = distance3 < distance4 ? intersection1 : intersection2;
//             closest_distanceC = distance3 < distance4 ? distance3 : distance4;
//         }
//         else if(val1 >= 0 && val1 <= this->height)
//         {
//             closest_cylindrical_intersection =  intersection1;
//             closest_distanceC = distance3;
//         }
//         else if(val2 >= 0 && val2 <= this->height)
//         {
//             closest_cylindrical_intersection =  intersection2;
//             closest_distanceC = distance4;
//         }
//         else
//         {
//             return closest_base_intersection;
//         }
//         Point closest_intersection;
//         closest_intersection = closest_distanceB < closest_distanceC ? closest_base_intersection : closest_cylindrical_intersection;

//         return closest_intersection;
//     }
// };

bool Cylinder::validate(Point p)
{
    Point pb = p - this->center_base;
    float pi = pb.dot(this->axis);

    return (0 <= pi && pi <= this->height);
}

Point Cylinder::rayIntersect(Point rayOrigin, Point rayDirection)
{
    Point rayDirectionN = rayDirection.normalized();

    Point pi_c = rayOrigin - this->center_base;

    Point v = pi_c - (this->axis * (pi_c.dot(this->axis)));

    Point w = rayDirectionN - (rayDirectionN.dot(this->axis)) * this->axis;

    float a = w.dot(w);

    float b = v.dot(w);

    float c = v.dot(v) - this->radius * this->radius;

    float delta  = b*b - a*c;

    if(delta < 0) {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }

    float t1, t2;
    float closest_distance = MAXFLOAT;

    Point int_base = planeIntersectBase(rayOrigin, rayDirection);
    if (int_base[0] < MAXFLOAT){
        float d = sqrt(pow(int_base[0] - this->center_base[0], 2) + pow(int_base[1] - this->center_base[1], 2) + pow(int_base[2] - this->center_base[2], 2));
        if (d > this->radius)
        {
            int_base = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
        }
        else
        {
            closest_distance = sqrt(pow(int_base[0] - rayOrigin[0], 2) + pow(int_base[1] - rayOrigin[1], 2) + pow(int_base[2] - rayOrigin[2], 2));
        }
    }

    Point int_top = planeIntersectTop(rayOrigin, rayDirection);
    float d = sqrt(pow(int_top[0] - this->center_top[0], 2) + pow(int_top[1] - this->center_top[1], 2) + pow(int_top[2] - this->center_top[2], 2));
    if(int_top[0] < MAXFLOAT && d <= this->radius){
        float dist = sqrt(pow(rayOrigin[0] - int_top[0], 2) + pow(rayOrigin[1] - int_top[1], 2) + pow(rayOrigin[2] - int_top[2], 2));
        if (!(int_base[0] < MAXFLOAT) || dist < closest_distance)
        {
            closest_distance = dist;
            int_base = int_top;
        }
    }

    float t1 = -b + sqrt(delta) / a;
    float t2 = -b - sqrt(delta) / a;

    Point int_cyl1 = rayOrigin + rayDirectionN.normalized() * t1;
    Point int_cyl2 = rayOrigin + rayDirectionN.normalized() * t2;

    if(validate(int_cyl1))
    {
        float dist = sqrt(pow(rayOrigin[0] - int_cyl1[0], 2) + pow(rayOrigin[1] - int_cyl1[1], 2) + pow(rayOrigin[2] - int_cyl1[2], 2));
        if (dist < closest_distance)
        {
            closest_distance = dist;
            int_base = int_cyl1;
        }
    }

    if(validate(int_cyl2))
    {
        float dist = sqrt(pow(rayOrigin[0] - int_cyl2[0], 2) + pow(rayOrigin[1] - int_cyl2[1], 2) + pow(rayOrigin[2] - int_cyl2[2], 2));
        if (dist < closest_distance)
        {
            closest_distance = dist;
            int_base = int_cyl2;
        }
    }
    return int_base;
}


Point Cylinder::normal(Point point)
{
    Point pointToCenter = point - this->center_base;
    float val = pointToCenter.dot(this->axis);
    Point a = this->axis * val;

    Point v = this->center_base + a;
    Point normal = point - v;
    normal = normal/this->radius;

    return normal;
}
