#ifndef LISTACENTROSDISTRIBUCION_H
#define LISTACENTROSDISTRIBUCION_H
#include "nodoCentroDistribucion.h"
#include <iostream>

class ListaCentrosDistribucion
{
private:
	NodoCentroDistribucion* primero;
	NodoCentroDistribucion* actual;

public:
	ListaCentrosDistribucion();
	~ListaCentrosDistribucion();

	void insertarCentro(CentroDistribucion* dato);
	void mostrarCentros() const;
	CentroDistribucion* buscar(string codigo) const;
	bool eliminarCentro(string codigo);

};

#endif // !LISTACENTROSDISTRIBUCION_H


