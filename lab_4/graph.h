#pragma once

#include "dirgraph.h"

using namespace std;

template <class T>
class Graph : virtual public DirGraph<T>
{
public:
    Graph(int size): DirGraph<T>(size) {};
    void changeEdge(int vert1, int vert2, T weight)
    {
        if(vert1 == vert2) throw out_of_range("INCORRECT INDEX");
        this->adjMatrix->Set(weight, vert1, vert2);
        this->adjMatrix->Set(weight, vert2, vert1);
    }
    ArraySequence<int> topologicalSort()
    {
        throw "CANNOT BE TOPOLOGICALLY SORTED";
    }
};