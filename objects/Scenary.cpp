#include "Scenary.hpp"

Scenary::Scenary(){

};

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
        for (int j = 0; j < this->canvas.rows(); j++)
        {
            for (int k = 0; k < this->canvas.cols(); k++)
            {
                Vertex rayOrigin = this->camera.eye;
                Point rayOriginp = Point(rayOrigin[0], rayOrigin[1], rayOrigin[2]);
                Point rayDirectionp = this->canvas(j, k) - rayOriginp;
                Vertex rayDirection = Vertex(rayDirectionp[0], rayDirectionp[1], rayDirectionp[2], 1.0);
                intersect = this->shapes[i].rayIntercect(rayOrigin, rayDirection);
                if (intersect[3] != -1)
                {
                    Point intensity = this->ambientLight.ambientIntensity(intersect, this->shapes[i].mat);
                    Vertex intersect_point = Vertex(0,0,0,0);
                    intersect_point[0] = this->canvas(j, k)[0];
                    intersect_point[1] = this->canvas(j, k)[1];
                    intersect_point[2] = this->canvas(j, k)[2];
                    intersect_point[3] = 1;
                    for (int l = 0; l < this->lights.size(); l++)
                    {

                        intensity += this->lights[l].difuseIntensity(intersect, this->shapes[i].normal(intersect_point), this->shapes[i].mat);
                        intensity += this->lights[l].specularIntensity(intersect, this->shapes[i].normal(intersect_point), this->shapes[i].mat);
                    }
                    this->frame(j, k)[0] = intensity[0];
                    this->frame(j, k)[1] = intensity[1];
                    this->frame(j, k)[2] = intensity[2];
                }
                else
                {
                    this->frame(j, k) = BG; /*colocar aqui a cor do background*/
                }
            }
        }
    }  
};
