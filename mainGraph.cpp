#include <iostream>
#include "graph.h"

using namespace std;

int main() {
    Graph g(10);

    g.addVertex('A');
    g.addVertex('B');
    g.addVertex('C');
    g.addVertex('D');
    g.addVertex('E');
    g.addVertex('F');
    g.addVertex('G');
    g.addVertex('H');
    g.addVertex('I');
    g.addVertex('J');

    g.addEdge('A', 'B', 1);
    g.addEdge('A', 'C', 2);
    g.addEdge('A', 'H', 7);
    g.addEdge('B', 'D', 3);
    g.addEdge('B', 'G', 8);
    g.addEdge('C', 'D', 5);
    g.addEdge('C', 'E', 4);
    g.addEdge('C', 'F', 12);
    g.addEdge('C', 'H', 14);
    g.addEdge('D', 'E', 6);
    g.addEdge('D', 'F', 13);
    g.addEdge('E', 'C', 4);
    g.addEdge('F', 'I', 9);
    g.addEdge('F', 'J', 10);
    g.addEdge('G', 'B', 8);
    g.addEdge('H', 'A', 7);
    g.addEdge('I', 'J', 11);
    g.addEdge('J', 'F', 10);

    g.displayAdjList();
    g.displayAdjMatrix();

    cout << "\nRemoving edge C - H\n";
    g.removeEdge('C', 'H');
    g.displayAdjList();
    g.displayAdjMatrix();

    g.bfsL('A');
    g.bfsM('A');
    g.dfsL('A');
    g.dfsM('A');

    cout << (g.detectCycle() ? "Cycle detected\n" : "No cycle detected\n");
    g.connectedComponents();

    return 0;
}