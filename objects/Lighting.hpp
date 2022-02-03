#include "Aux.hpp"

class Lighting
{
    public:
    float r;
    float g;
    float b;
    float difuseFactor(Vertex point, Vertex normal);
    float specularFactor(Vertex point, Vertex normal);
    Point difuseIntensity(Vertex point, Vertex normal, Material mat);
    Point specularIntensity(Vertex point, Vertex normal, Material mat);
    void setCameraCoordinates(Matrix worldToCamera);
    void setWorldCoordinates(Matrix cameraToWorld);
    Lighting();
};

class AmbientLighting: public Lighting
{
    public:
        float r;
        float g;
        float b;
        Point ambientIntensity(Vertex point, Material mat);
        AmbientLighting();
        AmbientLighting(float r, float g, float b);
};

class SpotLighting: public Lighting
{
    public:
        float r;
        float g;
        float b;
        Vertex position;
        Vertex direction;
        float angle;
        SpotLighting(float r, float g, float b, Vertex position, Vertex direction, float angle);
        float difuseFactor(Vertex point, Vertex normal);
        float specularFactor(Vertex point, Vertex normal);
        Point difuseIntensity(Vertex point, Vertex normal, Material mat);
        Point specularIntensity(Vertex point, Vertex normal, Material mat);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
};

class FarLighting: public Lighting
{
    public:
        float r;
        float g;
        float b;
        Vertex direction;
        FarLighting(float r, float g, float b, Vertex direction);
        float difuseFactor(Vertex point, Vertex normal);
        float specularFactor(Vertex point, Vertex normal);
        Point difuseIntensity(Vertex point, Vertex normal, Material mat);
        Point specularIntensity(Vertex point, Vertex normal, Material mat);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
};

class PointLighting: public Lighting
{
    public:
        float r;
        float g;
        float b;
        Vertex position;
        PointLighting(float r, float g, float b, Vertex position);
        float difuseFactor(Vertex point, Vertex normal);
        float specularFactor(Vertex point, Vertex normal);
        Point difuseIntensity(Vertex point, Vertex normal, Material mat);
        Point specularIntensity(Vertex point, Vertex normal, Material mat);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
};