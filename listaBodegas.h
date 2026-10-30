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

	bool eliminarBodega(string codigo);
};


#endif // !LISTABODEGAS_H



