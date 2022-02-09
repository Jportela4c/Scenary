#include "Aux.hpp"

Material::Material() {};
Material::Material(Point ka, Point kd, Point ks, float shininess)
{
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->shininess = shininess;
};

//////////////Faces////////////////////

Face::Face() {
    v1 = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    v2 = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    v3 = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
};

Face::Face(Point vertex1, Point vertex2, Point vertex3) {
    this->v1 = vertex1;
    this->v2 = vertex2;
    this->v3 = vertex3;
    this->v1v2 = this->v2 - this->v1;
    this->v1v3 = this->v3 - this->v1;
    this->v2v3 = this->v3 - this->v2;
    this->v3v1 = this->v1 - this->v3;

    this->normal = (v1v2.cross(v1v3)).normalized();
}

Point Face::planeIntersection(Point rayOrigin, Point rayDirection)
{
    float t;
    Point v_aux1 = this->v1 - rayOrigin;
    float prod = this->normal.dot(rayDirection);

    if (prod == 0)
    {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }

    else
    {
        t = (this->normal.dot(v_aux1)) / prod;
    }
    Point planeIntersection = rayOrigin + (rayDirection * t);
    return planeIntersection;
};

Point Face::rayIntersection(Point rayOrigin, Point rayDirection)
{
    Point planeIntersection = this->planeIntersection(rayOrigin, rayDirection);

    if (planeIntersection[2] == MAXFLOAT)
    {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }


    Point p1p2 = this->v2 - this->v1;
    Point p1p3 = this->v3 - this->v1;
    Point p2p3 = this->v3 - this->v2;
    Point p3p1 = this->v1 - this->v3;

    Point n = (p1p2.cross(p1p3)).normalized();

    Point p1pi = planeIntersection - this->v1;
    Point p2pi = planeIntersection - this->v2;
    Point p3pi = planeIntersection - this->v3;


    if(p1p2.cross(p1pi).dot(p1p2.cross(p1p3)) < 0)
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);

    if(p2p3.cross(p2pi).dot(p1p2.cross(p1p3)) < 0) 
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);

    if(p3p1.cross(p3pi).dot(p1p2.cross(p1p3)) < 0)
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);


    return planeIntersection;
};

Point Face::getNormal()
{
    return this->normal;
};

//////////////////Cluster////////////////////

void Cluster::addShape(Shape* shape)
{
    this->shapes.push_back(shape);
};

void Cluster::applyTransformation(Matrix transform)
{
    for (int i = 0; i < this->shapes.size(); i++)
    {
        this->shapes[i]->applyTransform(transform);
    }
};

void Cluster::setCameraCoordinates(Matrix worldToCamera)
{
    for (int i = 0; i < this->shapes.size(); i++)
    {
        this->shapes[i]->setCameraCoordinates(worldToCamera);
    }
};

void Cluster::setWorldCoordinates(Matrix cameraToWorld)
{
    for (int i = 0; i < this->shapes.size(); i++)
    {
        this->shapes[i]->setWorldCoordinates(cameraToWorld);
    }
};

Point* Cluster::Bounds()
{
    Point init_bound[2] = *this->shapes[0]->Bounds();
    Point max_bound = init_bound[0];
    Point min_bound = init_bound[1];

    for (int i = 0; i < this->shapes.size(); i++)
    {
        Point prov_bounds[2] = *this->shapes[i]->Bounds();
        Point prov_min = prov_bounds[0];
        Point prov_max = prov_bounds[1];
        
        if(prov_min[0] < min_bound[0])
        {
            min_bound[0] = prov_min[0];
        }
        if(prov_min[1] < min_bound[1])
        {
            min_bound[1] = prov_min[1];
        }
        if(prov_min[2] < min_bound[2])
        {
            min_bound[2] = prov_min[2];
        }
        if(prov_max[0] > max_bound[0])
        {
            max_bound[0] = prov_max[0];
        }
        if(prov_max[1] > max_bound[1])
        {
            max_bound[1] = prov_max[1];
        }
        if(prov_max[2] > max_bound[2])
        {
            max_bound[2] = prov_max[2];
        }

    }
    Point bounds[2] = {min_bound, max_bound};
    return bounds;
}

Point Cluster::rayIntersect(Point rayOrigin, Point rayDirection)
{
    Point pi = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    float closest_intersection = MAXFLOAT;
    for (int i = 0; i < this->shapes.size(); i++)
    {
        Point p = this->shapes[i]->rayIntersect(rayOrigin, rayDirection);
        if(p[0] < MAXFLOAT)
        {
            float distance = sqrt(pow(p[0] - rayOrigin[0], 2) + pow(p[1] - rayOrigin[1], 2) + pow(p[2] - rayOrigin[2], 2));
            if(distance < closest_intersection)
            {
                closest_intersection = distance;
                pi = p;
            }
        }
    }
    return pi;
}