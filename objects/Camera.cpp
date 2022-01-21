#include "Camera.hpp"

Camera::Camera(){};

Camera::Camera(Vertex eye, Vertex lookAt, Vertex viewUp)
{
    this->eye = eye;
    this->lookAt = lookAt;
    this->viewUp = viewUp;

    k = (eye - lookAt).normalized();
    i = (viewUp.cross(k)).normalized();
    j = k.cross(i);
};

Matrix Camera::worldToCamera()
{
    Matrix worldToCamera;
    worldToCamera << i.x(), i.y(), i.z(), -i.dot(eye),
                    j.x(), j.y(), j.z(), -j.dot(eye),
                    k.x(), k.y(), k.z(), -k.dot(eye),
                    0, 0, 0, 1;
    return worldToCamera;
};

Matrix Camera::cameraToWorld(){
    Matrix cameraToWorld;
    cameraToWorld << i.x(), j.x(), k.x(), eye.x(),
                    i.y(), j.y(), k.y(), eye.y(),
                    i.z(), j.z(), k.z(), eye.z(),
                    0, 0, 0, 1;
    return cameraToWorld;
};


void Camera::update(){
    k = (eye - lookAt).normalized();
    i = (viewUp.cross(k)).normalized();
    j = k.cross(i);
};


void Camera::moveX(float x)
{
    this->eye.x() += x;
    update();
};

void Camera::moveY(float y)
{
    this->eye.y() += y;
    update();
};

void Camera::moveZ(float z)
{
    this->eye.z() += z;
    update();
};

void Camera::moveTo(Vertex eye)
{
    this->eye = eye;
    update();
};