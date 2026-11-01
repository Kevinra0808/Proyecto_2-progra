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
		delete borrar;
	}
}

void ListaDespachos::insertarDespacho(Despacho* nuevoDespacho) {
	NodoDespacho* nuevo = new NodoDespacho(nuevoDespacho);
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

	while (aux != nullptr)
	{
		aux->getDato()->mostrarDespacho();
		cout << endl;

		aux = aux->getSiguiente();
	}
}

NodoDespacho* ListaDespachos::buscar(string codigo) const {
	NodoDespacho* aux = primero;

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

bool ListaDespachos::cambiarEstado(string codigo, string nuevoEstado) {
	NodoDespacho* nodoEncontrado = buscar(codigo);
	if (nodoEncontrado != nullptr) {
		nodoEncontrado->getDato()->setEstado(nuevoEstado);
		return true;
	}
	return false;
}