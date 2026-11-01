#ifndef NODOCENTRODISTRIBUCION_H
#define NODOCENTRODISTRIBUCION_H
#include "centroDistribucion.h"
#include <iostream>

class NodoCentroDistribucion
{
	private:
		CentroDistribucion* dato;
		NodoCentroDistribucion* siguiente;

	public:
		NodoCentroDistribucion(CentroDistribucion* dato);

		CentroDistribucion* getDato() const;
		NodoCentroDistribucion* getSiguiente() const;

		void setSiguiente(NodoCentroDistribucion* nuevoSiguiente);
};

#endif // !NODOCENTRODISTRIBUCION_H


