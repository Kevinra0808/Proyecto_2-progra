#include "listaCliente.h"
#include <string>

using namespace std;

ListaCliente::ListaCliente() {
	primero = nullptr;
	actual = nullptr;
}

ListaCliente::~ListaCliente() {
	while (primero != nullptr)
	{
		NodoCliente* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar;
	}
}

void ListaCliente::insertar(Cliente* cliente) {
	NodoCliente* nuevo = new NodoCliente(cliente);
	if (primero == nullptr) 
	{
		primero = nuevo;
	}
	else 
	{
		NodoCliente* aux = primero;
		while (aux->getSiguiente() != nullptr) 
		{
			aux = aux->getSiguiente();
		}
		aux->setSiguiente(nuevo);
	}
}

Cliente* ListaCliente::buscar(string identi) const {
	NodoCliente* aux = primero;

	while (aux != nullptr)
	{
		if (aux->getCliente()->getIdentificacion() == identi)
		{
			return aux->getCliente();
		}
		else
		{
			aux = aux->getSiguiente();
		}
	}

	return nullptr;
}

void ListaCliente::mostrarTodos() const {
	NodoCliente* aux = primero;

	while (aux != nullptr)
	{
		aux->getCliente()->mostrarInfo();
		cout << endl;

		aux = aux->getSiguiente();
	}
}