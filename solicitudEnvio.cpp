#include "solicitudEnvio.h"
#include <string>

using namespace std;

SolicitudEnvio::SolicitudEnvio(string codigo, Cliente* soliCliente, Paquete* paquete, Colaborador* responsable, string centroOrigen, string destinoEntrega, string fechaSoli) {
	this->codigo = codigo;
	this->soliCliente = soliCliente;
	this->paquete = paquete;
	this->responsable = responsable;
	this->centroOrigen = centroOrigen;
	this->destinoEntrega = destinoEntrega;
	this->fechaSoli = fechaSoli;
	this->estado = "Pendiente";

	calcularCostoEstimado();
}

//Gets
string SolicitudEnvio::getCodigo() const {
	return codigo;
}
Cliente* SolicitudEnvio::getSoliCliente() const {
	return soliCliente;
}
Paquete* SolicitudEnvio::getPaquete() const {
	return paquete;
}
Colaborador* SolicitudEnvio::getResponsable() const {
	return responsable;
}
string SolicitudEnvio::getCentroOrigen() const {
	return centroOrigen;
}
string SolicitudEnvio::getDestinoEntrega() const {
	return destinoEntrega;
}
string SolicitudEnvio::getFechaSoli() const {
	return fechaSoli;
}
double SolicitudEnvio::getCostoEstimado() const {
	return costoEstimado;
}
string SolicitudEnvio::getEstado() const {
	return estado;
}

//Sets
void SolicitudEnvio::setSoliCliente(Cliente* soliCliente) {
	this->soliCliente = soliCliente;
}
void SolicitudEnvio::setPaquete(Paquete* paquete) {
	this->paquete = paquete;
}
void SolicitudEnvio::setResponsable(Colaborador* responsable) {
	this->responsable = responsable;
}
void SolicitudEnvio::setCentroOrigen(string centroOrigen) {
	this->centroOrigen = centroOrigen;
}
void SolicitudEnvio::setDestinoEntrega(string destinoEntrega) {
	this->destinoEntrega = destinoEntrega;
}
void SolicitudEnvio::setFechaSoli(string fechaSoli) {
	this->fechaSoli = fechaSoli;
}
void SolicitudEnvio::setCostoEstimado(double costoEstimado) {
	this->costoEstimado = costoEstimado;
}
void SolicitudEnvio::setEstado(string nuevoEstado) {
	this->estado = nuevoEstado;
}

void SolicitudEnvio::mostrarSolicitud() const {

	cout << "Codigo de Solicitud: " << codigo << endl;
	if (soliCliente != nullptr && paquete != nullptr && responsable != nullptr)
	{
		cout << "Cliente: " << soliCliente->getNombre() << endl;
		cout << "Paquete: " << paquete->getDescripcion() << endl;
		cout << "Responsable: " << responsable->getNombre() << endl;
	}
	cout << "Centro de Origen: " << centroOrigen << endl;
	cout << "Destino de Entrega: " << destinoEntrega << endl;
	cout << "Fecha de Solicitud: " << fechaSoli << endl;
	cout << "Costo Estimado: " << costoEstimado << endl;
	cout << "Estado: " << estado << endl;
}

double SolicitudEnvio::calcularCostoBase(float peso, string categoria) const {

	for (int i = 0; i < categoria.length(); i++)
	{
		categoria[i] = tolower(categoria[i]);
	}

	if (categoria == "general")
	{
		return peso * 1500;
	}
	else if (categoria == "fragil")
	{
		return peso * 2000;
	}
	else if (categoria == "tecnologia")
	{
		return peso * 2500;
	}
	else if (categoria == "documentos")
	{
		return peso * 1000;
	}
	else {
		int error = -1; // Codigo de error para categoria no valida
		return error;
	}
}

void SolicitudEnvio::calcularCostoEstimado() {
	float costoBase = calcularCostoBase(paquete->getPeso(), paquete->getCategoria());
	Empresa* empresa = dynamic_cast<Empresa*>(soliCliente);
	
	if (empresa != nullptr)
	{
		costoEstimado = costoBase - ((costoBase * empresa->getDescuento()) / 100);
		cout << "Costo estimado con descuento aplicado: " << costoEstimado << endl;
	}
	else
	{
		costoEstimado = costoBase;
		cout << "Costo estimado: " << costoEstimado << endl;
	}
}