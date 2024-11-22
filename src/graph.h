#ifndef GRAPH_H
#define GRAPH_H

typedef struct Node {
    int id;
    struct Node* next; // Apunta al siguiente nodo
} Node;

typedef struct Graph {
    int numUsers;
    Node** adjacencyList;
} Graph;

Graph* initializeGraph(int numUsers);
void addConnection(Graph* graph, int user1, int user2);
void displayGraph(Graph* graph);
void freeGraph(Graph* graph);

#endif

