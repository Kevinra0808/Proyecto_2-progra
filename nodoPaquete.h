#ifndef NODOPAQUETE_H
#define NODOPAQUETE_H
#include "paquete.h"
#include <iostream>

class NodoPaquete
{
private:
	Paquete* dato;
	NodoPaquete* siguiente;

public:
	NodoPaquete(Paquete* dato);

	//Gets
	Paquete* getDato() const;
	NodoPaquete* getSiguiente() const;

	//Sets
	void setSiguiente(NodoPaquete* nuevoSiguiente);

};


#endif // !NODOPAQUETE_H



