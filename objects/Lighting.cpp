#include "Lighting.hpp"

AmbientLight::AmbientLight(){};
AmbientLight::AmbientLight(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
};

Vertex AmbientLight::ambientIntensity(Vertex point)
{
    return Vertex(this->r, this->g, this->b);
};

SpotLight::SpotLight(){};
SpotLight::SpotLight(float r, float g, float b, Vertex position, Vertex direction, float angle)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->position = position;
    this->direction = direction.normalized();
    this->angle = angle;
};

/*double check*/
float SpotLight::difuseFactor(Vertex point)
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
float SpotLight::specularFactor(Vertex point)
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
/*Vertex SpotLight::difuseIntensity(Vertex point)
{
    Vertex difuse_intensity;
    difuse_intensity[0] = this->r * material.kd[0];
    difuse_intensity[1] = this->g * material.kd[1];
    difuse_intensity[2] = this->b * material.kd[2];
    difuse_intensity = difuse_intensity * this->difuseFactor(point);
    return difuse_intensity;
};*/

/*Needs to implement materials*/
/*Vertex SpotLight::specularIntensity(Vertex point)
{
    Vertex specular_intensity;
    specular_intensity[0] = this->r * material.ks[0];
    specular_intensity[1] = this->g * material.ks[1];
    specular_intensity[2] = this->b * material.ks[2];
    specular_intensity = specular_intensity * pow(this->specularFactor(point), material.shininess);
    return specular_intensity;
};*/

void SpotLight::worldToCamera(Matrix worldToCamera)
{
    this->position = worldToCamera * this->position;
    this->direction = worldToCamera * this->direction;
};

void SpotLight::cameraToWorld(Matrix cameraToWorld)
{
    this->position = cameraToWorld * this->position;
    this->direction = cameraToWorld * this->direction;
};

FarLight::FarLight(){};
FarLight::FarLight(float r, float g, float b, Vertex direction) 
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->direction = direction;
};

/*double check*/
float FarLight::difuseFactor(Vertex point)
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
float FarLight::specularFactor(Vertex point)
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
/*Vertex FarLight::difuseIntensity(Vertex point)
{
    Vertex difuseIntensity;
    difuseIntensity[0] = this->r * material.kd[0];
    difuseIntensity[1] = this->g * material.kd[1];
    difuseIntensity[2] = this->b * material.kd[2];
    return difuseIntensity;
};*/

/*need to implement materials*/
/*Vertex FarLight::specularIntensity(Vertex point)
{
    Vertex specularIntensity;
    specularIntensity[0] = this->r * material.ks[0];
    specularIntensity[1] = this->g * material.ks[1];
    specularIntensity[2] = this->b * material.ks[2];
    specularIntensity = specularIntensity * this->specularFactor(point);
    return specularIntensity;
};*/

void FarLight::worldToCamera(Matrix worldToCamera)
{
    this->direction = worldToCamera * this->direction;
};

void FarLight::cameraToWorld(Matrix cameraToWorld)
{
    this->direction = cameraToWorld * this->direction;
};

PointLight::PointLight(){};
PointLight::PointLight(float r, float g, float b, Vertex position)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->position = position;
};

/*double check*/
float PointLight::difuseFactor(Vertex point)
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
float PointLight::specularFactor(Vertex point)
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
Vertex PointLight::difuseIntensity(Vertex point)
{
    Vertex difuseIntensity;
    difuseIntensity[0] = this->r * material.kd[0];
    difuseIntensity[1] = this->g * material.kd[1];
    difuseIntensity[2] = this->b * material.kd[2];

    difuseIntensity = difuseIntensity * this->difuseFactor(point);
    return difuseIntensity;
};
};

/*need to implement materials*/
Vertex PointLight::specularIntensity(Vertex point)
{
    Vertex specularIntensity;
    specularIntensity[0] = this->r * material.ks[0];
    specularIntensity[1] = this->g * material.ks[1];
    specularIntensity[2] = this->b * material.ks[2];
    specularIntensity = specularIntensity * pow(this->specularFactor(point), material.shininess);
    return specularIntensity;
};

void PointLight::worldToCamera(Matrix worldToCamera)
{
    this->position = worldToCamera * this->position;
};

void PointLight::cameraToWorld(Matrix cameraToWorld)
{
    this->position = cameraToWorld * this->position;
};