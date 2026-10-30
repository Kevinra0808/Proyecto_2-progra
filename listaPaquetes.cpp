#include "listaPaquetes.h"
#include <string>

using namespace std;

ListaPaquetes::ListaPaquetes() {
	primero = nullptr;
	actual = nullptr;
}

ListaPaquetes::~ListaPaquetes() {
	while (primero != nullptr)
	{
		NodoPaquete* borrar = primero;
		primero = primero->getSiguiente();
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
}

void ListaPaquetes::mostrar() const {
	NodoPaquete* aux = primero;

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