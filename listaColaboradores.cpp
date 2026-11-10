#include "listaColaboradores.h"
#include <string>

using namespace std;

ListaColaboradores::ListaColaboradores() {
	primero = nullptr;
	actual = nullptr;
	cantidad = 0;
}

ListaColaboradores::~ListaColaboradores() {
	while (primero != nullptr)
	{
		NodoColaborador* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar->getDato();
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
	cantidad++;
}

void ListaColaboradores::mostrar() const {
	NodoColaborador* aux = primero;

	if (aux == nullptr)
	{
		cout << "No hay colaboradores registrados." << endl;
	}

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

bool ListaColaboradores::eliminar(string identi) {
	NodoColaborador* aux = primero;
	NodoColaborador* anterior = nullptr;

	while (aux != nullptr)
	{
		if (aux->getDato()->getIdenti() == identi)
		{
			if (anterior == nullptr)
			{
				primero = aux->getSiguiente();
			}
			else
			{
				anterior->setSiguiente(aux->getSiguiente());
			}
			delete aux->getDato();
			delete aux;
			cantidad--;
			return true;
		}
		anterior = aux;
		aux = aux->getSiguiente();
	}
	return false;
}

bool ListaColaboradores::estaVacio() const {
	return primero == nullptr;
}

NodoColaborador* ListaColaboradores::getPrimero() const {
	return primero;
}
