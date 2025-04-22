#pragma once

#include "sequence.h"
#include "matrix.h"

using namespace std;

template <class T>
class DirGraph
{
protected:
    Matrix<T> *adjMatrix;
private:
    void _ts_(int v, bool visited[], ArraySequence<int> *stack)
    {
        visited[v] = true;
        for(int i = 0; i < this->getSize(); i++)
        {
            if(this->adjMatrix->Get(v, i) != 0)
            {
                if(!visited[i]) this->_ts_(i, visited, stack);
            }
        }
        stack->prepend(v);
    }
public:
    DirGraph(int size)
    {
        this->adjMatrix = new Matrix<T>(size, size);
    }
    ~DirGraph() = default;
    void changeEdge(int vert1, int vert2, T weight)
    {
        if(vert1 == vert2) throw out_of_range("INCORRECT INDEX");
        this->adjMatrix->Set(weight, vert1, vert2);
    }
    int getSize()
    {
        return this->adjMatrix->GetRows();
    }
    string toString()
    {
        return this->adjMatrix->toString();
    }
    ArraySequence<int>* getPath(int vert1, int vert2)
    {
        const int INF = 100000000;
        ArraySequence<int> dist(this->getSize());
        ArraySequence<bool> beenTo(this->getSize());
        ArraySequence<int> parent(this->getSize());
        for(int i = 0; i < this->getSize(); i++)
        {
            dist.set(INF, i);
            beenTo.set(false, i);
            parent.set(-1, i);
        }
        int min = 0;
        int index_min = 0;
        int temp = 0;
        dist.set(0, vert1);

        for(int i = 0; i < this->getSize(); i++)
        {
            min = INF;
            for(int j = 0; j < this->getSize(); ++j)
            {
                if(!beenTo.get(j) && dist.get(j) < min)
                {
                    min = dist.get(j);
                    index_min = j;
                }
            }
            beenTo.set(true, index_min);
            for (int j = 0; j < this->getSize(); ++j)
            {
                if (adjMatrix->Get(index_min, j) > 0)
                {
                    temp = min + adjMatrix->Get(index_min, j);
                    if (temp < dist.get(j))
                    {
                        dist.set(temp, j);
                        parent.set(index_min, j);
                    }
                }
            }
            if (beenTo.get(vert2) == true) break;
        }
        ArraySequence<int> *path = new ArraySequence<int>(0);
        if (parent.get(vert2) == -1)
        {
            path->append(-1);
            return path;
        }
        for(int i = vert2; i != -1; i = parent.get(i))
            path->prepend(i);
        return path;
    }
    T getPathWeight(ArraySequence<int> *path)
    {
        T result = 0;
        for (int i = 0; i < path->getSize() - 1; i++)
        {
            if (this->adjMatrix->Get(path->get(i), path->get(i + 1)) == 0) throw invalid_argument("INCORRECT PATH");
            result += this->adjMatrix->Get(path->get(i), path->get(i + 1));
        }
        return result;
    }
    ArraySequence<int>* getTopologicalSort()
    {
        ArraySequence<int> *stack;
        stack = new ArraySequence<int>();
        bool *visited = new bool[this->getSize()];
        for (int i = 0; i < this->getSize(); i++)
            visited[i] = false;
        for (int i = 0; i < this->getSize(); i++)
            if (visited[i] == false)
            {
                this->_ts_(i, visited, stack);
            }
        return stack;
    }
};