#include <string.h>  // Funcion memset
#include <iostream>  // Variables cin y cout
#include <queue>

using namespace std;

#define MAX_NODOS 26

//////////////////////////////////////////////////////////////
////////////        VARIABLES GLOBALES        ////////////////
//////////////////////////////////////////////////////////////

int nnodos;                   // Numero de nodos del grafo
int naristas;                 // Numero de aristas del grafo
bool G[MAX_NODOS][MAX_NODOS]; // Matriz de adyacencia
bool visitado[MAX_NODOS];     // Marcas de nodos visitados

//////////////////////////////////////////////////////////////
////////////     FUNCIONES DEL PROGRAMA       ////////////////
//////////////////////////////////////////////////////////////

void leeGrafo (void) {
	cin >> nnodos >> naristas;
	memset(G, 0, sizeof(G));
	char c1, c2;
	for (int i= 0; i<naristas; i++) {
		cin >> c1 >> c2;
		G[c1-'A'][c2-'A']= true;
	}
}

void bpa(int v) {
	queue<int> cola;
	int x;
	visitado[v]= true;
	cola.push(v);
	while ( !cola.empty() ) {
		x = cola.front();
		cout << char(x+'A');
		cola.pop();
		for ( int w = 0 ; w < nnodos ; w++ ) {
			if ( !visitado[w] && G[x][w]) {
				visitado[w]= true;
				cola.push(w);
			}
		}
	}
}

void busquedaPA (void) {
	memset(visitado, 0, sizeof(visitado));
	for (int v= 0; v<nnodos; v++)
		if (!visitado[v])
			bpa(v);
	cout << endl;
}

//////////////////////////////////////////////////////////////
////////////        PROGRAMA PRINCIPAL        ////////////////
//////////////////////////////////////////////////////////////

int main (void) {
	int ncasos;
	cin >> ncasos;
	for (int i= 0; i<ncasos; i++) {
		leeGrafo();
		busquedaPA();
	}
}
