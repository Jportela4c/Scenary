#include "Cube.hpp"

#define MAXFLOAT 1000000.f

Cube::Cube() {};
Cube::Cube(float side, Point  center, Material mat)
{
    this->side = side;
    this->center = center;
    this->mat = mat;

    float s = this->side / 2;
    this->vertices[0] = Point(this->center[0] - s, this->center[1] + s, this->center[2] + s);
    this->vertices[1] = Point(this->center[0] - s, this->center[1] + s, this->center[2] - s);
    this->vertices[2] = Point(this->center[0] + s, this->center[1] + s, this->center[2] - s);
    this->vertices[3] = Point(this->center[0] + s, this->center[1] + s, this->center[2] + s);
    this->vertices[4] = Point(this->center[0] - s, this->center[1] - s, this->center[2] + s);
    this->vertices[5] = Point(this->center[0] - s, this->center[1] - s, this->center[2] - s);
    this->vertices[6] = Point(this->center[0] + s, this->center[1] - s, this->center[2] - s);
    this->vertices[7] = Point(this->center[0] + s, this->center[1] - s, this->center[2] + s);

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

    this->normal_intersect = Point(0, 0, 0);
}

void Cube::updateFaces()
{
    //this->side = side;
    //this->center = center;

    //float s = this->side / 2;
    //this->vertices[0] = Point(this->center[0] - s, this->center[1] + s, this->center[2] + s);
    //this->vertices[1] = Point(this->center[0] - s, this->center[1] + s, this->center[2] - s);
    //this->vertices[2] = Point(this->center[0] + s, this->center[1] + s, this->center[2] - s);
    //this->vertices[3] = Point(this->center[0] + s, this->center[1] + s, this->center[2] + s);
    //this->vertices[4] = Point(this->center[0] - s, this->center[1] - s, this->center[2] + s);
    //this->vertices[5] = Point(this->center[0] - s, this->center[1] - s, this->center[2] - s);
    //this->vertices[6] = Point(this->center[0] + s, this->center[1] - s, this->center[2] - s);
    //this->vertices[7] = Point(this->center[0] + s, this->center[1] - s, this->center[2] + s);

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

    //this->normal_intersect = Point(0, 0, 0);
}
//Utilizar Vertex
void Cube::applyTransform(Matrix transform)
{
    Vertex c = Vertex(center[0], center[1], center[2], 1);
    c = transform * c;
    this->center = c;
    for (int i = 0; i < 8; i++)
    {
        Vertex v = this->vertices[i];
        Vertex p = transform * v;
        this->vertices[i] = Point(p[0], p[1], p[2]);
    }
    updateFaces();
}
//Utilizar Vertex
void Cube::setCameraCoordinates(Matrix worldToCamera)
{
    Vertex c = Vertex(this->center[0], this->center[1], this->center[2], 1);
    c =  worldToCamera * c;
    this->center = Point(c[0], c[1], c[2]);
    for (int i = 0; i < 8; i++)
    {
        Vertex v = Vertex(this->vertices[i][0], this->vertices[i][1], this->vertices[i][2], 1);
        v = worldToCamera * v;
        this->vertices[i] = Point(v[0], v[1], v[2]);
    }
    updateFaces();
}
//Utilizar Vertex
void Cube::setWorldCoordinates(Matrix cameraToWorld)
{
    Vertex c = Vertex(this->center[0], this->center[1], this->center[2], 1);
    c =  cameraToWorld * c;
    this->center = Point(c[0], c[1], c[2]);
    for (int i = 0; i < 8; i++)
    {
        Vertex v = Vertex(this->vertices[i][0], this->vertices[i][1], this->vertices[i][2], 1);
        v = cameraToWorld * v;
        this->vertices[i] = Point(v[0], v[1], v[2]);
    }
    updateFaces();
}

void Cube::setNormal(Point intersect)
{
    this->normal_intersect = intersect;
}

Point Cube::rayIntersect(Point rayOrigin, Point rayDirection)
{
    double distance = MAXFLOAT;
    Point closest_intersection = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
    for (int i = 0; i < 12; i++)
    {
        Face face = this->faces[i];
        Point intersection = face.rayIntersection(rayOrigin, rayDirection);
        double intersectionDistance = sqrt(pow(intersection[0] - rayOrigin[0], 2) + pow(intersection[1] - rayOrigin[1], 2) + pow(intersection[2] - rayOrigin[2], 2));
        if (intersection[0] < MAXFLOAT && intersectionDistance < distance)
        {
            distance = intersectionDistance;
            closest_intersection = intersection;
            setNormal(face.getNormal());
        }
    }
    return closest_intersection;
};

Point Cube::normal(Point point)
{
    return this->normal_intersect;
}

Point* Cube::Bounds()
{
    Point minBounds = this->vertices[0];
    Point maxBounds = this->vertices[0];
    for (int i = 0; i < 8; i++)
    {
        if (vertices[i][0] > maxBounds[0])
        {
            maxBounds[0] = vertices[i][0];
        }
        if (vertices[i][1] > maxBounds[1])
        {
            maxBounds[1] = vertices[i][1];
        }
        if (vertices[i][2] > maxBounds[2])
        {
            maxBounds[2] = vertices[i][2];
        }
        if (vertices[i][0] < minBounds[0])
        {
            minBounds[0] = vertices[i][0];
        }
        if (vertices[i][1] < minBounds[1])
        {
            minBounds[1] = vertices[i][1];
        }
        if (vertices[i][2] < minBounds[2])
        {
            minBounds[2] = vertices[i][2];
        }
    }

    Point bounds[2] = {minBounds, maxBounds};
    return bounds;
    
}