#include "listaBitacora.h"
#include <string>

using namespace std;

ListaBitacora::ListaBitacora() {
	primero = nullptr;
	actual = nullptr;
}

ListaBitacora::~ListaBitacora() {
	while (primero != nullptr)
	{
		NodoBitacora* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar->getDato();
		delete borrar;
	}
}

void ListaBitacora::insertarBitacora(Bitacora* nuevoBitacora) {
	NodoBitacora* nuevo = new NodoBitacora(nuevoBitacora);
	if (primero == nullptr)
	{
		primero = nuevo;
	}
	else
	{
		NodoBitacora* aux = primero;
		while (aux->getSiguiente() != nullptr)
		{
			aux = aux->getSiguiente();
		}
		aux->setSiguiente(nuevo);
	}
}

void ListaBitacora::mostrarBitacora() const {
	NodoBitacora* aux = primero;

	while (aux != nullptr)
	{
		aux->getDato()->mostrar();
		cout << endl;

		aux = aux->getSiguiente();
	}
}

bool ListaBitacora::estaVacia() const {
	return primero == nullptr;
}

NodoBitacora* ListaBitacora::getPrimero() const {
	return primero;
}

bool ListaBitacora::contieneResponsable(Colaborador* colaborador) const {
	NodoBitacora* aux = primero;

	while (aux != nullptr)
	{
		if (aux->getDato()->getResponsable() == colaborador)
		{
			return true;
		}
		aux = aux->getSiguiente();
	}
	return false;
}
