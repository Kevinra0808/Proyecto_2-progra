#include "listaClientes.h"
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
		delete borrar->getCliente();
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

	if (aux == nullptr)
	{
		cout << "No hay clientes registrados." << endl;
	}

	while (aux != nullptr)
	{
		aux->getCliente()->mostrarInfo();
		cout << endl;

		aux = aux->getSiguiente();
	}
}

bool ListaCliente::eliminar(string identi) {
	NodoCliente* aux = primero;
	NodoCliente* anterior = nullptr;

	while (aux != nullptr)
	{
		if (aux->getCliente()->getIdentificacion() == identi)
		{
			if (anterior == nullptr)
			{
				primero = aux->getSiguiente();
			}
			else
			{
				anterior->setSiguiente(aux->getSiguiente());
			}
			delete aux->getCliente();
			delete aux;
			return true;
		}
		anterior = aux;
		aux = aux->getSiguiente();
	}
	return false;
}

bool ListaCliente::estaVacio() const {
	return primero == nullptr;
}

NodoCliente* ListaCliente::getPrimero() const {
	return primero;
}
