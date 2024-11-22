#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_USERS 50 // Cantidad maxima de usuarios

typedef struct User // Estructura de usuario standar
{
    int id;                   // Id de usuario
    char username[30];        // Nombre mediante el txt - idea : if de genero, si es masculino o femenino usar el txt correspondiente, otro = cualquiera
    char gender[12];          // Masculino , Femenino , Otro
    char hobbies[100];        // Puede ser en vez de char un int con la ID de cada hobbie ej : 1 - fuchibol ; idHobbie = 1;
    char staticMessagge[100]; // Idea báscia de mensaje - reconsiderar bastante

    // hobbies y mensajes podrian llevarse a 2 struct diferentes
} User;

typedef struct Node
{
    int id;
    struct Node *next;
} Node;

typedef struct Graph
{
    int numUsers;
    Node **adjacencyList;
} Graph;

Graph *initializeGraph(int numUsers);
void addConnection(Graph *graph, int user1, int user2);
void displayGraph(Graph *graph);
void freeGraph(Graph *graph);