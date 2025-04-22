#include <cstdlib>
#include <iostream>
#include <string>
#include "graph.h"

using namespace std;

Graph<int>* getDefaultGraph()
{
    Graph<int> *gr = new Graph<int>(8);
    gr->changeEdge(0, 1, 5);
    gr->changeEdge(0, 2, 9);
    gr->changeEdge(1, 2, 3);
    gr->changeEdge(1, 4, 1);
    gr->changeEdge(2, 3, 2);
    gr->changeEdge(3, 4, 5);
    gr->changeEdge(3, 7, 4);
    gr->changeEdge(4, 5, 9);
    gr->changeEdge(1, 5, 8);
    gr->changeEdge(5, 6, 3);
    gr->changeEdge(6, 7, 4);
    return gr;
}
DirGraph<int>* getDefaultDirGraph()
{
    DirGraph<int> *gr = new DirGraph<int>(8);
    gr->changeEdge(0, 1, 5);
    gr->changeEdge(0, 2, 9);
    gr->changeEdge(1, 2, 3);
    gr->changeEdge(1, 4, 1);
    gr->changeEdge(2, 3, 2);
    gr->changeEdge(3, 4, 5);
    gr->changeEdge(3, 7, 4);
    gr->changeEdge(4, 5, 9);
    gr->changeEdge(1, 5, 8);
    gr->changeEdge(5, 6, 3);
    gr->changeEdge(6, 7, 4);
    return gr;
}
void editGraph(Graph<int> *gr)
{
    int choose = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    while(true)
    {
        cout << "Adjacency matrix:" << endl;
        cout << gr->toString();
        cout << endl;
        cout << "Enter 1 to add or change an edge" << endl;
        cout << "Enter anything else to continue" << endl;
        cin >> choose;
        cout << endl;
        switch(choose)
        {
            case 1:
                cout << "Enter the first vertex" << endl;
                cin >> vert1;
                cout << endl;
                cout << "Enter the second vertex" << endl;
                cin >> vert2;
                cout << endl;
                cout << "Enter a weight of the edge" << endl;
                cin >> weight;
                cout << endl;
                gr->changeEdge(vert1, vert2, weight);
                break;
            default:
                return;
        }
    }
}
void editDirGraph(DirGraph<int> *gr)
{
    int choose = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    while(true)
    {
        cout << "Adjacency matrix:" << endl;
        cout << gr->toString();
        cout << endl;
        cout << "Enter 1 to add or change an edge" << endl;
        cout << "Enter anything else to continue" << endl;
        cin >> choose;
        cout << endl;
        switch(choose)
        {
            case 1:
                cout << "Enter the first vertex" << endl;
                cin >> vert1;
                cout << endl;
                cout << "Enter the second vertex" << endl;
                cin >> vert2;
                cout << endl;
                cout << "Enter a weight of the edge" << endl;
                cin >> weight;
                cout << endl;
                gr->changeEdge(vert1, vert2, weight);
                break;
            default:
                return;
        }
    }
}

void interfaceGraph()
{
    int choose = 0;
    int i = 0;
    int j = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    Graph<int> *gr;
    ArraySequence<int> *path;

    cout << "Enter 1 to get a default graph" << endl;
    cout << "Enter 2 to create a custom graph" << endl;
    cout << "Enter a different number to quit" << endl;
    cin >> choose;
    cout << endl;
    switch (choose)
    {
        case 1:
            gr = getDefaultGraph();
            break;
        case 2:
            cout << "Enter a number of vertexes" << endl;
            cin >> choose;
            cout << endl;
            gr = new Graph<int>(choose);
            break;
        default:
            return;
    }
    editGraph(gr);
    while(true)
    {
        cout << "Enter 1 to find a path on the graph:" << endl;
        cout << "Enter 3 to add or change an edge" << endl;
        cout << "Enter a different number to quit" << endl;
        cin >> choose;
        cout << endl;
        switch(choose)
        {
            case 1:
                cout << "Enter a starting vertex:" << endl;
                cin >> i;
                cout << endl;
                cout << "Enter an ending vertex" << endl;
                cin >> j;
                cout << endl;
                path = gr->getPath(i, j);
                cout << "The shortest path:" << endl;
                for (int i = 0; i < path->getSize(); i++)
                    cout << path->get(i) << " ";
                cout << endl;
                cout << "It's weight: " << gr->getPathWeight(path) << endl;
                break;
            case 3:
                cout << "Enter the first vertex" << endl;
                cin >> vert1;
                cout << endl;
                cout << "Enter the second vertex" << endl;
                cin >> vert2;
                cout << endl;
                cout << "Enter a weight of the edge" << endl;
                cin >> weight;
                cout << endl;
                gr->changeEdge(vert1, vert2, weight);
                cout << "Adjacency matrix:" << endl;
                cout << gr->toString();
                cout << endl;
                break;
            default:
                return;
        }
    }
}
void interfaceDirGraph()
{
    int choose = 0;
    int i = 0;
    int j = 0;
    int vert1 = 0;
    int vert2 = 0;
    int weight = 0;
    DirGraph<int> *gr;
    ArraySequence<int> *path;
    ArraySequence<int> *ts;

    while(true)
    {
        cout << "Enter 1 to get a default directed graph" << endl;
        cout << "Enter 2 to create a custom directed graph" << endl;
        cout << "Enter a different number to quit" << endl;
        cin >> choose;
        cout << endl;

        switch (choose)
        {
            case 1:
                gr = getDefaultDirGraph();
                break;
            case 2:
                cout << "Enter a number of vertexes" << endl;
                cin >> choose;
                cout << endl;
                gr = new DirGraph<int>(choose);
                break;
            default:
                return;
        }
        editDirGraph(gr);
        while(true)
        {
            cout << "Enter 1 to find a path on the directed graph:" << endl;
            cout << "Enter 2 to topologically sort the graph" << endl;
            cout << "Enter 3 to add or change an edge" << endl;
            cout << "Enter a different number to quit" << endl;
            cin >> choose;
            cout << endl;
            switch(choose)
            {
                case 1:
                    cout << "Enter a starting vertex:" << endl;
                    cin >> i;
                    cout << endl;
                    cout << "Enter an ending vertex" << endl;
                    cin >> j;
                    cout << endl;
                    path = gr->getPath(i, j);
                    cout << "The shortest path:" << endl;
                    for (int i = 0; i < path->getSize(); i++)
                        cout << path->get(i) << " ";
                    cout << endl;
                    cout << "It's weight: " << gr->getPathWeight(path) << endl;
                    break;
                case 2:
                    ts = gr->getTopologicalSort();
                    cout << "The Topological sort:" << endl;
                    for (int i = 0; i < ts->getSize(); i++)
                        cout << ts->get(i) << " ";
                    cout << endl;
                    break;
                case 3:
                    cout << "Enter the first vertex" << endl;
                    cin >> vert1;
                    cout << endl;
                    cout << "Enter the second vertex" << endl;
                    cin >> vert2;
                    cout << endl;
                    cout << "Enter a weight of the edge" << endl;
                    cin >> weight;
                    cout << endl;
                    gr->changeEdge(vert1, vert2, weight);
                    cout << "Adjacency matrix:" << endl;
                    cout << gr->toString();
                    cout << endl;
                    break;
                default:
                    return;
            }
        }
    }
}

int main(int argc, const char *argv[])
{
    int choose = 0;

    cout << "Enter 1 to test directed graphs" << endl;
    cout << "Enter 2 to test undirected graphs" << endl;
    cin >> choose;
    cout << endl;

    switch(choose)
    {
        case 1:
            interfaceDirGraph();
            break;
        case 2:
            interfaceGraph();
            break;
        default:
            break;
    }

	return 0;
}