#include <stdlib.h>
#include <stdio.h>
#include "lista.h"

/* Función que ordena una lista de soluciones de acuerdo a como se pide en el enunciado
 * Entrada: Estructura Lista, Estructura Lista
 * Salida: Void
 * */
void ordenarSoluciones(struct Lista *l, struct Lista *l2){
    //Se recorren los nodos de la lista
    for(struct NodoLista *aux = l->nodos; aux != NULL; aux = aux->siguiente){
        //Se crea un contador que representa la cantidad de nodos con los que el nodo cumple con el problema
	int contador = 1;
	//Se busca si hay mas veces que salga el nodo en el espacio de soluciones
        for(struct NodoLista *aux2 = aux->siguiente; aux2 != NULL; aux2 = aux2->siguiente){
            if(aux->nombreOrigen == aux2->nombreOrigen){
                contador++;
            }
        }
	//Se busca si ya existe el elemento, para no repetir
        int r = encontrarElemento(l2, aux->nombreOrigen);
        if(r == -1){
            agregarElemento(l2, aux->nombreOrigen, aux->nombreOrigen, contador);
        }
    }
}

/* Función que busca un elemento en la lista usando dos nodos
 * Entrada: Estructura Lista, char nodo, char nodo2
 * Salida: Entero
 * */
int encontrarElementoConDosNodos(struct Lista *l, char nodo, char nodo2){
    for(struct NodoLista *aux = l->nodos; aux != NULL; aux = aux->siguiente){
        if((nodo == aux->nombreOrigen)&&(nodo2 == aux->nombreDestino)){
            return 0;
        }
    }
    return -1;

}

/* Función que busca un elemento en la lista de acuerdo al primer nodo
 * Entrada: Estructura Lista, char nodo
 * Salida: Entero
 * */
int encontrarElemento(struct Lista *l, char nodo){
    for(struct NodoLista *aux = l->nodos; aux != NULL; aux = aux->siguiente){
        if(nodo == aux->nombreOrigen){
            return 0;
        }
    }
    return -1;
}

/* Función que encuentra el grado minimo entre dos nodos de acuerdo al espacio de soluciones
 * Entrada: Estructura Lista, char nodo1, char nodo2
 * Salida: Entero
 * */
int obtenerGradoMinimo(struct Lista *l, char nodo1, char nodo2){
    int min = -1;
    //Se recorren los nodos de la lista
    for(struct NodoLista *aux = l->nodos; aux != NULL; aux = aux->siguiente){
	//Se preguntan si los nodos existen en la lista 
        if((aux->nombreOrigen == nodo1)&&(aux->nombreDestino == nodo2)){
	    //Se obtiene el minimo
            if(min == -1){
                min = aux->grado;
            }
            if(min > aux->grado){
                min = aux->grado;
            }
        }
    }
    return min;
}

/* Función que acota las soluiones dependiendo si el grado encontrado es el mínimo. Se usa la lista original, 
 * la que contiene la segunda acotación y una lista en donde se agrega la solución final
 * Entrada: Estructura Lista, estructura Lista, estructura Lista
 * Salida: Void
 * */
void acotarSolucionesMinimo(struct Lista *l2, struct Lista *l, struct Lista *lFinal){
    //Se recorren los nodos de la lista
    for(struct NodoLista *aux = l2->nodos; aux != NULL; aux = aux->siguiente){
        int grado = obtenerGradoMinimo(l, aux->nombreOrigen, aux->nombreDestino);
        if(grado == aux->grado){
            agregarElemento(lFinal, aux->nombreOrigen, aux->nombreDestino, aux->grado);

        }
    }
}


/* Función que hace la primera acotación de la solución de acuerdo al grado pedido
 * Entrada: Estructura Lista, estructura Lista, entero
 * Salida: Void 
 * */
void acotarSolucionesGrado(struct Lista *l2, struct Lista *l, int grado){
    for(struct NodoLista *aux = l->nodos; aux != NULL; aux = aux->siguiente){
        int r = encontrarElementoConDosNodos(l2, aux->nombreOrigen, aux->nombreDestino); 
        if((aux->grado == grado)&&(r == -1)){
            agregarElemento(l2, aux->nombreOrigen, aux->nombreDestino, aux->grado);
        }
    }
}

/* Función que imprime la lista
 * Entrada: Estructura Lista
 * Salida: Void
 * */
void imprimirLista(struct Lista *l){
    for(struct NodoLista *aux = l->nodos; aux != NULL; aux = aux->siguiente){
		printf("%c-", aux->nombreOrigen);
        printf("%c grado ", aux->nombreDestino);
		printf("%i\n", aux->grado);
	}
}

/* Función que agrega un elementos a la lista
 * Entrada: Estructura Lista, char nombreNodo, char nombreNodoDestino, entero
 * Salida: Void
 * */
void agregarElemento(struct Lista *l, const char nombreNodo, const char nombreNodoDestino, int grado){
    struct NodoLista *prev = l->nodos;
    //Se verifica si ya existe un nodo en la lista
    if(prev == NULL){
        l->nodos = malloc(sizeof(struct NodoLista));
        l->nodos->nombreOrigen = nombreNodo;
        l->nodos->nombreDestino = nombreNodoDestino;
        l->nodos->siguiente = NULL;
        l->nodos->grado = grado;
        return;
    }
    struct NodoLista *ptr = prev;
    while(ptr){
        prev = ptr;
        ptr = ptr->siguiente;
    }
    struct NodoLista *nuevo = malloc(sizeof(struct NodoLista));
    nuevo->nombreOrigen = nombreNodo;
    nuevo->siguiente = NULL;
    nuevo->nombreDestino = nombreNodoDestino;
    nuevo->grado = grado;
    prev->siguiente = nuevo;
}

/*Función que crea una lista
 * Entrada: Vacío
 * Salida: Estructura Lista 
 * */
struct Lista *crearLista(){
	struct Lista *l = malloc(sizeof(struct Lista));
	l->nodos = NULL;
	return l;
}
