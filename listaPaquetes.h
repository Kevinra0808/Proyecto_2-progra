#ifndef LISTAPAQUETES_H
#define LISTAPAQUETES_H
#include <iostream>
#include "nodoPaquete.h"

class ListaPaquetes
{
private:
	NodoPaquete* primero;
	NodoPaquete* actual;

	int cantidad;

public:
	ListaPaquetes();
	~ListaPaquetes();

	void insertarPaquete(Paquete* nuevoPaquete);
	void mostrar() const;
	Paquete* buscar(string codigo) const;
	bool eliminar(string codigo); // las condiciones se validan en CentroDistribucion
	bool estaVacio() const;
	NodoPaquete* getPrimero() const;

};

#endif // !LISTAPAQUETES_H
