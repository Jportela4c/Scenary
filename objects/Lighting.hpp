#include "Aux.hpp"

class Lighting
{
    
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
        float difuseFactor(Vertex point);
        float specularFactor(Vertex point);
        Point difuseIntensity(Vertex point, Material mat);
        Point specularIntensity(Vertex point, Material mat);
        void worldToCamera(Matrix worldToCamera);
        void cameraToWorld(Matrix cameraToWorld);
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
        float difuseFactor(Vertex point);
        float specularFactor(Vertex point);
        Point difuseIntensity(Vertex point, Material mat);
        Point specularIntensity(Vertex point, Material mat);
        void worldToCamera(Matrix worldToCamera);
        void cameraToWorld(Matrix cameraToWorld);
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
        float difuseFactor(Vertex point);
        float specularFactor(Vertex point);
        Point difuseIntensity(Vertex point, Material mat);
        Point specularIntensity(Vertex point, Material mat);
        void worldToCamera(Matrix worldToCamera);
        void cameraToWorld(Matrix cameraToWorld);
};