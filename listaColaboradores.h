#ifndef LISTACOLABORADOR_H
#define LISTACOLABORADOR_H
#include "nodoColaborador.h"
#include <iostream>

class ListaColaboradores
{
private:
	NodoColaborador* primero;
	NodoColaborador* actual;

	int cantidad;

public:
	ListaColaboradores();
	~ListaColaboradores();

	void insertarColaborador(Colaborador* nuevoColaborador);
	void mostrar() const;
	Colaborador* buscar(string identi) const;

};

#endif // !LISTACOLABORADOR_H



