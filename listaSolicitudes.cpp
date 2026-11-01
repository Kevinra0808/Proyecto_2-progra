#include "listaSolicitudes.h"
#include <string>

using namespace std;

ListaSolicitudes::ListaSolicitudes() {
	primero = nullptr;
	actual = nullptr;
}

ListaSolicitudes::~ListaSolicitudes() {
	while (primero != nullptr)
	{
		NodoSolicitud* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar;
	}
}

void ListaSolicitudes::insertarSolicitud(SolicitudEnvio* nuevoSolicitud) {
	NodoSolicitud* nuevo = new NodoSolicitud(nuevoSolicitud);
	if (primero == nullptr)
	{
		primero = nuevo;
	}
	else
	{
		NodoSolicitud* aux = primero;
		while (aux->getSiguiente() != nullptr)
		{
			aux = aux->getSiguiente();
		}
		aux->setSiguiente(nuevo);
	}
}

void ListaSolicitudes::mostrarSolicitudes() const {
	NodoSolicitud* aux = primero;

	while (aux != nullptr)
	{
		aux->getDato()->mostrarSolicitud();
		cout << endl;

		aux = aux->getSiguiente();
	}
}

NodoSolicitud* ListaSolicitudes::buscar(string codigo) const {
	NodoSolicitud* aux = primero;

	while (aux != nullptr)
	{
		if (aux->getDato()->getCodigo() == codigo)
		{
			return aux;
		}
		else
		{
			aux = aux->getSiguiente();
		}
	}
	return nullptr;
}

bool ListaSolicitudes::cambiarEstado(string codigo, string nuevoEstado) {
	NodoSolicitud* nodoEncontrado = buscar(codigo);
	if (nodoEncontrado != nullptr) {
		nodoEncontrado->getDato()->setEstado(nuevoEstado);
		return true;
	}
	return false;
}

bool ListaSolicitudes::estaVacio() const {
	return primero == nullptr;
}