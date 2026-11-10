#include "empresa.h"
#include "cliente.h"



Empresa::Empresa(string identi, string nombre, string telefono,	string correo, string activiEco, float descuento): Cliente(identi,nombre,telefono,correo) {
	this->activiEco = activiEco;
	this->descuento = descuento;
}

//Gets
string Empresa::getActiviEco() const {
	return activiEco;
}

float Empresa::getDescuento() const {
	return descuento;
}

//Sets
void Empresa::setActiviEco(string activiEco) {
	this->activiEco = activiEco;
}

void Empresa::setDescuento(float descuento) {
	this->descuento = descuento;
}

void Empresa::mostrarInfo() const {
	Cliente::mostrarInfo(); //llama el mostrarInfo de cliente y sobreescribe y muestra la actividad economica y el descuento
	cout << "Actividad Economica: " << activiEco << endl;
	cout << "Descuento permitido: " << descuento << endl;
}


string Empresa::getTipo() const {
	return "Empresa";
}
