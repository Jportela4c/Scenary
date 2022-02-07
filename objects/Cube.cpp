#include "Cube.hpp"

Cube::Cube(){};
Cube::Cube(float side, Vertex  center, Material mat)
{
    this->side = side;
    this->center = center;
    this->mat = mat;

    float s = this->side/2;
    this->vertices[0] = Vertex(this->center[0] - s, this->center[1] + s, this->center[2] + s, 1);
    this->vertices[1] = Vertex(this->center[0] - s, this->center[1] + s, this->center[2] - s, 1);
    this->vertices[2] = Vertex(this->center[0] + s, this->center[1] + s, this->center[2] - s, 1);
    this->vertices[3] = Vertex(this->center[0] + s, this->center[1] + s, this->center[2] + s, 1);
    this->vertices[4] = Vertex(this->center[0] - s, this->center[1] - s, this->center[2] + s, 1);
    this->vertices[5] = Vertex(this->center[0] - s, this->center[1] - s, this->center[2] - s, 1);
    this->vertices[6] = Vertex(this->center[0] + s, this->center[1] - s, this->center[2] - s, 1);
    this->vertices[7] = Vertex(this->center[0] + s, this->center[1] - s, this->center[2] + s, 1);

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

void Cube::updateFaces()
{
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
}

void Cube::applyTransform(Matrix transform)
{
    this->center = transform * this->center;
    for (int i = 0; i < 8; i++)
    {
        this->vertices[i] = transform * this->vertices[i];
    }
    updateFaces();
}

void Cube::setCameraCoordinates(Matrix worldToCamera)
{
    this->center = worldToCamera * this->center;
    for(int i = 0; i < 8; i++)
    {
        vertices[i] = worldToCamera * vertices[i];
    }
    updateFaces();
}

void Cube::setWorldCoordinates(Matrix cameraToWorld)
{
    this->center = cameraToWorld * this->center;
    for(int i = 0; i < 8; i++)
    {
        vertices[i] = cameraToWorld * vertices[i];
    }
    updateFaces();
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