#include "Cube.hpp"

Cube::Cube(){};
Cube::Cube(float side, Vertex  center, Material mat): s(side), c(center), mat(mat)
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

    this->normal_intersect = Vertex(0, 0, 0, -1);

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

void Cube::setNormal(Vertex intersect)
{
    this->normal_intersect = intersect;
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
            setNormal(face.getNormal());
        }
    }
    return closest_intersection;
};

Vertex Cube::normal(Vertex point)
{
    return this->normal_intersect;
}

Vertex Cube::Bounds()
{
    Vertex minBounds = Vertex(numeric_limits<float>::max(), numeric_limits<float>::max(), numeric_limits<float>::max(), 1);
    Vertex maxBounds = Vertex(numeric_limits<float>::min(),numeric_limits<float>::min(),numeric_limits<float>::min(), 1);
    for(int i = 0; i < 8; i++)
    {
        if(vertices[i][0] > maxBounds[0])
        {
            maxBounds[0] = vertices[i][0];
        }
        if(vertices[i][1] > maxBounds[1])
        {
            maxBounds[1] = vertices[i][1];
        }
        if(vertices[i][2] > maxBounds[2])
        {
            maxBounds[2] = vertices[i][2];
        }
        if(vertices[i][0] < minBounds[0])
        {
            minBounds[0] = vertices[i][0];
        }
        if(vertices[i][1] < minBounds[1])
        {
            minBounds[1] = vertices[i][1];
        }
        if(vertices[i][2] < minBounds[2])
        {
            minBounds[2] = vertices[i][2];
        }
    }
}