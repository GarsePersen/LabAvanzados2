#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "grafo.h"
#include "lista.h"
#include "lab_1.h"


int main(int argc, char const *argv[]){
	struct Grafo *g = crearGrafo();
	int r = leerArchivo(g);
	if(r == -1){
		free(g);
	}
	generarSoluciones(g, r);
	return 0;
}

/* Función que escribe en el archivo de salida
 * Entrada: Estructura lista
 * Salida: Un entero
 * */
int escribirArchivo(struct Lista *l){
	FILE *fp;
	fp = fopen("salida.out", "w");
	if(l->nodos == NULL){
		fprintf(fp, "No existen nodos que cumplan con el grado dado");   
	}
	for(struct NodoLista *aux = l->nodos; aux != NULL; aux = aux->siguiente){
		fprintf(fp, "%c %i\n", aux->nombreOrigen, aux->grado);
	}
	fclose(fp);
	return 0;

}

/* Funcion que llama a otras funciones que van generando las soluciones
 * Entrada: Estructura grafo, un entero
 * Salida: Void
 * */
void generarSoluciones(struct Grafo *g, int grado){ 
	struct Lista *solucion1 = crearLista();
	struct Lista *solucion2 = crearLista();
	struct Lista *solucion3 = crearLista();
	struct Lista *solucionFinal = crearLista();
	imprimirGrafo2(g, solucion1, grado);
	acotarSolucionesGrado(solucion2, solucion1, grado);
	acotarSolucionesMinimo(solucion2, solucion1, solucion3);
	ordenarSoluciones(solucion3, solucionFinal);
    imprimirLista(solucionFinal); 

	//Se libera memoria
	free(solucion1);
	free(solucion2);
	free(solucion3);
	//Se llama a funcion para escribir
	//escribirArchivo(solucionFinal);
}

/* Función que lee un archivo y almacena los datos en un grafo
 * Entrada: Estructura Grafo
 * Salida: Entero representando el grado a buscar
 * */
int leerArchivo(struct Grafo *g){
	FILE *fp;
	int c;
	int linea = 0;
	int grado = 0;
	int aux = 0;
	char nodo1;
	bool r;
	fp = fopen("entrada.in","r");
	if(fp == NULL) 
	{
		printf("Error, verifique que existe su archivo entrada.in");
		return(-1);
	}
	do
	{
		c = fgetc(fp);
		//Se verifica que no sea espacio
		if(feof(fp))
		{
			break;
		}
		if(c != 32){ 
			//Si es un salto de linea
			if(c == 10){
				linea ++;
				aux = 0; 
			}
			if(linea == 0)
			{
				grado = c-48;
			}else{
				if(c != 10){
					struct Nodo *nodo = buscarNodo(g, c);	
					if(nodo == NULL){
						agregarNodo(g, c);
					}
					//Si estamos en el primer nodo
					if(aux == 1){
						nodo1 = c;     
					}else{
						r = agregarVertice(g, nodo1, c); 
						if(r == false){
							printf("Ocurrio un error");
							return -1;
						}
					}
				}
			}
		}
		aux ++;
	}while(1);
	fclose(fp);
	return grado;


}

/* Función que recorre los vertices del grafo y los imprime
 * Entrada: Estructura Nodo
 * Salida: Void
 * */
void recorrerVertices2(struct Lista *l, char nodo1, int contador, struct Nodo *nodo, int grado){
    contador++;
    for(struct Vertice *ver = nodo->vertices; ver != NULL; ver = ver->siguiente){
        if(!ver->nodo->visitado){
            ver->nodo->visitado = true;
            char nodo2 = ver->nodo->nombre; 
            agregarElemento(l, nodo1, nodo2, contador);
        }
    }
    if(contador<grado){
        for(struct Vertice *ver = nodo->vertices; ver != NULL; ver = ver->siguiente){
            recorrerVertices2(l, nodo1, contador, ver->nodo, grado);
        }

    }

}

/* Función que imprime el grafo
 * Entrada: Estructura Grafo
 * Salida: Void
 * */
void imprimirGrafo2(struct Grafo *g, struct Lista *l, int grado){
    for(struct Nodo *ptr = g->nodos; ptr != NULL; ptr = ptr->siguiente){
        for(struct Nodo *ptrAux = g->nodos; ptrAux != NULL; ptrAux = ptrAux->siguiente){
            ptrAux->visitado = false;
        }
		//Se guarda el nombre del nodo de origen
		char nodo1 = ptr->nombre;
		//Se crea variable contador que representa el grado entre los nodos
		int contador = 0;
        ptr->visitado = true;
        recorrerVertices2(l, nodo1, contador, ptr, grado);    
    }

}
