//Estructura NodoLista, almacena dos nodos, el grado y un puntero al siguiente
struct NodoLista{
	char nombreOrigen;
	char nombreDestino;
	unsigned int grado;
	struct NodoLista *siguiente;
};
//Estructura Lista, almacena la estructura NodoLista
struct Lista{
	struct NodoLista *nodos;
};

int encontrarElementoConDosNodos(struct Lista *l, char nodo, char nodo2);

int encontrarElemento(struct Lista *l, char nodo);

void ordenarSoluciones(struct Lista *l, struct Lista *l2);

void acotarSolucionesMinimo(struct Lista *l2, struct Lista *l, struct Lista *lFinal);

int obtenerGradoMinimo(struct Lista *l, char nodo1, char nodo2);

void acotarSolucionesGrado(struct Lista *l2, struct Lista *l, int grado);

void imprimirLista(struct Lista *l);

void agregarElemento(struct Lista *l, const char nombreNodo, const char nombreNodoDestino, int grado);

struct Lista *crearLista();
