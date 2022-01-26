#include "Scenary.hpp"

Scenary::Scenary() {};

void Scenary::addShape(Shape shape) {
    this->shapes.push_back(shape);
}

void Scenary::addLight(Lighting light) {
    this->lights.push_back(light);
}

void Scenary::setCamera(Camera camera) {
    this->camera = camera;
}

void Scenary::setAmbientLight(AmbientLighting ambientLight) {
    this->ambientLight = ambientLight;
}
