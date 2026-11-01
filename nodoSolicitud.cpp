#include "nodoSolicitud.h"
#include <string>

NodoSolicitud::NodoSolicitud(SolicitudEnvio* dato) {
	this->dato = dato;
	this->siguiente = nullptr;
}

//Gets
SolicitudEnvio* NodoSolicitud::getDato() const {
	return dato;
}

NodoSolicitud* NodoSolicitud::getSiguiente() const {
	return siguiente;
}

//Sets
void NodoSolicitud::setSiguiente(NodoSolicitud* nuevoSiguiente) {
	this->siguiente = nuevoSiguiente;
}