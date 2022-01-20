#include "Aux.hpp"



Face::Face(){
    v1 = Vertex(0,0,0,1);
    v2 = Vertex(0,0,0,1);
    v3 = Vertex(0,0,0,1);
};

Face::Face(Vertex vertex1, Vertex vertex2, Vertex vertex3): v1(vertex1), v2(vertex2), v3(vertex3)
{
    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;
}

