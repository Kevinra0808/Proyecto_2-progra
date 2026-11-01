#include "registroBitacora.h"
#include <string>

using namespace std;

RegistroBitacora::RegistroBitacora(string estadoAnterior, string estadoNuevo, string fecha, Colaborador* responsable) {
	this->estadoAnterior = estadoAnterior;
	this->estadoNuevo = estadoNuevo;
	this->fecha = fecha;
	this->responsable = responsable;
}

//Gets
string RegistroBitacora::getEstadoAnterior() const {
	return estadoAnterior;
}

string RegistroBitacora::getEstadoNuevo() const {
	return estadoNuevo;
}

string RegistroBitacora::getFecha() const {
	return fecha;
}

Colaborador* RegistroBitacora::getResponsable() const {
	return responsable;
}

void RegistroBitacora::mostrarRegistro() const {
	cout << "Estado anterior: " << estadoAnterior << endl;
	cout << "Estado nuevo: " << estadoNuevo << endl;
	cout << "Fecha del cambio de estado: " << fecha << endl;
	cout << "Responsable del cambio: " << responsable << endl;
}