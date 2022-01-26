#include "Lighting.hpp"

AmbientLighting::AmbientLighting(){};
AmbientLighting::AmbientLighting(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
};

Vertex AmbientLighting::ambientIntensity(Vertex point)
{
    return Vertex(this->r, this->g, this->b);
};

SpotLighting::SpotLighting(){};
SpotLighting::SpotLighting(float r, float g, float b, Vertex position, Vertex direction, float angle)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->position = position;
    this->direction = direction.normalized();
    this->angle = angle;
};

/*double check*/
float SpotLighting::difuseFactor(Vertex point)
{
    Vertex lightDirection = this->position - point;
    lightDirection[3] = 1;
    float distance = lightDirection.norm();
    lightDirection = lightDirection.normalized();
    float angle = this->direction.dot(lightDirection);
    if (angle > cos(this->angle))
    {
        return 1.0 / (4 * M_PI * pow(distance, 2));
    }
    else
    {
        return 0;
    }
};

/*double check*/
float SpotLighting::specularFactor(Vertex point)
{
    Vertex lightDirection = this->position - point;
    lightDirection[3] = 1;
    float distance = lightDirection.norm();
    lightDirection = lightDirection.normalized();
    float angle = this->direction.dot(lightDirection);
    if (angle > cos(this->angle))
    {
        return pow(angle, 2) / (4 * M_PI * pow(distance, 2));
    }
    else
    {
        return 0;
    }
};

/* Needs to implement materials*/
/*Vertex SpotLighting::difuseIntensity(Vertex point)
{
    Vertex difuse_intensity;
    difuse_intensity[0] = this->r * material.kd[0];
    difuse_intensity[1] = this->g * material.kd[1];
    difuse_intensity[2] = this->b * material.kd[2];
    difuse_intensity = difuse_intensity * this->difuseFactor(point);
    return difuse_intensity;
};*/

/*Needs to implement materials*/
/*Vertex SpotLighting::specularIntensity(Vertex point)
{
    Vertex specular_intensity;
    specular_intensity[0] = this->r * material.ks[0];
    specular_intensity[1] = this->g * material.ks[1];
    specular_intensity[2] = this->b * material.ks[2];
    specular_intensity = specular_intensity * pow(this->specularFactor(point), material.shininess);
    return specular_intensity;
};*/

void SpotLighting::worldToCamera(Matrix worldToCamera)
{
    this->position = worldToCamera * this->position;
    this->direction = worldToCamera * this->direction;
};

void SpotLighting::cameraToWorld(Matrix cameraToWorld)
{
    this->position = cameraToWorld * this->position;
    this->direction = cameraToWorld * this->direction;
};

FarLighting::FarLighting(){};
FarLighting::FarLighting(float r, float g, float b, Vertex direction) 
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->direction = direction;
};

/*double check*/
float FarLighting::difuseFactor(Vertex point)
{
    Vertex normal = point.normal();
    float difuseFactor = (this->direction*-1).dot(normal);
    if (difuseFactor > 0)
    {
        return difuseFactor;
    }
    else
    {
        return 0;
    }

};

/*double check*/
float FarLighting::specularFactor(Vertex point)
{
    Vertex normal = point.normal();

    Vertex r = (2 * ((this->direction*-1).dot(normal)) * normal) - this->direction;
    Vertex v = point - Vertex(0, 0, 0, 0);
    float specularFactor = v.normalized().dot(r.normalized());

    if (specularFactor > 0)
    {
        return specularFactor;
    }
    else
    {
        return 0;
    }

};

/*need to implement materials*/
/*Vertex FarLighting::difuseIntensity(Vertex point)
{
    Vertex difuseIntensity;
    difuseIntensity[0] = this->r * material.kd[0];
    difuseIntensity[1] = this->g * material.kd[1];
    difuseIntensity[2] = this->b * material.kd[2];
    return difuseIntensity;
};*/

/*need to implement materials*/
/*Vertex FarLighting::specularIntensity(Vertex point)
{
    Vertex specularIntensity;
    specularIntensity[0] = this->r * material.ks[0];
    specularIntensity[1] = this->g * material.ks[1];
    specularIntensity[2] = this->b * material.ks[2];
    specularIntensity = specularIntensity * this->specularFactor(point);
    return specularIntensity;
};*/

void FarLighting::worldToCamera(Matrix worldToCamera)
{
    this->direction = worldToCamera * this->direction;
};

void FarLighting::cameraToWorld(Matrix cameraToWorld)
{
    this->direction = cameraToWorld * this->direction;
};

PointLighting::PointLighting(){};
PointLighting::PointLighting(float r, float g, float b, Vertex position)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->position = position;
};

/*double check*/
float PointLighting::difuseFactor(Vertex point)
{
    Vertex lightDirection = this->position - point;
    Vertex normal = point.normal();
    float difuseFactor = lightDirection.dot(normal);

    if (difuseFactor > 0)
    {
        return difuseFactor;
    }
    else
    {
        return 0;
    }
};

/*double check*/
float PointLighting::specularFactor(Vertex point)
{
    Vertex p = point - this->position;
    Vertex l = p.normalized();

    Vertex normal = point.normal();

    Vertex r = (2 * ((l).dot(normal)) * normal) - l;
    Vertex v = point - Vertex(0, 0, 0, 0);

    float specularFactor = v.normalized().dot(r.normalized());

    if (specularFactor > 0)
    {
        return specularFactor;
    }
    else
    {
        return 0;
    }
};

/*need to implement materials*/
Vertex PointLighting::difuseIntensity(Vertex point)
{
    Vertex difuseIntensity;
    difuseIntensity[0] = this->r * material.kd[0];
    difuseIntensity[1] = this->g * material.kd[1];
    difuseIntensity[2] = this->b * material.kd[2];

    difuseIntensity = difuseIntensity * this->difuseFactor(point);
    return difuseIntensity;
};

Vertex PointLighting::specularIntensity(Vertex point)
{
    Vertex specularIntensity;
    specularIntensity[0] = this->r * material.ks[0];
    specularIntensity[1] = this->g * material.ks[1];
    specularIntensity[2] = this->b * material.ks[2];
    specularIntensity = specularIntensity * pow(this->specularFactor(point), material.shininess);
    return specularIntensity;
};

void PointLighting::worldToCamera(Matrix worldToCamera)
{
    this->position = worldToCamera * this->position;
};

void PointLighting::cameraToWorld(Matrix cameraToWorld)
{
    this->position = cameraToWorld * this->position;
};