#ifndef NODOBODEGA_H
#define NODOBODEGA_H
#include <iostream>
#include "bodega.h"

class NodoBodega
{
private:
	Bodega* dato;
	NodoBodega* siguiente;

public:
	NodoBodega(Bodega* dato);

	//Gets
	Bodega* getDato() const;
	NodoBodega* getSiguiente() const;

	//Sets
	void setSiguiente(NodoBodega* nuevoSiguiente);
};

#endif // !NODOBODEGA_H


