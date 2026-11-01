#ifndef LISTACLIENTES_H
#define LISTACLIENTES_H
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
	bool estaVacio() const;

};

#endif // !LISTACLIENTES_H



