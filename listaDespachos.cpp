#include "listaDespachos.h"
#include <string>

using namespace std;

ListaDespachos::ListaDespachos() {
	primero = nullptr;
	actual = nullptr;
	cantidad = 0;
}

ListaDespachos::~ListaDespachos() {
	while (primero != nullptr)
	{
		NodoDespacho* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar->getDato();
		delete borrar;
	}
}

void ListaDespachos::insertarDespacho(Despacho* nuevaDespacho) {
	NodoDespacho* nuevo = new NodoDespacho(nuevaDespacho);
	if (primero == nullptr)
	{
		primero = nuevo;
	}
	else
	{
		NodoDespacho* aux = primero;
		while (aux->getSiguiente() != nullptr)
		{
			aux = aux->getSiguiente();
		}
		aux->setSiguiente(nuevo);
	}
	cantidad++;
}

void ListaDespachos::mostrarDespachos() const {
	NodoDespacho* aux = primero;

	if (aux == nullptr)
	{
		cout << "No hay despachos registrados." << endl;
	}

	while (aux != nullptr)
	{
		aux->getDato()->mostrarDespacho();
		cout << endl;

		aux = aux->getSiguiente();
	}
}

Despacho* ListaDespachos::buscar(string codigo) const {
	NodoDespacho* aux = primero;

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

bool ListaDespachos::estaVacio() const {
	return primero == nullptr;
}

NodoDespacho* ListaDespachos::getPrimero() const {
	return primero;
}
