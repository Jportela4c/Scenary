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

    Eigen::Vector3f v1v3n = Eigen::Vector3f(v1v3[0], v1v3[1], v1v3[2]);
    Eigen::Vector3f v1v2n = Eigen::Vector3f(v1v2[0], v1v2[1], v1v2[2]);
    Eigen::Vector3f normal = (v1v3n.cross(v1v2n)).normalized();

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
    Vertex pv1 = planeIntersection - this->v1;
    Vertex pv2 = planeIntersection - this->v2;
    Vertex pv3 = planeIntersection - this->v3;

    Eigen::Vector3f pv1n = Eigen::Vector3f(pv1[0], pv1[1], pv1[2]);
    Eigen::Vector3f pv2n = Eigen::Vector3f(pv2[0], pv2[1], pv2[2]);
    Eigen::Vector3f pv3n = Eigen::Vector3f(pv3[0], pv3[1], pv3[2]);

    Eigen::Vector3f v1v2n = Eigen::Vector3f(this->v1v2[0], this->v1v2[1], this->v1v2[2]);
    Eigen::Vector3f v1v3n = Eigen::Vector3f(this->v1v3[0], this->v1v3[1], this->v1v3[2]);
    Eigen::Vector3f v2v3n = Eigen::Vector3f(this->v2v3[0], this->v2v3[1], this->v2v3[2]);
    Eigen::Vector3f v3v1n = Eigen::Vector3f(this->v3v1[0], this->v3v1[1], this->v3v1[2]);

    if (pv1n.cross(v1v2n).dot((v1v3n).cross(v1v2n)) < 0)
    {
        return Vertex(0,0,0,-1);
    }
    else if (pv2n.cross(v2v3n).dot((v1v3n).cross(v1v2n)) < 0)
    {
        return Vertex(0,0,0,-1);
    }
    else if (pv3n.cross(v3v1n).dot((v1v3n).cross(v1v2n)) < 0)
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