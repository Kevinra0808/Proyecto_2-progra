#include "nodoDespacho.h"
#include <string>

using namespace std;

NodoDespacho::NodoDespacho(Despacho* dato) {
	this->dato = dato;
	this->siguiente = nullptr;
}

Despacho* NodoDespacho::getDato() const {
	return dato;
}

NodoDespacho* NodoDespacho::getSiguiente() const {
	return siguiente;
}

void NodoDespacho::setSiguiente(NodoDespacho* nuevoSiguiente) {
	this->siguiente = nuevoSiguiente;
}