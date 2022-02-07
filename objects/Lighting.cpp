#include "Lighting.hpp"

Lighting::Lighting(){};
float Lighting::difuseFactor(Point point, Point normal){return 0.0;};
float Lighting::specularFactor(Point point, Point normal){return 0.0;};
Point Lighting::difuseIntensity(Point point, Point normal, Material mat){return Point(0.0, 0.0, 0.0);};
Point Lighting::specularIntensity(Point point, Point normal, Material mat){return Point(0.0, 0.0, 0.0);};
void Lighting::setCameraCoordinates(Matrix worldToCamera){};
void Lighting::setWorldCoordinates(Matrix cameraToWorld){};


AmbientLighting::AmbientLighting(){
    r = 0.0;
    g = 0.0;
    b = 0.0;
};
AmbientLighting::AmbientLighting(float r, float g, float b)
{
    this->r = r;
    this->g = g;
    this->b = b;
};

Point AmbientLighting::ambientIntensity(Point point, Material mat)
{
    Point intensity;
    intensity[0] = this->r * mat.ka[0];
    intensity[1] = this->g * mat.ka[1];
    intensity[2] = this->b * mat.ka[2];
    return intensity;
};

SpotLighting::SpotLighting(float r, float g, float b, Point position, Point direction, float angle)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->position = position;
    this->direction = direction.normalized();
    this->angle = angle;
};

/*double check*/
float SpotLighting::difuseFactor(Point point, Point normal)
{
    Point lightDirection = this->position - point;
    lightDirection = lightDirection.normalized();
    float angle = this->direction.dot(lightDirection*-1);
    if(angle > cos(this->angle))
    {
        return 0;
    }
    else
    {
        float difuseFactor = lightDirection.dot(normal); 
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
float SpotLighting::specularFactor(Point point, Point normal)
{
    Point lightDirection = (this->position - point).normalized();
    Point reflectedDirection = 2*normal*(normal.dot(lightDirection)) - lightDirection;
    Point p = Point(0, 0, 0) - point;

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

Point SpotLighting::difuseIntensity(Point point, Point normal,  Material mat)
{
    Point difuse_intensity;
    difuse_intensity[0] = this->r * mat.kd[0];
    difuse_intensity[1] = this->g * mat.kd[1];
    difuse_intensity[2] = this->b * mat.kd[2];
    difuse_intensity = difuse_intensity * this->difuseFactor(point, normal);
    return difuse_intensity;
};

Point SpotLighting::specularIntensity(Point point, Point normal, Material mat)
{
    Point specular_intensity;
    specular_intensity[0] = this->r * mat.ks[0];
    specular_intensity[1] = this->g * mat.ks[1];
    specular_intensity[2] = this->b * mat.ks[2];
    specular_intensity = specular_intensity * pow(this->specularFactor(point, normal), mat.shininess);
    return specular_intensity;
};
//Utilizar Vertex
void SpotLighting::setCameraCoordinates(Matrix worldToCamera)
{
    this->position = worldToCamera * this->position;
    this->direction = worldToCamera * this->direction;
};
//Utilizar Vertex
void SpotLighting::setWorldCoordinates(Matrix cameraToWorld)
{
    this->position = cameraToWorld * this->position;
    this->direction = cameraToWorld * this->direction;
};

FarLighting::FarLighting(float r, float g, float b, Point direction) 
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->direction = direction.normalized();
};

/*double check*/
float FarLighting::difuseFactor(Point point, Point normal)
{
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
float FarLighting::specularFactor(Point point, Point normal)
{

    Point r = (2 * ((this->direction*-1).dot(normal)) * normal) + this->direction;
    Point v = Point(0, 0, 0) - point;
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

Point FarLighting::difuseIntensity(Point point, Point normal, Material mat)
{
    Point difuseIntensity;
    difuseIntensity[0] = this->r * mat.kd[0];
    difuseIntensity[1] = this->g * mat.kd[1];
    difuseIntensity[2] = this->b * mat.kd[2];
    difuseIntensity = difuseIntensity * this->difuseFactor(point, normal);
    return difuseIntensity;
};

Point FarLighting::specularIntensity(Point point, Point normal, Material mat)
{
    Point specularIntensity;
    specularIntensity[0] = this->r * mat.ks[0];
    specularIntensity[1] = this->g * mat.ks[1];
    specularIntensity[2] = this->b * mat.ks[2];
    specularIntensity = specularIntensity * this->specularFactor(point, normal);
    return specularIntensity;
};
//Utilizar Vertex
void FarLighting::setCameraCoordinates(Matrix worldToCamera)
{
    this->direction = worldToCamera * this->direction;
};
//Utilizar Vertex
void FarLighting::setWorldCoordinates(Matrix cameraToWorld)
{
    this->direction = cameraToWorld * this->direction;
};

PointLighting::PointLighting(float r, float g, float b, Point position)
{
    this->r = r;
    this->g = g;
    this->b = b;
    this->position = position;
};

/*double check*/
float PointLighting::difuseFactor(Point point, Point normal)
{
    Point lightDirection = this->position - point;
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
float PointLighting::specularFactor(Point point, Point normal)
{
    Point p = this->position - point;
    Point l = p.normalized();

    Point r = (2 * ((l).dot(normal)) * normal) - l;
    Point v = Point(0, 0, 0) - point;

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
Point PointLighting::difuseIntensity(Point point, Point normal, Material mat)
{
    Point difuseIntensity;
    difuseIntensity[0] = this->r * mat.kd[0];
    difuseIntensity[1] = this->g * mat.kd[1];
    difuseIntensity[2] = this->b * mat.kd[2];

    difuseIntensity = difuseIntensity * this->difuseFactor(point, normal);
    return difuseIntensity;
};

Point PointLighting::specularIntensity(Point point, Point normal, Material mat)
{
    Point specularIntensity;
    specularIntensity[0] = this->r * mat.ks[0];
    specularIntensity[1] = this->g * mat.ks[1];
    specularIntensity[2] = this->b * mat.ks[2];
    specularIntensity = specularIntensity * pow(this->specularFactor(point, normal), mat.shininess);
    return specularIntensity;
};
//Utilizar Vertex
void PointLighting::setCameraCoordinates(Matrix worldToCamera)
{
    this->position = worldToCamera * this->position;
};
//Utilizar Vertex
void PointLighting::setWorldCoordinates(Matrix cameraToWorld)
{
    this->position = cameraToWorld * this->position;
};