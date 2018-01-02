#include <list>
#include <iostream>
#include <string.h>

using namespace std;

#define MAX_NODOS 3500
#define NO_NODO -1
// bien
void leerGrafo(list<int> G[], int nnodos, int naristas) {
	int U, V;
	for (int i = 0 ; i < naristas ; i++) {
		cin >> U >> V;
		G[U].push_front(V);
		G[V].push_front(U);
/*		G[U].push_back(V);
		G[V].push_back(U);*/
	}
}

void bpp(list<int> G[], int v, bool visitado[]) {
	visitado[v]= true;
	for (list<int>::iterator it = G[v].begin() ; it != G[v].end() ; it++)
		if (!visitado[*it])
			bpp(G, *it, visitado);
}

bool verificar (list<int> G[], int nnodos) {
	// verificar grado par para todos
	
	for (int i = 0 ; i < nnodos ; i++) {
		if (G[i].size() % 2 != 0) return false;
	}
	/*
	// verificar conexo
	bool visitado[nnodos];
	memset(visitado, 0, sizeof(visitado));
	
	bpp(G, 0, visitado);
	
	for (int i = 0 ; i < nnodos ; i++) {
		//if (!visitado[i]) return false;
		if (!visitado[i] && !G[i].empty()) return false;
	}*/
	return true;
}

void borrarUno(list<int> &lista, int borrar) {
	list<int>::iterator it = lista.begin();
	while (*it != borrar) it++;
	// no se comprueba si lo ha en contrado porque siempre debe haber almenos uno
	lista.erase(it);
}


void encontrarCiclo(list<int> G[], int nnodos, list<int> &ciclo, int inicio) {
	ciclo.clear();
	
	ciclo.push_back(inicio);
	int ultimo = inicio;
	do {
		int aux = G[ultimo].front();
		G[ultimo].pop_front();
		borrarUno(G[aux], ultimo);
		ciclo.push_back(aux);
		ultimo  = aux;
	} while (ultimo != inicio);
	
	
	
	/*
	int primero = G[inicio].front();
	G[inicio].pop_front();
	// borrar del otro lado
	cilo.push_back(primero);


	int siguiente = primero;
	int aux;
	do {
	
		aux = G[siguiente].front();
		G[siguiente].pop_front();
		// borrar
		ciclo.push_back(aux);
		
		
		siguiente = aux;
	} while (siguiente != primero);
	*/
}

void rotarCiclo(list<int> &ciclo, int rotaciones) {
	ciclo.pop_front();
	for ( int i = 0 ; i < rotaciones ; i++ ) {
		ciclo.push_back(ciclo.front());
		ciclo.pop_front();
	}
	ciclo.push_front(ciclo.back());
}

bool contiene(list<int> l, int e) {
	list<int>::iterator it = l.begin();
	while (it != l.end() && e != *it) it++;
	return it != l.end();
}

void addCiclo(list<int> &circuito, list<int> &ciclo) {
	if (circuito.empty()) {
		circuito.splice(circuito.begin(), ciclo);
	} else {
		list<int>::iterator itciclo = ciclo.begin();
		list<int>::iterator itcircuito = circuito.begin();
		int i = 0;
		bool encontrado = false;
		//int foo;
		while (!encontrado) {
			//cout << "exterior---- " << encontrado << endl;
			//cin >> foo;
			itciclo = ciclo.begin();
			i = 0;
			while (itciclo != ciclo.end() && !encontrado) {
				encontrado = *itciclo == *itcircuito;
				//cout << "inrior----- " << encontrado << "/" << *itciclo << "/" << *itcircuito <<  endl;
				//cin >> foo;
				itciclo++;
				i++;
			}
			itcircuito++;
		}
		rotarCiclo(ciclo, i-1);
		ciclo.pop_front();
		circuito.splice(itcircuito, ciclo);
	}
}

void circuitoEuler (list<int> G[], int nnodos, list<int> &circuito) {
	list<int> ciclo;
	circuito.clear();
	for ( int i = 0 ; i < nnodos ; i++ ) {
		while (!G[i].empty()) {
			encontrarCiclo(G, nnodos, ciclo, i);
			addCiclo(circuito, ciclo);
		}
	}
}




// bien
void show(list<int> G[], int nnodos) {
	cout << "mostrando------------------------/" << endl;
	for ( int i = 0 ; i < nnodos ; i++ ) {
		for ( list<int>::iterator it = G[i].begin(); it != G[i].end() ; it++ ) {
			cout << (*it) << "\t";
		}
		cout << endl;
	}
	cout << "mostrando------------------------/" << endl;
}

void showL(list<int> &l) {
	cout << "lista----------------------------/" << endl;
	for ( list<int>::iterator it = l.begin(); it != l.end() ; it++ ) {
			cout << (*it) << "\t";
	}
	cout << endl << "lista----------------------------/" << endl;
}


void mostrarlista(list<int> &l) {
	list<int>::iterator it = l.begin();
	cout << *it;
	it++;
	for ( ; it != l.end() ; it++ ) {
			cout << " " << *it;
	}
	cout << endl;
}



int main () {
	
	list<int> G[MAX_NODOS];
	int nnodos;
	int naristas;
	
	list<int> circuito;
	
	int casos;
	cin >> casos;
	for (int i = 0 ; i < casos ; i++) {
		cin >> nnodos >> naristas;
		leerGrafo(G, nnodos, naristas);
		if (verificar(G, nnodos)) {
			//show(G, nnodos);
			cout << "YES" << endl;
			circuitoEuler(G, nnodos, circuito);
			mostrarlista(circuito);
		} else {
			cout << "NO" << endl;
			cout << 0 << endl;
		}
		//show(G, nnodos);
		for ( int i = 0 ; i < nnodos ; i++ ) {
			G[i].clear();
		}
	}
	
	return 0;
}
