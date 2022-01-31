#include "Scenary.hpp"

Scenary::Scenary() {};

void Scenary::addShape(Shape shape) 
{
    this->shapes.push_back(shape);
};

void Scenary::addLight(Lighting light) 
{
    this->lights.push_back(light);
};

void Scenary::setCamera(Camera camera) 
{
    this->camera = camera;
};

void Scenary::setAmbientLight(AmbientLighting ambientLight) 
{
    this->ambientLight = ambientLight;
};

void Scenary::setWorldCoordinates() 
{
    for (int i = 0; i < this->shapes.size(); i++) {
        this->shapes[i].setWorldCoordinates(this->camera.cameraToWorld());
    }
    for (int i = 0; i < this->lights.size(); i++) {
        this->lights[i].setWorldCoordinates(this->camera.cameraToWorld());
    }
};

void Scenary::setCameraCoordinates()
{
    for (int i = 0; i < this->shapes.size(); i++) {
        this->shapes[i].setCameraCoordinates(this->camera.worldToCamera());
    }
    for (int i = 0; i < this->lights.size(); i++) {
        this->lights[i].setCameraCoordinates(this->camera.worldToCamera());
    }
};

void Scenary::rayCasting() 
{
    this->setCameraCoordinates();
    this->setWorldCoordinates();
    Vertex intersect;
    for (int i = 0; i < this->shapes.size(); i++)
    {
        for (int j = 0; j < this->GRID.rows(); j++)
        {
            for (int k = 0; k < this->GRID.cols(); k++)
            {
                Vertex rayOrigin = this->camera.eye;
                Vertex rayDirection = this->GRID(j, k) - rayOrigin;
                intersect = this->shapes[i].rayIntercect(rayOrigin, rayDirection);
                if (intersect[3] != -1)
                {
                    Point intensity = this->ambientLight.ambientIntensity(intersect, this->shapes[i].mat);
                    for (int l = 0; l < this->lights.size(); l++)
                    {
                        intensity += this->lights[l].difuseIntensity(intersect, this->shapes[i].mat);
                        intensity += this->lights[l].specularIntensity(intersect, this->shapes[i].mat);
                    }
                    this->GRID(j, k)[0] = intensity[0];
                    this->GRID(j, k)[1] = intensity[1];
                    this->GRID(j, k)[2] = intensity[2];
                }
                else
                {
                    this->GRID(j, k) = Vertex(-1, -1, -1); /*colocar aqui a cor do background*/
                }
            }
        }
    }  
};
