#include "paquete.h"
#include <string>

using namespace std;

Paquete::Paquete() {
	codigo = "";
	descripcion = "";
	peso = 0;
	categoria = "";
	clientePrope = nullptr;
	centroDis = "";
	estado = "";
}

Paquete::Paquete(string codigo, string descripcion, float peso, string categoria, Cliente* clientePrope, string centroDis) {
	this->codigo = codigo;
	this->descripcion = descripcion;
	this->peso = peso;
	this->categoria = categoria;
	this->clientePrope = clientePrope;
	this->centroDis = centroDis;
	estado = "Recibido";
}

//Gets
string Paquete::getCodigo() const {
	return codigo;
}

string Paquete::getDescripcion() const {
	return descripcion;
}

float Paquete::getPeso() const {
	return peso;
}

string Paquete::getCategoria() const {
	return categoria;
}

Cliente* Paquete::getClientePrope() const {
	return clientePrope;
}

string Paquete::getCentroDis() const {
	return centroDis;
}

string Paquete::getEstado() const {
	return estado;
}

//Sets
void Paquete::setDescripcion(string descripcion) {
	this->descripcion = descripcion;
}

void Paquete::setPeso(float peso) {
	this->peso = peso;
}

void Paquete::setCategoria(string categoria) {
	this->categoria = categoria;
}

void Paquete::setCentroDis(string centroDis) {
	this->centroDis = centroDis;
}

void Paquete::setEstado(string nuevoEstado) {
	estado = nuevoEstado;
}

void Paquete::mostrarInfo() const{
	cout << "Codigo: " << codigo << endl;
	cout << "Descripcion: " << descripcion << endl;
	cout << "Peso: " << peso << endl;
	cout << "Categoria: " << categoria << endl;
	cout << "Cliente Propetario: " << clientePrope->getIdentificacion() << " - " << clientePrope->getNombre() << endl;
	cout << "Centro de distribucion: " << centroDis << endl;
	cout << "Estado: " << estado << endl;
}