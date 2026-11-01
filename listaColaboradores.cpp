#include "listaColaboradores.h"
#include <string>

using namespace std;

ListaColaboradores::ListaColaboradores() {
	primero = nullptr;
	actual = nullptr;
}

ListaColaboradores::~ListaColaboradores() {
	while (primero != nullptr)
	{
		NodoColaborador* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar;
	}
}

void ListaColaboradores::insertarColaborador(Colaborador* nuevoColaborador) {
	NodoColaborador* nuevo = new NodoColaborador(nuevoColaborador);
	if (primero == nullptr)
	{
		primero = nuevo;
	}
	else
	{
		NodoColaborador* aux = primero;
		while (aux->getSiguiente() != nullptr)
		{
			aux = aux->getSiguiente();
		}
		aux->setSiguiente(nuevo);
	}
}

void ListaColaboradores::mostrar() const {
	NodoColaborador* aux = primero;

	while (aux != nullptr)
	{
		aux->getDato()->mostrarInfo();
		cout << endl;

		aux = aux->getSiguiente();
	}
}

Colaborador* ListaColaboradores::buscar(string identi) const {
	NodoColaborador* aux = primero;

	while (aux != nullptr)
	{
		if (aux->getDato()->getIdenti() == identi)
		{
			return aux->getDato();
		}
		else
		{
			aux = aux->getSiguiente();
		}
	}
	return nullptr;
}