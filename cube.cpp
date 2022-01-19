#include "cube.hpp"
class Edge {
    public:
    Vector4f v_i, v_f;

    Edge(){
        v_i = Vector4f();
        v_f = Vector4f();
    }
    Edge(Vector4f v_i, Vector4f v_f){
        this->v_i = v_i;
        this->v_f = v_f;
    }
};


class Face {
    public:
    Edge e_1, e_2, e_3;

    Face(){
        e_1 = Edge();
        e_2 = Edge();
        e_3 = Edge();
    }
    Face(Edge e_1, Edge e_2, Edge e_3){
        this->e_1 = e_1;
        this->e_2 = e_2;
        this->e_3 = e_3;
    }
};

class Cube{
    public:

    Vector4f vertices[8];
    Edge arestas[18];
    Face faces[12];

    Cube(){
        for(int i = 0; i < 8; i++){
            vertices[i] = Vector4f(1, 1, 1, 1);
        }
        for(int i = 0; i < 18; i++){
            arestas[i] = Edge();
        }
        for(int i = 0; i < 12; i++){
            faces[i] = Face();
        }
    }

    Cube::Cube(float side){
        float s = side/2;
        vertices[0] = Vector4f(-s, -s, -s, 1);
        vertices[1] = Vector4f(-s, -s, s, 1);
        vertices[2] = Vector4f(s, -s, s, 1);
        vertices[3] = Vector4f(s, -s, -s, 1);
        vertices[4] = Vector4f(-s, s, -s, 1);
        vertices[5] = Vector4f(-s, s, s, 1);
        vertices[6] = Vector4f(s, s, s, 1);
        vertices[7] = Vector4f(s, s, -s, 1);

        arestas[0] = Edge(vertices[0], vertices[1]);
        arestas[1] = Edge(vertices[1], vertices[2]);
        arestas[2] = Edge(vertices[2], vertices[3]);
        arestas[3] = Edge(vertices[3], vertices[0]);
        arestas[4] = Edge(vertices[4], vertices[5]);
        arestas[5] = Edge(vertices[5], vertices[6]);
        arestas[6] = Edge(vertices[6], vertices[7]);
        arestas[7] = Edge(vertices[7], vertices[4]);
        arestas[8] = Edge(vertices[0], vertices[4]);
        arestas[9] = Edge(vertices[1], vertices[5]);
        arestas[10] = Edge(vertices[2], vertices[6]);
        arestas[11] = Edge(vertices[3], vertices[7]);
        arestas[12] = Edge(vertices[2], vertices[7]);
        arestas[13] = Edge(vertices[5], vertices[7]);
        arestas[14] = Edge(vertices[5], vertices[2]);
        arestas[15] = Edge(vertices[1], vertices[4]);
        arestas[16] = Edge(vertices[1], vertices[3]);
        arestas[17] = Edge(vertices[3], vertices[4]);

        faces[0] = Face(arestas[6], arestas[10], arestas[12]);
        faces[1] = Face(arestas[12], arestas[2], arestas[11]);
        faces[2] = Face(arestas[7], arestas[4], arestas[13]);
        faces[3] = Face(arestas[13], arestas[5], arestas[6]);
        faces[4] = Face(arestas[5], arestas[14], arestas[10]);
        faces[5] = Face(arestas[9], arestas[1], arestas[14]);
        faces[6] = Face(arestas[4], arestas[15], arestas[9]);
        faces[7] = Face(arestas[8], arestas[0], arestas[15]);
        faces[8] = Face(arestas[0], arestas[11], arestas[8]);
        faces[9] = Face(arestas[1], arestas[16], arestas[2]);
        faces[10] = Face(arestas[11], arestas[17], arestas[7]);
        faces[11] = Face(arestas[3], arestas[8], arestas[17]);
    }

};