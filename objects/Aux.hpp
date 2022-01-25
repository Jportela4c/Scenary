#include <eigen3/Eigen/Dense>

typedef Eigen::Vector3f Point;
typedef Eigen::Vector4f Vertex;
typedef Eigen::Matrix4f Matrix;
class Face {
    public:
    Face();
    Face(Vertex v1, Vertex v2, Vertex v3);
    Vertex v1;
    Vertex v2;
    Vertex v1v2;
    Vertex v1v3;
    Vertex v2v3;
    Vertex v3v1;
    Vertex v3;
    Vertex normal;
    Vertex intersection(Vertex v1, Vertex v2);
    bool validate(Vertex v1, Vertex v2, Vertex v3);
};