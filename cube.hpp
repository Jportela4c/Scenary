#include <eigen3/Eigen/Dense>

using namespace Eigen;

class Edge
{
    Vector4f v_i, v_f;
};
class Face
{
    Edge e_1, e_2, e_3;
};
class Cube
{
    Vector4f vertices[8];
    Edge arestas[18];
    Face faces[12];
};