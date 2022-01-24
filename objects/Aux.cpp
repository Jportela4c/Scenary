#include "Aux.hpp"



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

Vertex Face::intersection(Vertex v0, Vertex v2)
{
    float t;
    Vertex v_aux1 = this->v1 - v0;
    v_aux1[3] = 1;
    float prod = this->normal.dot(v2);

    if (prod == 0)
    {
        return Vertex(0,0,0,-1);
    }
    
    else
    {
        t = (this->normal.dot(v_aux1))/prod;
    }

    return v0 + (v2 * t);
};

bool Face::validate(Vertex v1, Vertex v2, Vertex v3)
{
    float validation = (this->v1v2.cross(this->v1v3)).dot(this->v1v2.cross(v1));
    
    if (validation < 0)
    {
        return false;
    }

    validation =  (this->v2v3.cross(v2)).dot(this->v1v2.cross(this->v1v3));

    if (validation < 0)
    {
        return false;
    }

    validation =  (this->v3v1.cross(v3)).dot(this->v1v2.cross(this->v1v3));

    if (validation < 0)
    {
        return false;
    }

    return true;
};