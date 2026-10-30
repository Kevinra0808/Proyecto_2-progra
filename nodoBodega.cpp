#include "nodoBodega.h"
using namespace std;

NodoBodega::NodoBodega(Bodega* dato) {
	this->dato = dato;
	this->siguiente = nullptr;
}

//Gets
Bodega* NodoBodega::getDato() const {
	return dato;
}

NodoBodega* NodoBodega::getSiguiente() const {
	return siguiente;
}

//Sets
void NodoBodega::setSiguiente(NodoBodega* nuevoSiguiente) {
	this->siguiente = nuevoSiguiente;
}