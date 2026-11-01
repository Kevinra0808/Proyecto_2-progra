#include "nodoCentroDistribucion.h"

using namespace std;

NodoCentroDistribucion::NodoCentroDistribucion(CentroDistribucion* dato) {
	this->dato = dato;
	this->siguiente = nullptr;
}

CentroDistribucion* NodoCentroDistribucion::getDato() const {
	return dato;
}
NodoCentroDistribucion* NodoCentroDistribucion::getSiguiente() const {
	return siguiente;
}

void NodoCentroDistribucion::setSiguiente(NodoCentroDistribucion* nuevoSiguiente) {
	this->siguiente = nuevoSiguiente;
}