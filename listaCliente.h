#ifndef LISTACLIENTE_H
#define LISTACLIENTE_H
#include "nodoCliente.h"

class ListaCliente
{
private:

	NodoCliente* primero;
	NodoCliente* actual;

public:

	//Constructor y desctructor
	ListaCliente();
	~ListaCliente();

	//metodos
	void insertar(Cliente* cliente);
	Cliente* buscar(string identi) const;
	void mostrarTodos() const;

};

#endif // !LISTACLIENTE_H



