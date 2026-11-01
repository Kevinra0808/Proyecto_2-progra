#ifndef NODOBITACORA_H
#define NODOBITACORA_H

#include "bitacora.h"

class NodoBitacora
{
private:
	Bitacora* dato;
	NodoBitacora* siguiente;

public:
	NodoBitacora(Bitacora* dato);

	//Gets
	Bitacora* getDato() const;
	NodoBitacora* getSiguiente() const;

	void setSiguiente(NodoBitacora* nuevoSiguiente);


};

#endif // !NODOBITACORA_H


