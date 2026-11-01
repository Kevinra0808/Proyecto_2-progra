#ifndef NODOSOLICITUD_H
#define NODOSOLICITUD_H
#include <iostream>
#include "solicitudEnvio.h"

class NodoSolicitud
{
private:

	SolicitudEnvio* dato;
	NodoSolicitud* siguiente;

public:
	NodoSolicitud(SolicitudEnvio* dato);

	//Gets
	SolicitudEnvio* getDato() const;
	NodoSolicitud* getSiguiente() const;

	//Sets
	void setSiguiente(NodoSolicitud* nuevoSiguiente);
};

#endif // !NODOSOLICITUD_H


