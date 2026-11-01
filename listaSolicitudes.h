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
	NodoSolicitud* buscar(string codigo) const;

	bool cambiarEstado(string codigo, string nuevoEstado);
};

#endif // !LISTASOLICITUDES_H


