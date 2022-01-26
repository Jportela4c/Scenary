#include "Aux.hpp"

class Camera {
    public:
        Vertex eye;
        Vertex lookAt;
        Vertex viewUp;
        Vertex k;
        Vertex i;
        Vertex j;

        Camera();
        Camera(Vertex eye, Vertex lookAt, Vertex viewUp);
        Matrix worldToCamera();
        Matrix cameraToWorld();
        void update();
        void moveX(float x);
        void moveY(float y);
        void moveZ(float z);
        void moveTo(Vertex eye);
};