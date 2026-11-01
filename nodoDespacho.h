#ifndef NODODESPACHO_H
#define NODODESPACHO_H
#include <iostream>
#include "despacho.h"

class NodoDespacho
{
private:
	Despacho* dato;
	NodoDespacho* siguiente;

public:
	NodoDespacho(Despacho* dato);

	Despacho* getDato() const;
	NodoDespacho* getSiguiente() const;

	void setSiguiente(NodoDespacho* nuevoSiguiente);
};

#endif // !NODODESPACHO_H


