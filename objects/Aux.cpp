#include "Aux.hpp"

Material::Material(){};
Material::Material(Point ka, Point kd, Point ks, float shininess)
{
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->shininess = shininess;
};

Shape::Shape(){};
Point Shape::Bounds(){return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);};
Point Shape::rayIntercect(Point rayOrigin, Point rayDirection){return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);};
Point Shape::normal(Point point){return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);};
void Shape::setCameraCoordinates(Matrix worldToCamera){};
void Shape::setWorldCoordinates(Matrix camreToWolrd){};

Face::Face(){
    v1 = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    v2 = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    v3 = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
};

Face::Face(Point vertex1, Point vertex2, Point vertex3)
{
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
        t = (this->normal.dot(v_aux1))/prod;
    }
    Point planeIntersection = rayOrigin + (rayDirection * t);
    return planeIntersection;
};

Point Face::rayIntersection(Point rayOrigin, Point rayDirection)
{
    Point planeIntersection = this->planeIntersection(rayOrigin, rayDirection);

    if(planeIntersection[3] == MAXFLOAT)
    {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
    

    Point p1p2 = this->v2 - this->v1;
    Point p1p3 = this->v3 - this->v1;
    Point p2p3 = this->v3 - this->v2;
    Point p3p1 = this->v1 - this->v3;

    Point n = (p1p2.cross(p1p3)).normalized();

    Point p1pi = this->v1 - planeIntersection;
    Point p2pi = this->v2 - planeIntersection;
    Point p3pi = this->v3 - planeIntersection;

    float e = p1pi.cross(p2pi).dot(n);
    float f = (p2pi.cross(p3pi)).dot(n);
    float s = 1 - e - f;

    if (e < 0)
    {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
    else if (f < 0)
    {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
    else if (s < 0)
    {
        return Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    }
    else
    {
        return planeIntersection;
    }
};

Point Face::getNormal()
{
    return this->normal;
};