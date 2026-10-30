#include "nodoCliente.h"

NodoCliente::NodoCliente(Cliente* cliente) {
	this->cliente = cliente;
	this->siguiente = nullptr;
}

Cliente* NodoCliente::getCliente() {
	return cliente;
}

NodoCliente* NodoCliente::getSiguiente() {
	return siguiente;
}

void NodoCliente::setCliente(Cliente* cliente) {
	this->cliente = cliente;
}

void NodoCliente::setSiguiente(NodoCliente* siguiente) {
	this->siguiente = siguiente;
}
