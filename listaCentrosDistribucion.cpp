#include "listaCentrosDistribucion.h"
#include <string>

using namespace std;

ListaCentrosDistribucion::ListaCentrosDistribucion() {
	primero = nullptr;
	actual = nullptr;
}

ListaCentrosDistribucion::~ListaCentrosDistribucion() {
	while (primero != nullptr)
	{
		NodoCentroDistribucion* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar;
	}
}

void ListaCentrosDistribucion::insertarCentro(CentroDistribucion* nuevoCentro) {
	NodoCentroDistribucion* nuevo = new NodoCentroDistribucion(nuevoCentro);
	if (primero == nullptr)
	{
		primero = nuevo;
	}
	else
	{
		NodoCentroDistribucion* aux = primero;
		while (aux->getSiguiente() != nullptr)
		{
			aux = aux->getSiguiente();
		}
		aux->setSiguiente(nuevo);
	}
}

void ListaCentrosDistribucion::mostrarCentros() const {
	NodoCentroDistribucion* aux = primero;

	while (aux != nullptr)
	{
		aux->getDato()->mostrarCentro();
		cout << endl;

		aux = aux->getSiguiente();
	}
}

CentroDistribucion* ListaCentrosDistribucion::buscar(string codigo) const {
	NodoCentroDistribucion* aux = primero;

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

bool ListaCentrosDistribucion::eliminarCentro(string codigo) {
	NodoCentroDistribucion* actual = primero;
	NodoCentroDistribucion* anterior = nullptr;

	while (actual != nullptr)
	{
		if (actual->getDato()->getCodigo() == codigo)
		{
			if (!actual->getDato()->estaVacio()) {	
				cout << "Error: El centro de distribucion no se puede eliminar porque aun tiene paquetes." << endl;
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
			
			return true;
		}
		anterior = actual;
		actual = actual->getSiguiente();
	}
	return false;
}
