#include "NodoColaborador.h"
#include <string>

using namespace std;

NodoColaborador::NodoColaborador(Colaborador* dato) {
	this->dato = dato;
	this->siguiente = nullptr;
}

//Gets
Colaborador* NodoColaborador::getDato() const{
	return dato;
}

NodoColaborador* NodoColaborador::getSiguiente() const{
	return siguiente;
}

//Sets
void NodoColaborador::setSiguiente(NodoColaborador* nuevoSiguiente) {
	this->siguiente = nuevoSiguiente;
}
