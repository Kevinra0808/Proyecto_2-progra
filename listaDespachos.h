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
	Despacho* buscar(string codigo) const;

	bool estaVacio() const;
	NodoDespacho* getPrimero() const;
};

#endif // !LISTADESPACHOS_H
