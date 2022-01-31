#include "Lighting.hpp"

AmbientLighting::AmbientLighting(){};
AmbientLighting::AmbientLighting(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
};

Point AmbientLighting::ambientIntensity(Vertex point, Material mat)
{
    Point intensity;
    intensity[0] = this->r * mat.ka[0];
    intensity[1] = this->g * mat.ka[1];
    intensity[2] = this->b * mat.ka[2];
    return intensity;
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
    lightDirection = lightDirection.normalized();
    float angle = this->direction.dot(lightDirection*-1);
    if(angle > cos(this->angle))
    {
        return 0;
    }
    else
    {
        float difuseFactor = lightDirection.dot(this->direction); /*<<<<<<<<NÂO È this->direction*/
        if(difuseFactor < 0)
        {
            return 0;
        }
        else
        {
            return difuseFactor;
        }
    }
};

/*double check*/
float SpotLighting::specularFactor(Vertex point)
{
    Vertex lightDirection = (this->position - point).normalized();
    lightDirection[3] = 1;
    Vertex normal = this->direction.normalized(); /*<<<<<<<<<NÂO È ISSO*/
    Vertex reflectedDirection = 2*normal*(normal.dot(lightDirection)) - lightDirection;
    Vertex p = Vertex(0, 0, 0, 0) - point;

    if(lightDirection.dot(this->direction) > cos(this->angle))
    {
        return 0;

    }
    else
    {
        float specularFactor = reflectedDirection.dot(p);
        if(specularFactor < 0)
        {
            return 0;
        }
        else
        {
            return specularFactor;
        }
    }
};

Point SpotLighting::difuseIntensity(Vertex point, Material mat)
{
    Vertex difuse_intensity;
    difuse_intensity[0] = this->r * mat.kd[0];
    difuse_intensity[1] = this->g * mat.kd[1];
    difuse_intensity[2] = this->b * mat.kd[2];
    difuse_intensity = difuse_intensity * this->difuseFactor(point);
    return difuse_intensity;
};

Point SpotLighting::specularIntensity(Vertex point, Material mat)
{
    Vertex specular_intensity;
    specular_intensity[0] = this->r * mat.ks[0];
    specular_intensity[1] = this->g * mat.ks[1];
    specular_intensity[2] = this->b * mat.ks[2];
    specular_intensity = specular_intensity * pow(this->specularFactor(point), mat.shininess);
    return specular_intensity;
};

void SpotLighting::setCameraCoordinates(Matrix worldToCamera)
{
    this->position = worldToCamera * this->position;
    this->direction = worldToCamera * this->direction;
};

void SpotLighting::setWorldCoordinates(Matrix cameraToWorld)
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
    this->direction = direction.normalized();
};

/*double check*/
float FarLighting::difuseFactor(Vertex point)
{
    Vertex normal = this->direction; /*<<<<<<<<NÃO È ISSO*/
    float difuseFactor = (this->direction*-1).dot(normal);
    if (difuseFactor >= 0)
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
    Vertex normal = this->direction; /*<<<<<<<<NÃO È ISSO*/

    Vertex r = (2 * ((this->direction*-1).dot(normal)) * normal) + this->direction;
    Vertex v = Vertex(0, 0, 0, 0) - point;
    float specularFactor = v.normalized().dot(r.normalized());

    if (specularFactor >= 0)
    {
        return specularFactor;
    }
    else
    {
        return 0;
    }

};

Point FarLighting::difuseIntensity(Vertex point, Material mat)
{
    Vertex difuseIntensity;
    difuseIntensity[0] = this->r * mat.kd[0];
    difuseIntensity[1] = this->g * mat.kd[1];
    difuseIntensity[2] = this->b * mat.kd[2];
    difuseIntensity = difuseIntensity * this->difuseFactor(point);/*<<<<<<<È ISSO MESMO??????*/
    return difuseIntensity;
};

Point FarLighting::specularIntensity(Vertex point, Material mat)
{
    Vertex specularIntensity;
    specularIntensity[0] = this->r * mat.ks[0];
    specularIntensity[1] = this->g * mat.ks[1];
    specularIntensity[2] = this->b * mat.ks[2];
    specularIntensity = specularIntensity * this->specularFactor(point);
    return specularIntensity;
};

void FarLighting::setCameraCoordinates(Matrix worldToCamera)
{
    this->direction = worldToCamera * this->direction;
};

void FarLighting::setWorldCoordinates(Matrix cameraToWorld)
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
    Vertex normal = this->position.normalized(); /*<<<<<<<<NÃO È ISSO*/
    float difuseFactor = lightDirection.dot(normal);

    if (difuseFactor >= 0)
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
    Vertex p = this->position - point;
    Vertex l = p.normalized();

    Vertex normal = this->position.normalized(); /*<<<<<<<<NÃO È ISSO*/

    Vertex r = (2 * ((l).dot(normal)) * normal) - l;
    Vertex v = Vertex(0, 0, 0, 0) - point;

    float specularFactor = v.normalized().dot(r.normalized());

    if (specularFactor >= 0)
    {
        return specularFactor;
    }
    else
    {
        return 0;
    }
};

/*need to implement materials*/
Point PointLighting::difuseIntensity(Vertex point, Material mat)
{
    Vertex difuseIntensity;
    difuseIntensity[0] = this->r * mat.kd[0];
    difuseIntensity[1] = this->g * mat.kd[1];
    difuseIntensity[2] = this->b * mat.kd[2];

    difuseIntensity = difuseIntensity * this->difuseFactor(point);
    return difuseIntensity;
};

Point PointLighting::specularIntensity(Vertex point, Material mat)
{
    Vertex specularIntensity;
    specularIntensity[0] = this->r * mat.ks[0];
    specularIntensity[1] = this->g * mat.ks[1];
    specularIntensity[2] = this->b * mat.ks[2];
    specularIntensity = specularIntensity * pow(this->specularFactor(point), mat.shininess);
    return specularIntensity;
};

void PointLighting::setCameraCoordinates(Matrix worldToCamera)
{
    this->position = worldToCamera * this->position;
};

void PointLighting::setWorldCoordinates(Matrix cameraToWorld)
{
    this->position = cameraToWorld * this->position;
};