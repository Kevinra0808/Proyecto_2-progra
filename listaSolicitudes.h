#ifndef LISTASOLICITUDES_H
#define LISTASOLICITUDES_H
#include <iostream>
#include "nodoSolicitud.h"

class ListaSolicitudes
{
private:
	NodoSolicitud* primero;
	NodoSolicitud* actual;
	int cantidad;

public:
	ListaSolicitudes();
	~ListaSolicitudes();

	void insertarSolicitud(SolicitudEnvio* nuevaSolicitud);
	void mostrarSolicitudes() const;
	SolicitudEnvio* buscar(string codigo) const;

	// Solo permite Pendiente -> Rechazada / Anulada (la aprobacion se hace en CentroDistribucion)
	bool cambiarEstado(string codigo, string nuevoEstado);

	bool estaVacio() const;
	NodoSolicitud* getPrimero() const;
	
};

#endif // !LISTASOLICITUDES_H
