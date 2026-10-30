#include "listaBodegas.h"
#include <string>

using namespace std;

ListaBodegas::ListaBodegas() {
	primero = nullptr;
	actual = nullptr;
}

ListaBodegas::~ListaBodegas() {
	while (primero != nullptr)
	{
		NodoBodega* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar;
	}
}

void ListaBodegas::insertarBodega(Bodega* nuevoBodega) {
	NodoBodega* nuevo = new NodoBodega(nuevoBodega);
	if (primero == nullptr)
	{
		primero = nuevo;
	}
	else
	{
		NodoBodega* aux = primero;
		while (aux->getSiguiente() != nullptr)
		{
			aux = aux->getSiguiente();
		}
		aux->setSiguiente(nuevo);
	}
}

void ListaBodegas::mostrar() const {
	NodoBodega* aux = primero;

	while (aux != nullptr)
	{
		aux->getDato()->mostrarBodega();
		cout << endl;

		aux = aux->getSiguiente();
	}
}

Bodega* ListaBodegas::buscar(string codigo) const {
	NodoBodega* aux = primero;

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

bool ListaBodegas::eliminarBodega(string codigo) {
	NodoBodega* actual = primero;
	NodoBodega* anterior = nullptr;

	while (actual != nullptr)
	{
		if (actual->getDato()->getCodigo() == codigo)
		{
			if (!actual->getDato()->estaVacia()) {
				cout << "Error: La bodega no se puede eliminar porque aún tiene paquetes." << endl;
				return false;
			}

			if (anterior == nullptr)
			{
				primero = actual->getSiguiente();
			}
			else
			{
				anterior->setSiguiente(actual->getSiguiente());
			}

			delete actual->getDato();
			delete actual;
			cantidad--;
			return true;
		}
		anterior = actual;
		actual = actual->getSiguiente();
	}
	return false;
}