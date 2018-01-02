#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <list>

using namespace std;

#define INFINITO 2147483647
#define SIN_CAMINO -1
#define NO_NODO -2

typedef struct {
	int nodo;
	int coste;
} arista;

/*
// bien
void insertar(list<arista> &lista, arista a) {
	list<arista>::iterator it = lista.begin();
	while (it != lista.end() && a.nodo > (*it).nodo) {
		it++;
	}
	if (it == lista.end() || a.nodo != (*it).nodo) {
		lista.insert(it, a);
	}
}
// bien
int consultar(list<arista> &lista, int nodo) {
	list<arista>::iterator it = lista.begin();
	while (it != lista.end() && nodo > (*it).nodo) {
		it++;
	}
	if (it != lista.end() && (*it).nodo == nodo) {
		return (*it).coste;
	}	
	return INFINITO;
}
*/

// bien
void leerGrafo(list<arista> G[], int nnodos, int naristas) {
	int U, V, coste;
	for ( int i = 0 ; i < naristas ; i++ ) {
		cin >> U >> V >> coste;
		arista aux;
		aux.coste = coste;
		aux.nodo = V-1;
		G[U-1].push_front(aux);
		aux.nodo = U-1;
		G[V-1].push_front(aux);
	}
}

// devuelve el nodo que tine el camino mas corto y no ha sido escogido aun
int nodoSinCaminoCorto (int nnodos, int costes[], bool escogidos[]) {
	int actual = NO_NODO;
	int menorCoste = INFINITO;
	for ( int i = 0 ; i < nnodos ; i++ ) {
		if (!escogidos[i] && costes[i] < menorCoste) {
			actual = i;
			menorCoste = costes[i];
		}
	}
	return actual;
}

// funcion principal del algoritmo
void dijkstra (int inicio, int destino, list<arista> G[], int nnodos, int costes[], int camino[]) {
	bool escogidos[nnodos];
	// inicilizacion de variables
	for ( int i = 0 ; i < nnodos ; i++) {
		costes[i] = INFINITO;
		camino[i] = SIN_CAMINO;
		escogidos[i] = false;
	}
	
	costes[inicio] = 0;
	int v;
	for ( int i = 0 ; i < nnodos ; i++ ) {
		v = nodoSinCaminoCorto(nnodos, costes, escogidos);
		// terminar si ya se han encontrado todos los caminos mas cortos de la componente conexa en la que esta el nodo inicial
		if (v == NO_NODO) return;
		// terminar si ya se ha encontrado el camino especial mas corto para el destino que se estaba buscando
		if (v == destino) return;
		escogidos[v] = true;
		for (list<arista>::iterator it = G[v].begin() ; it != G[v].end() ; it++ ) {
			if (!escogidos[(*it).nodo] && ((costes[v]+ (*it).coste)<costes[(*it).nodo])){
				costes[(*it).nodo] = costes[v] + (*it).coste;
				camino[(*it).nodo] = v;
			}
		}
	}
}

int caminoCorto (list<arista> G[], int nnodos, int inicio, int destino) {
	int costes[nnodos];
	int camino[nnodos];
	dijkstra (inicio, destino, G, nnodos, costes, camino);
	return costes[destino];
	
}

/*
// bien
void show(list<arista> G[], int nnodos) {
	cout << "mostrando------------------------/" << endl;
	for ( int i = 0 ; i < nnodos ; i++ ) {
		for ( list<arista>::iterator it = G[i].begin(); it != G[i].end() ; it++ ) {
			cout << (*it).nodo << "/" << (*it).coste << " - ";
		}
		cout << endl;
	}
	cout << "mostrando------------------------/" << endl;
}
//bien
void show2(list<arista> G[], int nnodos) {
	cout << "mostrando-------------2-----------/" << endl;
	for ( int i = 0 ; i < nnodos ; i++ ) {
		for ( int j = 0 ; j < nnodos ; j++ ) {
			cout << consultar(G[i], j) << " -\t";
		}
		cout << endl;
	}
	cout << "mostrando-------------2-----------/" << endl;
}
*/


int main () {
	

	list<arista>* G;
	int nnodos;
	int naristas;

	int inicio;
	int destino;
	int intermedio;
	
	int coste1;
	int coste2;

	int casos;
	cin >> casos;
	for ( int i = 0 ; i < casos ; i++ ) {
		
		cin >> nnodos;
		cin >> naristas;
		cin >> inicio >> destino >> intermedio;
		G = new list<arista>[nnodos];
		leerGrafo(G, nnodos, naristas);
		coste1 = caminoCorto(G, nnodos, inicio-1, intermedio-1);
		coste2 = caminoCorto(G, nnodos, intermedio-1, destino-1);
		if ( coste1 == INFINITO || coste2 == INFINITO ) {
			cout << "IMPOSIBLE" << endl;
		} else {
			cout << coste1+coste2 << endl;
		}
		delete[] G;
	}
	return 0;
}






