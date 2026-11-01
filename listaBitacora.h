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

};

#endif // !LISTABITACORA_H


