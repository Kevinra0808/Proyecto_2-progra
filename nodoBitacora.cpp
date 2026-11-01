#include "nodoBitacora.h"
#include <string>
using namespace std;

NodoBitacora::NodoBitacora(Bitacora* dato) {
	this->dato = dato;
	this->siguiente = nullptr;
}

//Gets
Bitacora* NodoBitacora::getDato() const {
	return dato;
}

NodoBitacora* NodoBitacora::getSiguiente() const {
	return siguiente;
}

//Sets
void NodoBitacora::setSiguiente(NodoBitacora* nuevoSiguiente) {
	this->siguiente = nuevoSiguiente;
}