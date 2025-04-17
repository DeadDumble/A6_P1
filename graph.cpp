#include "graph.h"
#include "sqll.h"
#include <queue>

Graph::Graph(int maxV)
{
    maxVertices = maxV;
    numVertices = 0;
    vertices = nullptr;

    adjMatrix = new int*[maxVertices]; // pointer of rows
    // each int* stores a row
    for(int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i] = new int[maxVertices]; // create a new row (array of ints)
        for(int j = 0; j < maxVertices; j++)
            adjMatrix[i][j] = 0;
    }

    visited = new bool[maxVertices] {false};    
}

Graph::~Graph()
{
    delete[] visited;

    for(int i = 0; i < maxVertices; i++)
    {
        delete[] adjMatrix[i];
    }
    delete[] adjMatrix;

    vertex* tempVertex;
    while (vertices) 
    {
        edge* tempEdge;
        // free the memory of the neighbor list of that vertex
        while(vertices->aHead)
        {
            tempEdge = vertices->aHead;
            vertices->aHead = vertices->aHead->eNext;
            delete tempEdge;
        }
        // free that vertex itself
        tempVertex = vertices;
        vertices = vertices->vNext;
        delete tempVertex;

    }
}

void Graph::addVertex(char data)
{
    if(numVertices >= maxVertices)
    {
        cout << "Max number of vertices reached!" << endl;
        return;
    }

    vertex* newVertex = new vertex;
    newVertex->data = data;
    newVertex->vNext = vertices;
    newVertex->aHead = nullptr;
    newVertex->visited = 0;
    vertices = newVertex;

    numVertices++;
}

void Graph::addEdge(char src, char dest, int weight)
{
    vertex* srcVertex = vertices;
    vertex* destVertex = vertices;

    // find src and dest vertices
    while(srcVertex && srcVertex->data != src)
    {
        srcVertex = srcVertex->vNext;
    }
    while(destVertex && destVertex->data != dest)
    {
        destVertex = destVertex->vNext;
    }

    if(!srcVertex || !destVertex)
    {
        cout << "Vertices not found - can't add an edge" << endl;
        return;
    }

    // Adj list - undirected graph
    edge* newEdge = new edge;
    newEdge->dest = destVertex;
    newEdge->weight = weight;
    newEdge->eNext = srcVertex->aHead;
    srcVertex->aHead = newEdge;

    // Since undirected, add the reverse edge as well
    newEdge = new edge;
    newEdge->dest = srcVertex;
    newEdge->weight = weight;
    newEdge->eNext = destVertex->aHead;
    destVertex->aHead = newEdge;

    // Adj Matrix
    int srcIndex = srcVertex->data - 'A';
    int destIndex = destVertex->data - 'A';
    adjMatrix[srcIndex][destIndex] = weight;
    adjMatrix[destIndex][srcIndex] = weight;
}

void Graph::removeVertex(char data)
{
    // find the vertex
    vertex* temp = vertices;
    vertex* prev = nullptr;

    while(temp && temp->data != data)
    {
        prev = temp;
        temp = temp->vNext;
    }
    
    if(!temp)
    {
        cout << "Vertex not found - can't remove" << endl;
        return;
    }

    // remove that vertex from the adj list of all other vertices
    for(vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        edge* e = v->aHead;
        edge* prevEdge = nullptr;
        while(e)
        {
            if(e->dest->data == data)
            {
                if(prevEdge)
                    prevEdge->eNext = e->eNext;
                else
                    v->aHead = e->eNext;
                delete e;
                break;
            }
            prevEdge = e;
            e = e->eNext;
        }
    }

    // remove the vertex
    if(prev)
        prev->vNext = temp->vNext;
    else
        vertices = temp->vNext;

    delete temp;

    // Adj matrix
    int index = temp->data - 'A';
    for(int i = 0; i < maxVertices; i++)
    {
        adjMatrix[i][index] = 0;
        adjMatrix[index][i] = 0;
    }

    numVertices--;
}

void Graph::displayAdjList()
{
    for(vertex* v = vertices; v != nullptr; v = v->vNext)
    {
        cout << v->data << " -> ";
        for(edge* e = v->aHead; e != nullptr; e = e->eNext)
        {
            cout << e->dest->data << " (" << e->weight << ") -> ";
        }
        cout << "null" << endl;
    }
    cout << endl;
}

void Graph::displayAdjMatrix()
{
    cout << "     ";
    for(int i = 0; i < maxVertices; i++)
    {
        cout << setw(3) << char('A' + i) << " "; // column headers
    }
    cout << endl;
    cout << "   ";
    
    for(int i = 0; i < maxVertices; i++)
    {
        cout << "-----";
    }
    cout << endl;

    for(int i = 0; i < maxVertices; i++)
    {
        cout << setw(3) << char('A' + i) << " |"; // row header
        for(int j = 0; j < maxVertices; j++)
        {
            cout << setw(3) << adjMatrix[i][j] << " ";
        }
        cout << endl;
    }
}

void Graph::bfsL(char start) {
    bool* visited = new bool[maxVertices]();
    node* queue = nullptr;
    int index = start - 'A';
    enqueue(queue, index);
    visited[index] = true;

    cout << "BFS (Adjacency List) starting from " << start << ": ";

    while (queue) {
        int currentIndex = queue->data;
        dequeue(queue);
        cout << char(currentIndex + 'A') << " ";

        vertex* currentVertex = vertices;
        while (currentVertex && currentVertex->data != char(currentIndex + 'A'))
            currentVertex = currentVertex->vNext;

        if (currentVertex) {
            edge* e = currentVertex->aHead;
            while (e) {
                int neighborIndex = e->dest->data - 'A';
                if (!visited[neighborIndex]) {
                    enqueue(queue, neighborIndex);
                    visited[neighborIndex] = true;
                }
                e = e->eNext;
            }
        }
    }
    cout << endl;
    delete[] visited;
}

void Graph::removeEdge(char src, char dest) {
    // Remove from adjacency list
    vertex* srcVertex = vertices;
    while (srcVertex && srcVertex->data != src)
        srcVertex = srcVertex->vNext;
    
    if (!srcVertex) return;

    edge* prev = nullptr;
    edge* curr = srcVertex->aHead;
    while (curr) {
        if (curr->dest->data == dest) {
            if (prev)
                prev->eNext = curr->eNext;
            else
                srcVertex->aHead = curr->eNext;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->eNext;
    }

    // Since undirected, also remove from the other direction
    vertex* destVertex = vertices;
    while (destVertex && destVertex->data != dest)
        destVertex = destVertex->vNext;

    if (!destVertex) return;

    prev = nullptr;
    curr = destVertex->aHead;
    while (curr) {
        if (curr->dest->data == src) {
            if (prev)
                prev->eNext = curr->eNext;
            else
                destVertex->aHead = curr->eNext;
            delete curr;
            break;
        }
        prev = curr;
        curr = curr->eNext;
    }

    // Remove from adjacency matrix
    int i = src - 'A';
    int j = dest - 'A';
    if (i < maxVertices && j < maxVertices) {
        adjMatrix[i][j] = 0;
        adjMatrix[j][i] = 0;
    }
}


void Graph::bfsM(char start) {
    int startIndex = start - 'A';
    if (startIndex >= maxVertices) return;

    bool* visited = new bool[maxVertices]();
    queue<int> q;
    q.push(startIndex);
    visited[startIndex] = true;

    cout << "BFS (Adjacency Matrix) starting from " << start << ": ";

    while (!q.empty()) {
        int current = q.front();
        q.pop();
        cout << char(current + 'A') << " ";

        for (int i = 0; i < maxVertices; i++) {
            if (adjMatrix[current][i] != 0 && !visited[i]) {
                q.push(i);
                visited[i] = true;
            }
        }
    }
    cout << endl;
    delete[] visited;
}


void dfsListHelper(vertex* v) {
    if (!v || v->visited) return;
    v->visited = 1;
    cout << v->data << " ";
    
    edge* e = v->aHead;
    while (e) {
        if (!e->dest->visited)
            dfsListHelper(e->dest);
        e = e->eNext;
    }
}

void Graph::dfsL(char start) {
    vertex* v = vertices;
    while (v) {
        v->visited = 0; // reset visited flags
        v = v->vNext;
    }

    v = vertices;
    while (v && v->data != start)
        v = v->vNext;

    cout << "DFS (Adjacency List) starting from " << start << ": ";
    dfsListHelper(v);
    cout << endl;
}


void dfsMatrixHelper(int index, bool* visited, int maxVertices, int** matrix) {
    visited[index] = true;
    cout << char(index + 'A') << " ";

    for (int i = 0; i < maxVertices; i++) {
        if (matrix[index][i] != 0 && !visited[i]) {
            dfsMatrixHelper(i, visited, maxVertices, matrix);
        }
    }
}

void Graph::dfsM(char start) {
    int startIndex = start - 'A';
    if (startIndex >= maxVertices) return;

    bool* visited = new bool[maxVertices]();
    cout << "DFS (Adjacency Matrix) starting from " << start << ": ";
    dfsMatrixHelper(startIndex, visited, maxVertices, adjMatrix);
    cout << endl;
    delete[] visited;
}


bool Graph::detectCycleUtil(vertex* v, vertex* parent) {
    v->visited = 1;
    edge* e = v->aHead;
    while (e) {
        if (!e->dest->visited) {
            if (detectCycleUtil(e->dest, v))
                return true;
        } else if (e->dest != parent) {
            return true;
        }
        e = e->eNext;
    }
    return false;
}

bool Graph::detectCycle() {
    vertex* v = vertices;
    while (v) {
        v->visited = 0;
        v = v->vNext;
    }

    v = vertices;
    while (v) {
        if (!v->visited) {
            if (detectCycleUtil(v, nullptr))
                return true;
        }
        v = v->vNext;
    }
    return false;
}

void Graph::dfsComponent(vertex* v) {
    v->visited = 1;
    cout << v->data << " ";
    edge* e = v->aHead;
    while (e) {
        if (!e->dest->visited)
            dfsComponent(e->dest);
        e = e->eNext;
    }
}

void Graph::connectedComponents() {
    vertex* v = vertices;
    while (v) {
        v->visited = 0;
        v = v->vNext;
    }

    v = vertices;
    cout << "Connected Components:" << endl;
    while (v) {
        if (!v->visited) {
            dfsComponent(v);
            cout << endl;
        }
        v = v->vNext;
    }
}