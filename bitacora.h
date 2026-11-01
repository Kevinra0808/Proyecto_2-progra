#ifndef BITACORA_H
#define BITACORA_H
#include "colaborador.h"
#include <iostream>

class Bitacora
{
private:
	string estadoAnterior;
	string estadoNuevo;
	string fecha;
	Colaborador* responsable;

public:
	Bitacora(string estadoAnterior, string estadoNuevo, string fecha, Colaborador* responsable);
	
	string getEstadoAnterior() const;
	string getEstadoNuevo() const;
	string getFecha() const;
	Colaborador* getResponsable() const;

	void mostrar() const;

};

#endif // !BITACORA_H


