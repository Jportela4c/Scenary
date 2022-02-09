#include "Cone.hpp"

Cone::Cone() {};
Cone::Cone(float radius, float height, Point center, Point axis, Material mat)
{
    this->radius = radius;
    this->height = height;
    this->center = center;
    this->axis = axis;
    this->origin = center + axis * height;
    this->mat = mat;
};

//Utilizar Vertex
void Cone::applyTransform(Matrix transform)
{
    Vertex cb = Vertex(this->center[0], this->center[1], this->center[2], 1);
    cb = transform * cb;
    this->center = Point(cb[0], cb[1], cb[2]);

    Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    axisv = transform * axisv;

    this->origin = this->center + this->axis * this->height;
};
//Utilizar Vertex
void Cone::setCameraCoordinates(Matrix worldToCamera)
{
    Vertex cb = Vertex(this->center[0], this->center[1], this->center[2], 1);
    cb = worldToCamera * cb;
    this->center = Point(cb[0], cb[1], cb[2]);

    Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    axisv = worldToCamera * axisv;

    this->origin = this->center + this->axis * this->height;
};
//Utilizar Vertex
void Cone::setWorldCoordinates(Matrix cameraToWorld)
{
    Vertex cb = Vertex(this->center[0], this->center[1], this->center[2], 1);
    cb = cameraToWorld * cb;
    this->center = Point(cb[0], cb[1], cb[2]);

    Vertex axisv = Vertex(this->axis[0], this->axis[1], this->axis[2], 1);
    axisv = cameraToWorld * axisv;

    this->origin = this->center + this->axis * this->height;
};

Point Cone::planeIntersectBase(Point rayOrigin, Point rayDirection)
{
    Point v = this->center - rayOrigin;
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
        intersection[3] = 1;
        return intersection;
    }
};

// Point Cone::rayIntersect(Point rayOrigin, Point rayDirection)
// {
//     Point base_intersection = this->planeIntersectBase(rayOrigin, rayDirection);
//     float distance_base_intersection  = sqrt(pow(base_intersection[0] - rayOrigin[0], 2) + pow(base_intersection[1] - rayOrigin[1], 2) + pow(base_intersection[2] - rayOrigin[2], 2));

//     Point v = this->origin - rayOrigin;

//     float a = pow(rayDirection.dot(this->axis), 2) - rayDirection.dot(rayDirection) * pow(cos(this->angle), 2);
//     float b = v.dot(rayDirection) * pow(cos(this->angle), 2) - v.dot(this->axis) * rayDirection.dot(this->axis);
//     float c = pow(v.dot(this->axis), 2) - v.dot(v) * pow(cos(this->angle), 2);

//     float delta = pow(b, 2) - a * c;

//     if(base_intersection[1] < MAXFLOAT)
//     {
//         if (delta < 0)
//         {
//             return base_intersection;
//         }
//         else
//         {
//             float s1 = a != 0 ? (-b + sqrt(delta)) / a : -c / 2*b;
//             float s2 = a != 0 ? (-b + sqrt(delta)) / a : -c / 2*b;

//             if (s1 == s2)
//             {
//                 Point cone_intersection = rayOrigin + rayDirection * s1;
//                 float val = (this->origin - cone_intersection).dot(this->axis);
//                 float distance_cone_intersection = sqrt(pow(cone_intersection[0] - rayOrigin[0], 2) + pow(cone_intersection[1] - rayOrigin[1], 2) + pow(cone_intersection[2] - rayOrigin[2], 2));
//                 if ((this->height >= val) && (val >= 0))
//                 {
//                     Point intersection = distance_base_intersection < distance_cone_intersection ? base_intersection : cone_intersection;
//                     return intersection;
//                 }
//                 else
//                 {
//                     return base_intersection;
//                 }
//             }
//             else
//             {
//                 Point cone_intersection1 = rayOrigin + rayDirection * s1;
//                 Point cone_intersection2 = rayOrigin + rayDirection * s2;
//                 float val1 = (this->origin - cone_intersection1).dot(this->axis);
//                 float val2 = (this->origin - cone_intersection2).dot(this->axis);
//                 float distance_cone_intersection1 = sqrt(pow(cone_intersection1[0] - rayOrigin[0], 2) + pow(cone_intersection1[1] - rayOrigin[1], 2) + pow(cone_intersection1[2] - rayOrigin[2], 2));
//                 float distance_cone_intersection2 = sqrt(pow(cone_intersection2[0] - rayOrigin[0], 2) + pow(cone_intersection2[1] - rayOrigin[1], 2) + pow(cone_intersection2[2] - rayOrigin[2], 2));
//                 if (this->height >= val1 >= 0 && this->height >= val2 >= 0)
//                 {
//                     float distance_cone_intersection = distance_cone_intersection1 < distance_cone_intersection2 ? distance_cone_intersection1 : distance_cone_intersection2;
//                     Point cone_intersection = distance_cone_intersection1 < distance_cone_intersection2 ? cone_intersection1 : cone_intersection2;
//                     Point intersection = distance_base_intersection < distance_cone_intersection ? base_intersection : cone_intersection;
//                     return intersection;
//                 }
//                 else if (this->height >= val1 >= 0)
//                 {
//                     Point intersection = distance_base_intersection < distance_cone_intersection1 ? base_intersection : cone_intersection1;
//                     return intersection;
//                 }
//                 else if (this->height >= val2 >= 0)
//                 {
//                     Point intersection = distance_base_intersection < distance_cone_intersection2 ? base_intersection : cone_intersection2;
//                     return intersection;
//                 }
//                 else
//                 {
//                     return base_intersection;
//                 }
//             }
//         }
//     }
//     else
//         {
//             if (delta < 0)
//             {
//                 return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
//             }
//             else
//             {
//                 float s1 = a != 0 ? (-b + sqrt(delta)) / a : -c / 2*b;
//                 float s2 = a != 0 ? (-b + sqrt(delta)) / a : -c / 2*b;
//                 if (s1 == s2)
//                 {
//                     Point cone_intersection = rayOrigin + rayDirection * s1;
//                     float val = (this->origin - cone_intersection).dot(this->axis);
//                     float distance_cone_intersection = sqrt(pow(cone_intersection[0] - rayOrigin[0], 2) + pow(cone_intersection[1] - rayOrigin[1], 2) + pow(cone_intersection[2] - rayOrigin[2], 2));
//                     if (this->height >= val >= 0)
//                     {
//                         return cone_intersection;
//                     }
//                     else
//                     {
//                         return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
//                     }
//                 }
//                 else
//                 {
//                     Point cone_intersection1 = rayOrigin + rayDirection * s1;
//                     Point cone_intersection2 = rayOrigin + rayDirection * s2;
//                     float val1 = (this->origin - cone_intersection1).dot(this->axis);
//                     float val2 = (this->origin - cone_intersection2).dot(this->axis);
//                     float distance_cone_intersection1 = sqrt(pow(cone_intersection1[0] - rayOrigin[0], 2) + pow(cone_intersection1[1] - rayOrigin[1], 2) + pow(cone_intersection1[2] - rayOrigin[2], 2));
//                     float distance_cone_intersection2 = sqrt(pow(cone_intersection2[0] - rayOrigin[0], 2) + pow(cone_intersection2[1] - rayOrigin[1], 2) + pow(cone_intersection2[2] - rayOrigin[2], 2));
//                     if (this->height >= val1 >= 0 && this->height >= val2 >= 0)
//                     {
//                         Point cone_intersection = distance_cone_intersection1 < distance_cone_intersection2 ? cone_intersection1 : cone_intersection2;
//                         return cone_intersection;
//                     }
//                     else if (this->height >= val1 >= 0)
//                     {
//                         return cone_intersection1;
//                     }
//                     else if (this->height >= val2 >= 0)
//                     {
//                         return cone_intersection2;
//                     }
//                     else
//                     {
//                         return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
//                     }
//                 }
//             }
//         }
// };

bool Cone::validate(Point p, Point ray)
{
    Point aux = p - ray;
    float s = aux.dot(this->axis);

    return ((s >= 0) && (s <= this->height));
}

Point Cone::base_intesection(Point rayOrigin, Point rayDirection)
{
    Point v = this->center - rayOrigin;
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

        float d = sqrt(pow(intersection[0] - this->center[0], 2) + pow(intersection[1] - this->center[1], 2) + pow(intersection[2] - this->center[2], 2));

        if (d <= this->radius)
        {
            return intersection;
        }
        else
        {
            return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
        }
    }
};

Point Cone::rayIntersect(Point rayOrigin, Point rayDirection)
{
    float cos_theta = this->height / sqrt(pow(this->height, 2) + pow(this->radius, 2));

    Point normal_aux = this->axis * this->height;

    Point vertex = this->center + normal_aux;

    Point d = rayDirection.normalized();

    Point v = vertex - rayOrigin;

    float a = pow(d.dot(this->axis), 2) - (d.dot(d) * pow(cos_theta, 2));

    float b = d.dot(v) * pow(cos_theta, 2) - ((d.dot(this->axis) * v.dot(this->axis)));

    float c = pow(v.dot(this->axis), 2) - (pow(cos_theta, 2) * v.dot(v));

    float delta = b*b - (a * c);

    float t1, t2;
    Point pi = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);

    if (delta > 0)
    {
        if (a != 0)
        {
            t1 = (-b + sqrt(delta)) / a;
            t2 = (-b - sqrt(delta)) / a;
        }
        else
        {
            t1 = -c / (2 * b);
            t2 = -c / (2 * b);
        }

        Point p1 = rayOrigin + d * t1;
        Point p2 = rayOrigin + d * t2;

        Point bi = base_intesection(rayOrigin, d);
        if (validate(this->origin, p1))
        {
            pi = p1;
        }
        else if (bi[0] < MAXFLOAT)
        {
            pi = bi;
        }

        float d1 = MAXFLOAT;
        if (pi[0] < MAXFLOAT)
        {
            d1 = sqrt(pow(pi[0] - rayOrigin[0], 2) + pow(pi[1] - rayOrigin[1], 2) + pow(pi[2] - rayOrigin[2], 2));
        }

        float d2 = sqrt(pow(p2[0] - rayOrigin[0], 2) + pow(p2[1] - rayOrigin[1], 2) + pow(p2[2] - rayOrigin[2], 2));
        if (validate(this->origin, p2))
        {
            if (!(pi[0] < MAXFLOAT) || d2 < d1)
            {
                pi = p2;
            }

        }
        else if (bi[0] < MAXFLOAT)
        {
            pi = bi;
        }
    }
    else if (delta == 0 && b != 0 && a != 0)
    {
        t1 = -b + sqrt(delta) / a;
        Point p1 = rayOrigin + d * t1;
        Point bi = base_intesection(rayOrigin, d);
        float db = sqrt(pow(bi[0] - rayOrigin[0], 2) + pow(bi[1] - rayOrigin[1], 2) + pow(bi[2] - rayOrigin[2], 2));
        float dp = sqrt(pow(p1[0] - rayOrigin[0], 2) + pow(p1[1] - rayOrigin[1], 2) + pow(p1[2] - rayOrigin[2], 2));
        if (validate(this->origin, p1))
        {
            pi = p1;
        }
        else if (bi[0] < MAXFLOAT && (!(pi[0] < MAXFLOAT) || db < dp))
        {
            pi = bi;
        }
    }
    return pi;
};



Point Cone::normal(Point point)
{
    Point v = this->height * this->axis;
    Point n = this->center + v;
    Point a = point - this->center;

    float f = a.dot(this->axis);
    Point p = this->center + f * this->axis;

    Point a2 = point - p;
    Point a3 = n - point;

    Point T = a2.cross(a3);
    Point N = (a3.cross(T)).normalized();

    return N;

};

Point* Cone::Bounds()
{
    Point max_bounds = this->center + this->height * this->axis;
    Point min_bounds = this->center - this->height * this->axis;

    Point p = Point (1, 0, 0);

    if (this->axis[1] != 1)
    {
        p = this->axis * Point(0, 1, 0);
    }
    Point p2 = (this->axis).cross(p);

    for (int i = 0; i < 4; i++)
    {
        if(this->center[0] > max_bounds[0])
        {
            max_bounds[0] = this->center[0];
        }
        if(this->center[0] < min_bounds[0])
        {
            min_bounds[0] = this->center[0];
        }
        if(this->center[1] > max_bounds[1])
        {
            max_bounds[1] = this->center[1];
        }
        if(this->center[1] < min_bounds[1])
        {
            min_bounds[1] = this->center[1];
        }
        if(this->center[2] > max_bounds[2])
        {
            max_bounds[2] = this->center[2];
        }
        if(this->center[2] < min_bounds[2])
        {
            min_bounds[2] = this->center[2];
        }

        p = p2;
        p2 = (this->axis).cross(p);
    }

    Point bounds[2] = {min_bounds, max_bounds};

    return bounds;
}