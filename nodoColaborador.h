#ifndef NODOCOLABORADOR_H
#define NODOCOLABORADOR_H
#include <iostream>
#include "colaborador.h"

class NodoColaborador
{
private:
	Colaborador* dato;
	NodoColaborador* siguiente;

public:
	NodoColaborador(Colaborador* dato);

	//Gets
	Colaborador* getDato() const;
	NodoColaborador* getSiguiente() const;

	//Sets
	void setSiguiente(NodoColaborador* nuevoSiguiente);

};

#endif // !NODOCOLABORADOR_H


