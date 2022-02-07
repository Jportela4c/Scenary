#include "Aux.hpp"

class Lighting
{
    public:
    float r;
    float g;
    float b;
    float difuseFactor(Point point, Point normal);
    float specularFactor(Point point, Point normal);
    Point difuseIntensity(Point point, Point normal, Material mat);
    Point specularIntensity(Point point, Point normal, Material mat);
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
        Point ambientIntensity(Point point, Material mat);
        AmbientLighting();
        AmbientLighting(float r, float g, float b);
};

class SpotLighting: public Lighting
{
    public:
        float r;
        float g;
        float b;
        Point position;
        Point direction;
        float angle;
        SpotLighting(float r, float g, float b, Point position, Point direction, float angle);
        float difuseFactor(Point point, Point normal);
        float specularFactor(Point point, Point normal);
        Point difuseIntensity(Point point, Point normal, Material mat);
        Point specularIntensity(Point point, Point normal, Material mat);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
};

class FarLighting: public Lighting
{
    public:
        float r;
        float g;
        float b;
        Point direction;
        FarLighting(float r, float g, float b, Point direction);
        float difuseFactor(Point point, Point normal);
        float specularFactor(Point point, Point normal);
        Point difuseIntensity(Point point, Point normal, Material mat);
        Point specularIntensity(Point point, Point normal, Material mat);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
};

class PointLighting: public Lighting
{
    public:
        float r;
        float g;
        float b;
        Point position;
        PointLighting(float r, float g, float b, Point position);
        float difuseFactor(Point point, Point normal);
        float specularFactor(Point point, Point normal);
        Point difuseIntensity(Point point, Point normal, Material mat);
        Point specularIntensity(Point point, Point normal, Material mat);
        void setCameraCoordinates(Matrix worldToCamera);
        void setWorldCoordinates(Matrix cameraToWorld);
};