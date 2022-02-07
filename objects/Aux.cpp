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
Vertex Shape::Bounds(){return Vertex(0, 0, 0, -1);};
Vertex Shape::rayIntercect(Vertex rayOrigin, Vertex rayDirection){return Vertex(0, 0, 0, -1);};
Vertex Shape::normal(Vertex point){return Vertex(0, 0, 0, -1);};
void Shape::setCameraCoordinates(Matrix worldToCamera){};
void Shape::setWorldCoordinates(Matrix camreToWolrd){};

Face::Face(){
    v1 = Vertex(0.0,0.0,0.0,1.0);
    v2 = Vertex(0.0,0.0,0.0,1.0);
    v3 = Vertex(0.0,0.0,0.0,1.0);
};

Face::Face(Vertex vertex1, Vertex vertex2, Vertex vertex3)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    this->v1v2 = this->v2 - this->v1;
    this->v1v3 = this->v3 - this->v1;
    this->v2v3 = this->v3 - this->v2;
    this->v3v1 = this->v1 - this->v3;
    this->v1v2[3] = 1;
    this->v1v3[3] = 1;
    this->v2v3[3] = 1;
    this->v3v1[3] = 1;

    Point v1v3n = Point(v1v3[0], v1v3[1], v1v3[2]);
    Point v1v2n = Point(v1v2[0], v1v2[1], v1v2[2]);
    Point normal = (v1v2n.cross(v1v3n)).normalized();

    this->normal = Vertex(normal[0], normal[1], normal[2], 1.0);
}

Vertex Face::planeIntersection(Vertex rayOrigin, Vertex rayDirection)
{
    float t;
    Vertex v_aux1 = this->v1 - rayOrigin;
    v_aux1[3] = 1;
    float prod = this->normal.dot(rayDirection);

    if (prod == 0)
    {
        return Vertex(0,0,0,-1);
    }
    
    else
    {
        t = (this->normal.dot(v_aux1))/prod;
    }
    Vertex planeIntersection = rayOrigin + (rayDirection * t);
    planeIntersection[3] = 1;
    return planeIntersection;
};

Vertex Face::rayIntersection(Vertex rayOrigin, Vertex rayDirection)
{
    Vertex planeIntersection = this->planeIntersection(rayOrigin, rayDirection);

    if(planeIntersection[3] == -1)
    {
        return Vertex(0,0,0,-1);
    }
    
    Point pi = Point(planeIntersection[0], planeIntersection[1], planeIntersection[2]);

    Point v1p = Point(this->v1[0], this->v1[1], this->v1[2]);
    Point v2p = Point(this->v2[0], this->v2[1], this->v2[2]);
    Point v3p = Point(this->v3[0], this->v3[1], this->v3[2]);

    Point p1p2p = v2p - v1p;
    Point p1p3p = v3p - v1p;
    Point p2p3p = v3p - v2p;
    Point p3p1p = v1p - v3p;

    Point n = (p1p2p.cross(p1p3p)).normalized();

    Point p1pi = v1p - pi;
    Point p2pi = v2p - pi;
    Point p3pi = v3p - pi;

    float e = p1pi.cross(p2pi).dot(n);
    float f = (p2pi.cross(p3pi)).dot(n);
    float s = 1 - e - f;

    if (e < 0)
    {
        return Vertex(0,0,0,-1);
    }
    else if (f < 0)
    {
        return Vertex(0,0,0,-1);
    }
    else if (s < 0)
    {
        return Vertex(0,0,0,-1);
    }
    else
    {
        return planeIntersection;
    }
};

Vertex Face::getNormal()
{
    return this->normal;
};