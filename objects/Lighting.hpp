#include "Aux.hpp"

class Lighting
{
    public:
    virtual void setCameraCoordinates(Matrix worldToCamera);
    virtual void setWorldCoordinates(Matrix cameraToWorld);
    virtual float difuseFactor(Vertex point, Vertex normal);
    virtual float specularFactor(Vertex point, Vertex normal);
    virtual Point difuseIntensity(Vertex point, Vertex normal, Material mat);
    virtual Point specularIntensity(Vertex point, Vertex normal, Material mat);
};

class AmbientLighting: public Lighting
{
    public:
        float r;
        float g;
        float b;
        AmbientLighting();
        AmbientLighting(float r, float g, float b);
        Point ambientIntensity(Vertex point, Material mat);
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
        SpotLighting();
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
        FarLighting();
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
        PointLighting();
        PointLighting(float r, float g, float b, Vertex position);
        float difuseFactor(Vertex point, Vertex normal);
        float specularFactor(Vertex point, Vertex normal);
        Point difuseIntensity(Vertex point, Vertex normal, Material mat);
        Point specularIntensity(Vertex point, Vertex normal, Material mat);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
};