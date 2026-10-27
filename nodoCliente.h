#ifndef NODOCLIENTE_H
#define NODOCLIENTE_H
#include "cliente.h"
#include <iostream>


class NodoCliente
{
private:

	Cliente* cliente;
	NodoCliente* siguiente;

public:
	NodoCliente(Cliente* cliente);

	//Gets
	Cliente* getCliente();
	NodoCliente* getSiguiente();

	//sets
	void setCliente(Cliente* cliente);
	void setSiguiente(NodoCliente* siguiente);
};


#endif // !NODOCLIENTE_H



