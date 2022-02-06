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
    v1v2[3] = 1;
    v1v3[3] = 1;
    v2v3[3] = 1;
    v3v1[3] = 1;

    Point v1v3n = Point(v1v3[0], v1v3[1], v1v3[2]);
    Point v1v2n = Point(v1v2[0], v1v2[1], v1v2[2]);
    Point normal = (v1v3n.cross(v1v2n)).normalized();

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
    Vertex pv1 = this->v1 - planeIntersection;
    Vertex pv2 = this->v2 - planeIntersection;
    Vertex pv3 = this->v3 - planeIntersection;

    Point pv1n = Point(pv1[0], pv1[1], pv1[2]);
    Point pv2n = Point(pv2[0], pv2[1], pv2[2]);
    Point pv3n = Point(pv3[0], pv3[1], pv3[2]);

    Point v1v2n = Point(this->v1v2[0], this->v1v2[1], this->v1v2[2]);
    Point v1v3n = Point(this->v1v3[0], this->v1v3[1], this->v1v3[2]);
    Point v2v3n = Point(this->v2v3[0], this->v2v3[1], this->v2v3[2]);
    Point v3v1n = Point(this->v3v1[0], this->v3v1[1], this->v3v1[2]);

    float e = (pv1n.cross(pv2n)).dot(this->normal);
    float f = (pv2n.cross(pv3n)).dot(this->normal);
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