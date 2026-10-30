#ifndef REGISTROBITACORA_H
#define REGISTROBITACORA_H
#include "colaborador.h"
#include <iostream>

class RegistroBitacora
{
private:
	string estadoAnterior;
	string estadoNuevo;
	string fecha;
	Colaborador* responsable;

public:
	RegistroBitacora(string estadoAnterior, string estadoNuevo, string fecha, Colaborador* responsable);
	
	string getEstadoAnterior() const;
	string getEstadoNuevo() const;
	string getFecha() const;
	Colaborador* getResponsable() const;

	void mostrarRegistro() const;

};

#endif // !REGISTROBITACORA_H


