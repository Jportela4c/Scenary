#include <eigen3/Eigen/Dense>

typedef Eigen::Vector4f Vertex;
typedef Eigen::Matrix4f Matrix;

class Face {
    public:
    Face();
    Face(Vertex v1, Vertex v2, Vertex v3);
    Vertex v1;
    Vertex v2;
    Vertex v3;
};