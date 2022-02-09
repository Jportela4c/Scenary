#include "Scenary.hpp"
Scenary::Scenary(){

};

void Scenary::addShape(Shape* shape) 
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
        this->shapes[i]->setWorldCoordinates(this->camera.cameraToWorld());
    }
    for (int i = 0; i < this->lights.size(); i++) {
        this->lights[i].setWorldCoordinates(this->camera.cameraToWorld());
    }
};

void Scenary::setCameraCoordinates()
{
    for (int i = 0; i < this->shapes.size(); i++) {
        this->shapes[i]->setCameraCoordinates(this->camera.worldToCamera());
    }
    for (int i = 0; i < this->lights.size(); i++) {
        this->lights[i].setCameraCoordinates(this->camera.worldToCamera());
    }
};

void Scenary::rayCasting() 
{
    this->setCameraCoordinates();
    Point intersect;
    for (int i = 0; i < HEIGHT; i++)
    {
        for (int j = 0; j < WIDTH; j++)
        {
            Point rayOrigin = this->camera.eye;
            Point rayDirection = this->canvas[i*WIDTH + j] - rayOrigin;
            Point intersect = Point(MAXFLOAT, MAXFLOAT, MAXFLOAT);
            float closestDistance = MAXFLOAT;
            for (int k = 0; k < this->shapes.size(); k++)
            {
                Point c_intersect = this->shapes[k]->rayIntersect(rayOrigin, rayDirection);
                float d = (c_intersect - rayOrigin).norm();
                if (d < closestDistance)
                {
                    closestDistance = d;
                    intersect = c_intersect;
                }
            }

            if (intersect[0] < MAXFLOAT)
            {
                Point intensity = this->ambientLight.ambientIntensity(intersect, this->shapes[i]->mat);
                // Point intersect_point = Point(0,0,0);
                // intersect_point[0] = this->canvas(j, k)[0];
                // intersect_point[1] = this->canvas(j, k)[1];
                // intersect_point[2] = this->canvas(j, k)[2];
                for (int l = 0; l < this->lights.size(); l++)
                {
                    intensity += this->lights[l].difuseIntensity(intersect, this->shapes[i]->normal(this->canvas[i*WIDTH + j]), this->shapes[i]->mat);
                    intensity += this->lights[l].specularIntensity(intersect, this->shapes[i]->normal(this->canvas[i*WIDTH + j]), this->shapes[i]->mat);
                }
                int position = j*3*WIDTH+i*3;
                this->frame[position] = intensity[0];
                this->frame[position+1] = intensity[1];
                this->frame[position+2] = intensity[2];
            }
            else
            {
                int position = j*3*WIDTH+i*3;
                this->frame[position] = BG[0];
                this->frame[position+1] = BG[1];
                this->frame[position+2] = BG[2];
            }
        }
    }  
};
