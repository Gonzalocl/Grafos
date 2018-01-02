#include <iostream>
#include <list>
#include <string.h>



using namespace std;

#define MAX_FILAS 150
#define MAX_COLUMNAS 150

#define MAX_GARBANCILLOS 12*150
#define MAX_ASTRAGALUS 15*150

#define VACIO -1

void registrarGar(int garbancillos[][MAX_COLUMNAS], int fila, int columna, int numero) {
	for ( int i = 0 ; i < 12 ; i++ ) {
		garbancillos[fila][columna+i] = numero;
	}
}
void registrarAst(int astragalus[][MAX_COLUMNAS], int fila, int columna, int numero) {
	for ( int i = 0 ; i < 10 ; i++ ) {
		astragalus[fila+i][columna] = numero;
	}
}

void buscarGarAst (int garbancillos[][MAX_COLUMNAS], int astragaluses[][MAX_COLUMNAS], int filas, int columnas, int &ngar, int &nast) {
	char mapa[filas][columnas];
	char punto;
	// rellenar mapa y buscar garbancillos
	int contador = 0;
	string garbancillo = "GARBANCILLOS";
	string::iterator itGar = garbancillo.begin();
	for ( int f = 0 ; f < filas ; f++ ) {
		for ( int c = 0 ; c < columnas ; c++ ) {
			// rellenar mapa
			cin >> punto;
			mapa[f][c] = punto;
			
			// buscar garbancillos
			if (punto == *itGar) {
				itGar++;
			} else if (punto == 'G') {
				itGar = garbancillo.begin();
				itGar++;
			} else {
				itGar = garbancillo.begin();
			}
			
			if (itGar == garbancillo.end()) {
				registrarGar(garbancillos, f, c-11, contador);
				itGar = garbancillo.begin();
				contador++;
			}
		}
	}
	ngar = contador;
	
	// buscar astragalus
	contador = 0;
	for ( int c = 0 ; c < columnas ; c++ ) {
		for ( int f = 0 ; f < filas-9 ; f++ ) {
			
			if (mapa[f][c] == 'A') {
				if (mapa[f+1][c] == 'S' && mapa[f+2][c] == 'T' &&
					mapa[f+3][c] == 'R' && mapa[f+4][c] == 'A' &&
					mapa[f+5][c] == 'G' && mapa[f+6][c] == 'A' &&
					mapa[f+7][c] == 'L' && mapa[f+8][c] == 'U' &&
					mapa[f+9][c] == 'S') {
						registrarAst(astragaluses, f, c, contador);
						contador++;
				}
			}
		}
	}
	nast = contador;
}

void leerGrafo (list<int> G[], int &ngar, int &nast) {
	int filas, columnas;
	cin >> filas >> columnas;
	int garbancillos[MAX_FILAS][MAX_COLUMNAS];
	int astragalus[MAX_FILAS][MAX_COLUMNAS];
	memset(garbancillos, VACIO, sizeof(garbancillos));
	memset(astragalus, VACIO, sizeof(astragalus));
	
	buscarGarAst(garbancillos, astragalus, filas, columnas, ngar, nast);
	for ( int f = 0 ; f < filas ; f++ ) {
		for ( int c = 0 ; c < columnas ; c++ ) {
			if ( garbancillos[f][c] != VACIO && astragalus[f][c] != VACIO ) {
				G[garbancillos[f][c]].push_front(astragalus[f][c]);
			}
		}
	}
	
}

bool buscarAlt(int gar, list<int> G[], int garUsados[], int astUsados[], bool visitados[]) {
	if (gar == VACIO) return true;
	if (visitados[gar]) return false;
	visitados[gar] = true;
	
	bool alt = false;
	list<int>::iterator it = G[gar].begin();
	while (it != G[gar].end() && !alt) {
		alt = buscarAlt(astUsados[*it] ,G, garUsados, astUsados, visitados);
		if (alt) {
			astUsados[*it] = gar;
			garUsados[gar] = *it;
			return true;
		}
		it++;
	}
	return false;

}

int maxFlujo(list<int> G[], int &ngar, int &nast) {
	int garUsados[ngar];
	int astUsados[nast];
	bool visitados[ngar];
	memset(garUsados, VACIO, sizeof(garUsados));
	memset(astUsados, VACIO, sizeof(astUsados));
	
	int flujo = 0;
	
	for ( int i = 0 ; i < ngar ; i++ ) {
		list<int>::iterator it = G[i].begin();
		while (it != G[i].end() && garUsados[i] == VACIO) {
			if (astUsados[*it] == VACIO) {
				flujo++;
				astUsados[*it] = i;
				garUsados[i] = *it;
			}
			it++;
		}
		
		
		if (garUsados[i] == VACIO) {
			memset(visitados, false, sizeof(visitados));
			visitados[i] = true;
			bool alt = false;
			list<int>::iterator itAlt = G[i].begin();
			while (itAlt != G[i].end() && !alt) {
				alt = buscarAlt(astUsados[*itAlt], G, garUsados, astUsados, visitados);
				if (alt) {
					astUsados[*itAlt] = i;
					garUsados[i] = *itAlt;
				}
				itAlt++;
			}
			if (alt) flujo++;
		}
	}
	
	return flujo;
	
}


int main () {
	
	list<int> gar[MAX_GARBANCILLOS];
	
	int ngar = 0;	// numero de garbancillos
	int nast = 0;	// numero de astragalus
	
	int casos;
	cin >> casos;
	for ( int i = 0 ; i < casos ; i++ ) {
		// vaciar el grafo
		for ( int i = 0 ; i < ngar ; i++ ) {
			gar[i].clear();
		}
		leerGrafo(gar, ngar, nast);
		cout << maxFlujo(gar, ngar, nast) << endl;
	}
	
	return 0;
}


