#include "Aux.hpp"

class Camera {
    public:
        Point eye;
        Point lookAt;
        Point viewUp;
        Point k;
        Point i;
        Point j;
        Camera();
        Camera(Point eye, Point lookAt, Point viewUp);
        Matrix worldToCamera();
        Matrix cameraToWorld();
        void update();
        void moveX(float x);
        void moveY(float y);
        void moveZ(float z);
        void moveTo(Point eye);
};