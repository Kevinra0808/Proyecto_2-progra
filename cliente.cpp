#include "cliente.h"

Cliente::Cliente(string identi, string nombre, string telefono, string correo) {
	this->identi = identi;
	this->nombre = nombre;
	this->telefono = telefono;
	this->correo = correo;
}

string Cliente::getIdentificacion() const {
	return identi;
}

string Cliente::getNombre() const {
	return nombre;
}

string Cliente::getTelefono() const {
	return telefono;
}

string Cliente::getCorreo() const {
	return correo;
}

void Cliente::setNombre(string nombre) {
	this->nombre = nombre;
}

void Cliente::setTelefono(string telefono) {
	this->telefono = telefono;
}

void Cliente::setCorreo(string correo) {
	this->correo = correo;
}

void Cliente::mostrarInfo() const {
	cout << "Identificacion: " << identi << endl;
	cout << "Nombre: " << nombre << endl;
	cout << "Telefono: " << telefono << endl;
	cout << "Correo: " << correo << endl;
}

