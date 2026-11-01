#ifndef LISTADESPACHOS_H
#define LISTADESPACHOS_H
#include <iostream>
#include "nodoDespacho.h"

class ListaDespachos
{
private:

	NodoDespacho* primero;
	NodoDespacho* actual;
	int cantidad;

public:
	ListaDespachos();
	~ListaDespachos();

	void insertarDespacho(Despacho* nuevaDespacho);
	void mostrarDespachos() const;
	NodoDespacho* buscar(string codigo) const;

	bool cambiarEstado(string codigo, string nuevoEstado);
	bool estaVacio() const;
};

#endif // !LISTADESPACHOS_H