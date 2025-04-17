#ifndef GRAPH_H
#define GRAPH_H

#include <iostream>
#include <iomanip>
#include <string>
#include <queue>  // required for bfsM
using namespace std;

struct vertex;  // forward declaration for edge

struct edge {
    vertex* dest;
    edge* eNext;
    int weight;
};

struct vertex {
    char data;
    vertex* vNext;
    edge* aHead;
    short visited;
};

class Graph {
private:
    vertex* vertices;
    int** adjMatrix;
    bool* visited;
    int maxVertices;
    int numVertices;

public:
    Graph(int maxV);
    ~Graph();

    // core operations
    void addVertex(char data);
    void addEdge(char src, char dest, int weight);
    void removeVertex(char data);
    void removeEdge(char src, char dest);

    // display
    void displayAdjList();
    void displayAdjMatrix();

    // traversal
    void bfsL(char start);
    void bfsM(char start);
    void dfsL(char start);
    void dfsM(char start);

    // extra credit
    bool detectCycle();
    bool detectCycleUtil(vertex* v, vertex* parent);
    void connectedComponents();
    void dfsComponent(vertex* v);
};

#endif
