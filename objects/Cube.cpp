#include "Cube.hpp"
#include "Aux.hpp"
Cube::Cube(){};
Cube::Cube(float side, Vertex  center): s(side), c(center)
{

    Face faces[12];

    float s = side;
    Vertex c = center;
    Vertex v1 = Vertex(c[0] - s/2, c[1] + s, c[2] + s/2, 1);
    Vertex v2 = Vertex(c[0] - s/2, c[1] + s, c[2] - s/2, 1);
    Vertex v3 = Vertex(c[0] + s/2, c[1] + s, c[2] - s/2, 1);
    Vertex v4 = Vertex(c[0] + s/2, c[1] + s, c[2] + s/2, 1);
    Vertex v5 = Vertex(c[0] - s/2, c[1], c[2] + s/2, 1);
    Vertex v6 = Vertex(c[0] - s/2, c[1], c[2] - s/2, 1);
    Vertex v7 = Vertex(c[0] + s/2, c[1], c[2] - s/2, 1);
    Vertex v8 = Vertex(c[0] + s/2, c[1], c[2] + s/2, 1);
    
    vertices[0] = v1;
    vertices[1] = v2;
    vertices[2] = v3;
    vertices[3] = v4;
    vertices[4] = v5;
    vertices[5] = v6;
    vertices[6] = v7;
    vertices[7] = v8;
    
    faces[0] = Face(vertices[0], vertices[3], vertices[2]);
    faces[1] = Face(vertices[2], vertices[1], vertices[0]);
    faces[2] = Face(vertices[6], vertices[5], vertices[2]);
    faces[3] = Face(vertices[5], vertices[1], vertices[2]);
    faces[4] = Face(vertices[7], vertices[6], vertices[3]);
    faces[5] = Face(vertices[6], vertices[2], vertices[3]);
    faces[6] = Face(vertices[4], vertices[7], vertices[3]);
    faces[7] = Face(vertices[3], vertices[0], vertices[4]);
    faces[8] = Face(vertices[5], vertices[4], vertices[0]);

}

void Cube::applyTransform(Matrix transform)
{
    for(int i = 0; i < 8; i++)
    {
        vertices[i] = transform * vertices[i];
    }
}

void Cube::setCameraCoordinates(Matrix worldToCamera)
{
    for(int i = 0; i < 8; i++)
    {
        vertices[i] = worldToCamera * vertices[i];
    }
}

void Cube::setWorldCoordinates(Matrix cameraToWorld)
{
    for(int i = 0; i < 8; i++)
    {
        vertices[i] = cameraToWorld * vertices[i];
    }
}

Vertex Cube::rayIntersect(Vertex rayOrigin, Vertex rayDirection)
{
    float distance = MAXFLOAT;
    Vertex closest_intersection = Vertex(0,0,0,-1);
    for (int i = 0; i < 12; i++)
    {
        
        Face face = this->faces[i];
        Vertex intersection = face.rayIntersection(rayOrigin, rayDirection);
        float intersectionDistance = sqrt(pow(intersection[0] - rayOrigin[0], 2) + pow(intersection[1] - rayOrigin[1], 2) + pow(intersection[2] - rayOrigin[2], 2));
        if (intersection[3] > -1 && intersectionDistance < distance)
        {
            distance = intersectionDistance;
            closest_intersection = intersection;
        }
    }
    return closest_intersection;
}