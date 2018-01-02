#include <iostream>
#include <list>
#include <string.h>



using namespace std;

#define SIN_PAREJA -1

void leerGrafo (list<int> G[], int hombres, int mujeres) {
	int relaciones;
	cin >> relaciones;
	
	int hombre, mujer;
	for ( int i = 0 ; i < relaciones ; i++ ) {
		cin >> hombre >> mujer;
		G[hombre-1].push_front(mujer-hombres-1);
	}
}

// busca una configuracion alternativa del flujo para el nodo pasado por parametro
bool buscarAlt(int hombre, list<int> G[], int hombresEmparejados[], int mujeresEmparejadas[], bool visitados[]) {
	if (hombre == SIN_PAREJA) return true;
	if (visitados[hombre]) return false;
	visitados[hombre] = true;
	
	bool alt = false;
	list<int>::iterator it = G[hombre].begin();
	while (it != G[hombre].end() && !alt) {
		alt = buscarAlt(mujeresEmparejadas[*it] ,G , hombresEmparejados, mujeresEmparejadas, visitados);
		if (alt) {
			mujeresEmparejadas[*it] = hombre;
			hombresEmparejados[hombre] = *it;
			return true;
		}
		it++;
	}
	return false;

}


// buscar el maximo flujo del grafo
int maxFlujo(list<int> G[], int hombres, int mujeres) {
	int hombresEmparejados[hombres];
	int mujeresEmparejadas[mujeres];
	bool visitados[hombres];
	memset(hombresEmparejados, SIN_PAREJA, sizeof(hombresEmparejados));
	memset(mujeresEmparejadas, SIN_PAREJA, sizeof(mujeresEmparejadas));
	
	int flujo = 0;
	
	for ( int i = 0 ; i < hombres ; i++ ) {
		list<int>::iterator it = G[i].begin();
		while (it != G[i].end() && hombresEmparejados[i] == SIN_PAREJA) {
			if (mujeresEmparejadas[*it] == SIN_PAREJA) {
				flujo++;
				mujeresEmparejadas[*it] = i;
				hombresEmparejados[i] = *it;
			}
			it++;
		}
		
		
		if (hombresEmparejados[i] == SIN_PAREJA) {
			memset(visitados, false, sizeof(visitados));
			visitados[i] = true;
			bool alt = false;
			list<int>::iterator itAlt = G[i].begin();
			while (itAlt != G[i].end() && !alt) {
				alt = buscarAlt(mujeresEmparejadas[*itAlt], G, hombresEmparejados, mujeresEmparejadas, visitados);
				if (alt) {
					mujeresEmparejadas[*itAlt] = i;
					hombresEmparejados[i] = *itAlt;
				}
				itAlt++;
			}
			if (alt) flujo++;
		}
		
	}
	return flujo;
	
}


int main () {
	
	list<int>* G;
	
	int hombres = 0;
	int mujeres = 0;
	
	int casos;
	cin >> casos;
	for ( int i = 0 ; i < casos ; i++ ) {
		cin >> hombres;
		cin >> mujeres;
		
		G = new list<int>[hombres];
		
		leerGrafo(G, hombres, mujeres);
		cout << maxFlujo(G, hombres, mujeres) << endl;
		delete[] G;
	}
	
	return 0;
}


