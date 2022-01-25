#include "Aux.hpp"

class AmbientLight
{
    float r;
    float g;
    float b;
    AmbientLight();
    AmbientLight(float r, float g, float b);
    Vertex ambientIntensity(Vertex point);
};

class SpotLight
{
    float r;
    float g;
    float b;
    Vertex position;
    Vertex direction;
    float angle;
    SpotLight();
    SpotLight(float r, float g, float b, Vertex position, Vertex direction, float angle);
    float difuseFactor(Vertex point);
    float specularFactor(Vertex point);
    Vertex difuseIntensity(Vertex point);
    Vertex specularIntensity(Vertex point);
    void worldToCamera(Matrix worldToCamera);
    void cameraToWorld(Matrix cameraToWorld);
};

class FarLight
{
    float r;
    float g;
    float b;
    Vertex direction;
    FarLight();
    FarLight(float r, float g, float b, Vertex direction);
    float difuseFactor(Vertex point);
    float specularFactor(Vertex point);
    Vertex difuseIntensity(Vertex point);
    Vertex specularIntensity(Vertex point);
    void worldToCamera(Matrix worldToCamera);
    void cameraToWorld(Matrix cameraToWorld);
};

class PointLight
{
    float r;
    float g;
    float b;
    Vertex position;
    PointLight();
    PointLight(float r, float g, float b, Vertex position);
    float difuseFactor(Vertex point);
    float specularFactor(Vertex point);
    Vertex difuseIntensity(Vertex point);
    Vertex specularIntensity(Vertex point);
    void worldToCamera(Matrix worldToCamera);
    void cameraToWorld(Matrix cameraToWorld);
};

