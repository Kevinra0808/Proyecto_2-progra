#include "listaSolicitudes.h"
#include <string>

using namespace std;

ListaSolicitudes::ListaSolicitudes() {
	primero = nullptr;
	actual = nullptr;
	cantidad = 0;
}

ListaSolicitudes::~ListaSolicitudes() {
	while (primero != nullptr)
	{
		NodoSolicitud* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar->getDato();
		delete borrar;
	}
}

void ListaSolicitudes::insertarSolicitud(SolicitudEnvio* nuevaSolicitud) {
	NodoSolicitud* nuevo = new NodoSolicitud(nuevaSolicitud);
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
	cantidad++;
}

void ListaSolicitudes::mostrarSolicitudes() const {
	NodoSolicitud* aux = primero;

	if (aux == nullptr)
	{
		cout << "No hay solicitudes registradas." << endl;
	}

	while (aux != nullptr)
	{
		aux->getDato()->mostrarSolicitud();
		cout << endl;

		aux = aux->getSiguiente();
	}
}

SolicitudEnvio* ListaSolicitudes::buscar(string codigo) const {
	NodoSolicitud* aux = primero;

	while (aux != nullptr)
	{
		if (aux->getDato()->getCodigo() == codigo)
		{
			return aux->getDato();
		}
		aux = aux->getSiguiente();
	}
	return nullptr;
}

bool ListaSolicitudes::cambiarEstado(string codigo, string nuevoEstado) {
	SolicitudEnvio* solicitud = buscar(codigo);

	if (solicitud == nullptr || nuevoEstado == "Aprobada")
	{
		return false;
	}
	return solicitud->cambiarEstado(nuevoEstado);
}

bool ListaSolicitudes::estaVacio() const {
	return primero == nullptr;
}

NodoSolicitud* ListaSolicitudes::getPrimero() const {
	return primero;
}
