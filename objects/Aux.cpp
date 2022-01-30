#include "Aux.hpp"

Shape::Shape(){};

Material::Material(){};
Material::Material(Point ka, Point kd, Point ks, float shininess)
{
    this->ka = ka;
    this->kd = kd;
    this->ks = ks;
    this->shininess = shininess;
};

Face::Face(){
    v1 = Vertex(0,0,0,1);
    v2 = Vertex(0,0,0,1);
    v3 = Vertex(0,0,0,1);
};

Face::Face(Vertex vertex1, Vertex vertex2, Vertex vertex3): v1(vertex1), v2(vertex2), v3(vertex3)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
    Vertex v1v2 = v2 - v1;
    Vertex v1v3 = v3 - v1;
    Vertex v2v3 = v3 - v2;
    Vertex v3v1 = v1 - v3;
    v1v2[3] = 1;
    v1v3[3] = 1;
    v2v3[3] = 1;
    v3v1[3] = 1;
    this->normal = (v1v2.cross(v1v3)).normalized();
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
    Vertex pv1 = planeIntersection - this->v1;
    Vertex pv2 = planeIntersection - this->v2;
    Vertex pv3 = planeIntersection - this->v3;

    if (pv1.cross(this->v1v2).dot((this->v1v3).cross(this->v1v2)) < 0)
    {
        return Vertex(0,0,0,-1);
    }
    else if (pv2.cross(this->v2v3).dot((this->v1v3).cross(this->v1v2)) < 0)
    {
        return Vertex(0,0,0,-1);
    }
    else if (pv3.cross(this->v3v1).dot((this->v1v3).cross(this->v1v2)) < 0)
    {
        return Vertex(0,0,0,-1);
    }
    else
    {
        return planeIntersection;
    }
};