#include "solicitudEnvio.h"
#include <string>

using namespace std;

const double SolicitudEnvio::tarifaGeneral = 1500;
const double SolicitudEnvio::tarifaFragil = 2000;
const double SolicitudEnvio::tarifaTecnologia = 2500;
const double SolicitudEnvio::tarifaDocumentos = 1000;

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
bool SolicitudEnvio::cambiarEstado(string nuevoEstado) {
	if (estado != "Pendiente") {
		return false;
	}
	if (nuevoEstado != "Aprobada" && nuevoEstado != "Rechazada" && nuevoEstado != "Anulada") {
		return false;
	}
	estado = nuevoEstado;
	return true;
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

double SolicitudEnvio::getTarifa(string categoria) {
	if (categoria == "General") return tarifaGeneral;
	if (categoria == "Fragil") return tarifaFragil;
	if (categoria == "Tecnologia") return tarifaTecnologia;
	if (categoria == "Documentos") return tarifaDocumentos;
	return -1;
}

double SolicitudEnvio::calcularCostoBase(float peso, string categoria) const {
	double tarifa = getTarifa(categoria);

	if (tarifa < 0) {
		return -1; // categoria no valida
	}
	return peso * tarifa;
}

void SolicitudEnvio::calcularCostoEstimado() {
	double costoBase = calcularCostoBase(paquete->getPeso(), paquete->getCategoria());

	float descuento = soliCliente->getDescuento();
	costoEstimado = costoBase - ((costoBase * descuento) / 100);
}
