#include "Aux.hpp"
#include "Camera.hpp"
#include "Lighting.hpp"

class Scenary
{
    public:
        Camera camera;
        vector<Shape*> shapes;    
        AmbientLighting ambientLight;
        vector<Lighting> lights;
        Point canvas[HEIGHT*WIDTH];
        float frame[HEIGHT*WIDTH*3];
        Scenary();
        void addShape(Shape* shape);
        void addLight(Lighting light);
        void setCamera(Camera camera);
        void setAmbientLight(AmbientLighting ambientLight);
        void setWorldCoordinates();
        void setCameraCoordinates();
        void rayCasting();
};