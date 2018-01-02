#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <list>

using namespace std;

#define INFINITO 2147483647
#define SIN_CAMINO -1
#define NO_NODO -2
#define COSTE_DESCONODIDO -3

typedef struct {
	int nodo;
	int coste;
} arista;

void inicializar (list<arista> G[], int ancho, int alto) {
	arista destino;
	destino.coste = COSTE_DESCONODIDO;
	for ( int H = 0 ; H < alto ; H++ ) {
		for ( int W = 0 ; W < ancho ; W++ ) {
			if ( H != 0 ) {
				destino.nodo = ancho*(H-1)+W;
				G[ancho*H+W].push_back(destino);
			}
			if ( W != 0 ) {
				destino.nodo = ancho*H+W-1;
				G[ancho*H+W].push_back(destino);
			}
			if ( W != ancho-1 ) {
				destino.nodo = ancho*H+W+1;
				G[ancho*H+W].push_back(destino);
			}
			if ( H != alto-1 ) {
				destino.nodo = ancho*(H+1)+W;
				G[ancho*H+W].push_back(destino);
			}
		}
	}
}

void borrarUno(list<arista> &lista, int borrar) {
	list<arista>::iterator it = lista.begin();
	while (it != lista.end() && (*it).nodo != borrar) it++;
	if (it != lista.end()) lista.erase(it);
}

void leerGrafo(list<arista> G[], int nnodos, int ancho, int alto) {
	// poner un laberinto sin muros ni maquinas
	inicializar(G, ancho, alto);

	int nmuros;
	int nmaquinas;
	
	// poner muros
	cin >> nmuros;
	int x, y;
	for ( int i = 0 ; i < nmuros ; i++ ) {
		cin >> x >> y;
		G[ancho*y+x].clear();
		if (y != 0) borrarUno(G[ancho*(y-1)+x] ,ancho*y+x);
		if (x != 0) borrarUno(G[ancho*y+x-1] ,ancho*y+x);
		if (x != ancho-1) borrarUno(G[ancho*y+x+1] ,ancho*y+x);
		if (y != alto-1) borrarUno(G[ancho*(y+1)+x] ,ancho*y+x);
	}
	
	// poner maquinas
	cin >> nmaquinas;
	int xdestino, ydestino, coste;
	arista destino;
	for ( int i = 0 ; i < nmaquinas ; i++ ) {
		cin >> x >> y >> xdestino >> ydestino >> coste;
		G[ancho*y+x].clear();
		destino.nodo = ancho*ydestino+xdestino;
		destino.coste = coste;
		G[ancho*y+x].push_back(destino);
	}
	
	// poner todos los costes que se desconocen a su valor
	cin >> coste;
	for ( int i = 0 ; i < nnodos ; i++ ) {
		for ( list<arista>::iterator it = G[i].begin(); it != G[i].end() ; it++ ) {
			if ((*it).coste == COSTE_DESCONODIDO) (*it).coste = coste;
		}
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

int buscarSalida (list<arista> G[], int nnodos, int inicio, int destino) {
	int costes[nnodos];
	int camino[nnodos];
	dijkstra (inicio, destino, G, nnodos, costes, camino);
	return costes[destino];
	
}

int main () {
	
	list<arista>* G;
	int nnodos;

	int alto;
	int ancho;
	int costeTotal;
	
	int casos;
	cin >> casos;
	for ( int i = 0 ; i < casos ; i++ ) {
		
		cin >> ancho >> alto;
		nnodos = ancho*alto;
		G = new list<arista>[nnodos];
		leerGrafo(G, nnodos, ancho, alto);
		costeTotal = buscarSalida(G, nnodos, 0, nnodos-1);
		if (costeTotal == INFINITO) cout << "LOST" << endl;
		else cout << costeTotal << endl;
		delete[] G;
	}
	return 0;
}






