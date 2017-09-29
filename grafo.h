#include <stdint.h>
#include <stdbool.h>
//Estructura que almacena los nodos del vértice
struct Vertice{
    struct Nodo *nodo;
    struct Vertice *siguiente;  
};
//Estructura que almacena el nombre del nodo, un booleano si esta vistiado, puntero a la estructura Nodo, puntero a la estructura Vertices 
struct Nodo{
    char nombre;
    bool visitado;
    struct Nodo *siguiente;
    struct Vertice *vertices;
};
//Estructura que almacena la cantidad de nodos del grafo y un puntero a la estructura Nodo
struct Grafo{
    size_t cantNodos;
    struct Nodo *nodos;
};

struct Nodo *buscarNodo(struct Grafo *g, const char nombreNodo);

struct Grafo *crearGrafo();

void agregarNodo(struct Grafo *g, const char nombreNodo);

bool agregarVertice(struct Grafo *g, const char nombreNodo1, const char nombreNodo2);

void imprimirGrafo(struct Grafo *g);
