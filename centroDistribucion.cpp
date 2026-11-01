#include "centroDistribucion.h"
#include <string>

using namespace std;

CentroDistribucion::CentroDistribucion(string codigo, string nombre, string provincia, string direccionDescriptiva, string telefono) {
	this->codigo = codigo;
	this->nombre = nombre;
	this->provincia = provincia;
	this->direccionDescriptiva = direccionDescriptiva;
	this->telefono = telefono;
}

//Gets
string CentroDistribucion::getCodigo() {
	return codigo;
}
string CentroDistribucion::getNombre() {
	return nombre;
}
string CentroDistribucion::getProvincia() {
	return provincia;
}
string CentroDistribucion::getDireccionDescriptiva() {
	return direccionDescriptiva;
}
string CentroDistribucion::getTelefono() {
	return telefono;
}

//Gets listas
ListaBodegas* CentroDistribucion::getListaBodegas() {
	return &listaBodegas;
}
ListaSolicitudes* CentroDistribucion::getListaSolicitudes() {
	return &listaSolicitudes;
}
ListaDespachos* CentroDistribucion::getListaDespachos() {
	return &listaDespachos;
}

ListaPaquetes* CentroDistribucion::getListaPaquetes() {
	return &listaPaquetes;
}
ListaCliente* CentroDistribucion::getListaClientes() {
	return &listaClientes;
}
ListaColaboradores* CentroDistribucion::getListaColaboradores() {
	return &listaColaboradores;
}


void CentroDistribucion::mostrarCentro() const {
	cout << "Codigo: " << codigo << endl;
	cout << "Nombre: " << nombre << endl;
	cout << "Provincia: " << provincia << endl;
	cout << "Direccion Descriptiva: " << direccionDescriptiva << endl;
	cout << "Telefono: " << telefono << endl;
}
bool CentroDistribucion::estaVacio() const {
	return listaClientes.estaVacio() &&
		listaColaboradores.estaVacio() &&
		listaBodegas.estaVacio() &&
		listaPaquetes.estaVacio() &&
		listaSolicitudes.estaVacio() &&
		listaDespachos.estaVacio();
}