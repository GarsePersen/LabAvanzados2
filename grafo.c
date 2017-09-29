#include <string.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include "grafo.h"

/* Función que crea un grafo
 * Entrada: Vacío
 * Salida: Estructura Grafo 
 *  */
struct Grafo *crearGrafo(){
    struct Grafo *g = malloc(sizeof(struct Grafo));
    g->nodos = NULL;
    g->cantNodos = 0; 
    return g;
}


/* Función que agrega un nodo al grafo
 * Entrada: Estructura Grafo, char nombreNodo
 * Salida: Void
 * */

void agregarNodo(struct Grafo *g, const char nombreNodo){
    struct Nodo *prev = g->nodos;
    //Si es el primer nodo que se agrega
    if(prev == NULL){
        g->nodos = malloc(sizeof(struct Nodo));
        g->nodos->nombre = nombreNodo;
        g->nodos->siguiente = NULL;
        g->nodos->vertices = NULL;
	g->nodos->visitado = NULL;
        g->cantNodos = 1;
        return;
    }
    //Si ya hay un nodo en en grafo
    size_t contador = 0;
    struct Nodo *ptr = prev;
    //Se llega al último nodo
    while(ptr){
        contador++;
        prev = ptr;
        ptr = ptr->siguiente;
    }
    // agregamos a prev
    struct Nodo *nuevo = malloc(sizeof(struct Nodo));
    nuevo->nombre = nombreNodo;
    nuevo->siguiente = NULL;
    nuevo->vertices = NULL;
    nuevo->visitado = NULL;
    prev->siguiente = nuevo;
}

/* Función que busca un nodo en el grafo
 * Entrada: Estructura Grafo, char nombre
 * Salida: Estructura Nodo
 * */
struct Nodo *buscarNodo(struct Grafo *g, const char nombre){
    for(struct Nodo *ptr = g->nodos; ptr != NULL; ptr = ptr->siguiente){
        if(ptr->nombre == nombre){
            return ptr;    
        }
    }
    return NULL;
}

/* Función que agrega un vertice al grafo entre dos nodos
 * Entrada: Estructura Grafo, char nombreNodo1, char nombreNodo2
 * Salida: Booleano
 * */
bool agregarVertice(struct Grafo *g, const char nombreNodo1, const char nombreNodo2){
    //Se buscan si los nodos existen en el grafo
    struct Nodo *nodo1 = buscarNodo(g, nombreNodo1);	
    struct Nodo *nodo2 = buscarNodo(g, nombreNodo2);	
    if(!(nodo1 &&  nodo2)){
        return false;
    }else{
	//Se verifica si es el primer vertice del nodo1
        if(nodo1->vertices == NULL){
            nodo1->vertices = malloc(sizeof(struct Vertice));
            nodo1->vertices->nodo  = nodo2;
            nodo1->vertices->siguiente = NULL;
            return true;
        }
        struct Vertice *ptr = nodo1->vertices;
        while(ptr->siguiente){
            ptr = ptr->siguiente;
        }
        struct Vertice *nuevo = malloc(sizeof(struct Vertice));
        nuevo->nodo = nodo2;
        nuevo->siguiente = NULL;
        ptr->siguiente  = nuevo;
        return true;
    }
}

/* Función que recorre los vertices del grafo y los imprime
 * Entrada: Estructura Nodo
 * Salida: Void
 * */
void recorrerVertices(struct Nodo *nodo){
    for(struct Vertice *ver = nodo->vertices; ver != NULL; ver = ver->siguiente){
        if(!ver->nodo->visitado){
            printf("----%c", ver->nodo->nombre);
            ver->nodo->visitado = true;
            recorrerVertices(ver->nodo); 
        }
    }

}

/* Función que imprime el grafo
 * Entrada: Estructura Grafo
 * Salida: Void
 * */
void imprimirGrafo(struct Grafo *g){
    for(struct Nodo *ptr = g->nodos; ptr != NULL; ptr = ptr->siguiente){
        printf("\n");
        printf("%c", ptr->nombre);
        for(struct Nodo *ptrAux = g->nodos; ptrAux != NULL; ptrAux = ptrAux->siguiente){
            ptrAux->visitado = false;

        }

        ptr->visitado = true;
        recorrerVertices(ptr);    
    }

}
