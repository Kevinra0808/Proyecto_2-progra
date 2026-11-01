#include "nodoPaquete.h"
#include <string>
using namespace std;

NodoPaquete::NodoPaquete(Paquete* dato) {
	this->dato = dato;
	this->siguiente = nullptr;
}

//Gets
Paquete* NodoPaquete::getDato() const {
	return dato;
}

NodoPaquete* NodoPaquete::getSiguiente() const {
	return siguiente;
}

//Sets
void NodoPaquete::setSiguiente(NodoPaquete* nuevoSiguiente) {
	this->siguiente = nuevoSiguiente;
}
