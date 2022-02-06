#include "Cube.hpp"

Cube::Cube(){};
Cube::Cube(float side, Vertex  center, Material mat): s(side), c(center), mat(mat)
{
    float s = side;
    Vertex c = center;
    Vertex v0 = Vertex(c[0] - s/2, c[1] + s/2, c[2] + s/2, 1);
    Vertex v1 = Vertex(c[0] - s/2, c[1] + s/2, c[2] - s/2, 1);
    Vertex v2 = Vertex(c[0] + s/2, c[1] + s/2, c[2] - s/2, 1);
    Vertex v3 = Vertex(c[0] + s/2, c[1] + s/2, c[2] + s/2, 1);
    Vertex v4 = Vertex(c[0] - s/2, c[1] - s/2, c[2] + s/2, 1);
    Vertex v5 = Vertex(c[0] - s/2, c[1] - s/2, c[2] - s/2, 1);
    Vertex v6 = Vertex(c[0] + s/2, c[1] - s/2, c[2] - s/2, 1);
    Vertex v7 = Vertex(c[0] + s/2, c[1] - s/2, c[2] + s/2, 1);
    
    this->vertices[0] = v0;
    this->vertices[1] = v1;
    this->vertices[2] = v2;
    this->vertices[3] = v3;
    this->vertices[4] = v4;
    this->vertices[5] = v5;
    this->vertices[6] = v6;
    this->vertices[7] = v7;
    
    this->faces[0] = Face(this->vertices[2], this->vertices[3], this->vertices[7]);
    this->faces[1] = Face(this->vertices[2], this->vertices[7], this->vertices[6]);
    this->faces[2] = Face(this->vertices[2], this->vertices[1], this->vertices[0]);
    this->faces[3] = Face(this->vertices[2], this->vertices[0], this->vertices[3]);
    this->faces[4] = Face(this->vertices[3], this->vertices[0], this->vertices[7]);
    this->faces[5] = Face(this->vertices[0], this->vertices[4], this->vertices[7]);
    this->faces[6] = Face(this->vertices[1], this->vertices[4], this->vertices[0]);
    this->faces[7] = Face(this->vertices[1], this->vertices[5], this->vertices[4]);
    this->faces[8] = Face(this->vertices[7], this->vertices[4], this->vertices[6]);
    this->faces[9] = Face(this->vertices[4], this->vertices[5], this->vertices[6]);
    this->faces[10] = Face(this->vertices[2], this->vertices[6], this->vertices[1]);
    this->faces[11] = Face(this->vertices[6], this->vertices[5], this->vertices[1]);


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

    return maxBounds;
}