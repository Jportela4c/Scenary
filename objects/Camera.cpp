#include "Camera.hpp"

Camera::Camera(){};
Camera::Camera(Point eye, Point lookAt, Point viewUp)
{
    this->eye = eye;
    this->lookAt = lookAt;
    this->viewUp = viewUp;

    Point k = (eye - lookAt).normalized();

    Point i = (viewUp.cross(k)).normalized();
    Point j = (k.cross(i)).normalized();
};

Matrix Camera::worldToCamera()
{
    Matrix worldToCamera;
    worldToCamera << i[0], i[1], i[2], -i.dot(eye),
                    j[0], j[1], j[2], -j.dot(eye),
                    k[0], k[1], k[2], -k.dot(eye),
                    0, 0, 0, 1;
    return worldToCamera;
};

Matrix Camera::cameraToWorld(){
    Matrix cameraToWorld;
    cameraToWorld << i[0], j[0], k[0], eye[0],
                    i[1], j[1], k[1], eye[1],
                    i[2], j[2], k[2], eye[2],
                    0, 0, 0, 1;
    return cameraToWorld;
};

void Camera::update(){

    Point k1 = (eye - lookAt).normalized();

    Point i = (viewUp.cross(k1)).normalized();
    Point j = (k1.cross(i)).normalized();

    Vertex k = Vertex(k[0], k[1], k[2], 1);
    Vertex i = Vertex(i[0], i[1], i[2], 1.0);
    Vertex j = Vertex(j[0], j[1], j[2], 1.0);
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

void Camera::moveTo(Point eye)
{
    this->eye = eye;
    update();
};