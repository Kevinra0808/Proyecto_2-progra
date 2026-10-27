#include "colaborador.h"

Colaborador::Colaborador(string identi, string nombre, string fechaIngreso, string puesto) {
	this->identi = identi;
	this->nombre = nombre;
	this->fechaIngreso = fechaIngreso;
	this->puesto = puesto;
}

//Gets
string Colaborador::getIdenti() const{
	return identi;
}

string Colaborador::getNombre() const{
	return nombre;
}

string Colaborador::getFechaIngreso() const{
	return fechaIngreso;
}

string Colaborador::getPuesto() const{
	return puesto;
}

//Sets
void Colaborador::setNombre(string nombre) {
	this->nombre = nombre;
}

void Colaborador::setFechaIngreso(string fechaIngreso) {
	this->fechaIngreso = fechaIngreso;
}

void Colaborador::setPuesto(string puesto) {
	this->puesto = puesto;
}


void Colaborador::mostrarInfo() const{
	cout << "Identificacion: " << identi << endl;
	cout << "Nombre: " << nombre << endl;
	cout << "Fecha de Ingreso: " << fechaIngreso << endl;
	cout << "Puesto: " << puesto << endl;
}