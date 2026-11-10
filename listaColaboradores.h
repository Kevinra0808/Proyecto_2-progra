#ifndef LISTACOLABORADORES_H
#define LISTACOLABORADORES_H
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
	bool eliminar(string identi); // las dependencias se validan en CentroDistribucion
	bool estaVacio() const;
	NodoColaborador* getPrimero() const;

};

#endif // !LISTACOLABORADORES_H
