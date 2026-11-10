#ifndef LISTABODEGAS_H
#define LISTABODEGAS_H
#include "nodoBodega.h"
#include <iostream>

class ListaBodegas
{
private:
	NodoBodega* primero;
	NodoBodega* actual;

	int cantidad;

public:

	ListaBodegas();
	~ListaBodegas();

	void insertarBodega(Bodega* dato);
	void mostrar() const;
	Bodega* buscar(string codigo) const;

	// Solo elimina si todas las celdas estan libres
	bool eliminarBodega(string codigo);

	bool estaVacio() const;
	int getCantidad() const;
	NodoBodega* getPrimero() const;
};


#endif // !LISTABODEGAS_H
