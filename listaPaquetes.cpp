#include "listaPaquetes.h"
#include <string>

using namespace std;

ListaPaquetes::ListaPaquetes() {
	primero = nullptr;
	actual = nullptr;
	cantidad = 0;
}

ListaPaquetes::~ListaPaquetes() {
	while (primero != nullptr)
	{
		NodoPaquete* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar->getDato();
		delete borrar;
	}
}

void ListaPaquetes::insertarPaquete(Paquete* nuevoPaquete) {
	NodoPaquete* nuevo = new NodoPaquete(nuevoPaquete);
	if (primero == nullptr)
	{
		primero = nuevo;
	}
	else
	{
		NodoPaquete* aux = primero;
		while (aux->getSiguiente() != nullptr)
		{
			aux = aux->getSiguiente();
		}
		aux->setSiguiente(nuevo);
	}
	cantidad++;
}

void ListaPaquetes::mostrar() const {
	NodoPaquete* aux = primero;

	if (aux == nullptr)
	{
		cout << "No hay paquetes registrados." << endl;
	}

	while (aux != nullptr)
	{
		aux->getDato()->mostrarInfo();
		cout << endl;

		aux = aux->getSiguiente();
	}
}

Paquete* ListaPaquetes::buscar(string codigo) const {
	NodoPaquete* aux = primero;

	while (aux != nullptr)
	{
		if (aux->getDato()->getCodigo() == codigo)
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

bool ListaPaquetes::eliminar(string codigo) {
	NodoPaquete* aux = primero;
	NodoPaquete* anterior = nullptr;

	while (aux != nullptr)
	{
		if (aux->getDato()->getCodigo() == codigo)
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

bool ListaPaquetes::estaVacio() const {
	return primero == nullptr;
}

NodoPaquete* ListaPaquetes::getPrimero() const {
	return primero;
}
