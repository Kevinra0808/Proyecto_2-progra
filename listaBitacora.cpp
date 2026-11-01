#include "listaBitacora.h"
#include <string>

using namespace std;

ListaBitacora::ListaBitacora() {
	primero = nullptr;
	actual = nullptr;
}

ListaBitacora::~ListaBitacora() {
	while (primero != nullptr)
	{
		NodoBitacora* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar;
	}
}

void ListaBitacora::insertarBitacora(Bitacora* nuevoBitacora) {
	NodoBitacora* nuevo = new NodoBitacora(nuevoBitacora);
	if (primero == nullptr)
	{
		primero = nuevo;
	}
	else
	{
		NodoBitacora* aux = primero;
		while (aux->getSiguiente() != nullptr)
		{
			aux = aux->getSiguiente();
		}
		aux->setSiguiente(nuevo);
	}
}

void ListaBitacora::mostrarBitacora() const {
	NodoBitacora* aux = primero;

	while (aux != nullptr)
	{
		aux->getDato()->mostrar();
		cout << endl;

		aux = aux->getSiguiente();
	}
}