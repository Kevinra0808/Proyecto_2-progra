#ifndef LISTABITACORA_H
#define LISTABITACORA_H
#include "nodoBitacora.h"

class ListaBitacora
{
private:
	NodoBitacora* primero;
	NodoBitacora* actual;

public:
	ListaBitacora();
	~ListaBitacora();

	void insertarBitacora(Bitacora* nuevoBitacora);
	void mostrarBitacora() const;
	bool estaVacia() const;
	NodoBitacora* getPrimero() const;
	bool contieneResponsable(Colaborador* colaborador) const;

};

#endif // !LISTABITACORA_H


