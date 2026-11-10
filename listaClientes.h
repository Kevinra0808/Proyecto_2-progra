#ifndef LISTACLIENTES_H
#define LISTACLIENTES_H
#include "nodoCliente.h"

class ListaCliente
{
private:

	NodoCliente* primero;
	NodoCliente* actual;

public:

	ListaCliente();
	~ListaCliente();

	void insertar(Cliente* cliente);
	Cliente* buscar(string identi) const;
	void mostrarTodos() const;
	bool eliminar(string identi);
	bool estaVacio() const;
	NodoCliente* getPrimero() const;

};

#endif // !LISTACLIENTES_H
