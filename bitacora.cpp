#include "bitacora.h"
#include <string>

using namespace std;

Bitacora::Bitacora(string estadoAnterior, string estadoNuevo, string fecha, Colaborador* responsable) {
	this->estadoAnterior = estadoAnterior;
	this->estadoNuevo = estadoNuevo;
	this->fecha = fecha;
	this->responsable = responsable;
}

//Gets
string Bitacora::getEstadoAnterior() const {
	return estadoAnterior;
}

string Bitacora::getEstadoNuevo() const {
	return estadoNuevo;
}

string Bitacora::getFecha() const {
	return fecha;
}

Colaborador* Bitacora::getResponsable() const {
	return responsable;
}

void Bitacora::mostrar() const {
	cout << "Estado anterior: " << estadoAnterior << endl;
	cout << "Estado nuevo: " << estadoNuevo << endl;
	cout << "Fecha del cambio de estado: " << fecha << endl;

	if (responsable != nullptr)
	{
		cout << "Responsable del cambio: " << responsable->getIdenti() << " - " << responsable->getNombre() << endl;
	}
	else
	{
		cout << "No hubo un responsable asignado al cambio\n";
	}
}