#include "despacho.h"
#include <string>

Despacho::Despacho(string codigo, SolicitudEnvio* solicitudAsociada, Paquete* paquete, Cliente* cliente, Colaborador* responsable, string centroOrigen, string destino, string fechaDespacho, string hora) {
	this->codigo = codigo;
	this->solicitudAsociada = solicitudAsociada;
	this->paquete = paquete;
	this->cliente = cliente;
	this->responsable = responsable;
	this->centroOrigen = centroOrigen;
	this->destino = destino;
	this->fechaDespacho = fechaDespacho;
	this->hora = hora;
	this->estado = "En proceso";
}

// Gets
string Despacho::getCodigo() const {
	return codigo;
}
SolicitudEnvio* Despacho::getSolicitudAsociada() const {
	return solicitudAsociada;
}
Paquete* Despacho::getPaquete() const {
	return paquete;
}
Cliente* Despacho::getCliente() const {
	return cliente;
}
Colaborador* Despacho::getResponsable() const {
	return responsable;
}
string Despacho::getCentroOrigen() const {
	return centroOrigen;
}
string Despacho::getDestino() const {
	return destino;
}
string Despacho::getFechaDespacho() const {
	return fechaDespacho;
}
string Despacho::getHora() const {
	return hora;
}
string Despacho::getEstado() const {
	return estado;
}

// Sets
void Despacho::setSolicitudAsociada(SolicitudEnvio* solicitudAsociada) {
	this->solicitudAsociada = solicitudAsociada;
}

void Despacho::setPaquete(Paquete* paquete) {
	this->paquete = paquete;
}

void Despacho::setCliente(Cliente* cliente) {
	this->cliente = cliente;
}

void Despacho::setResponsable(Colaborador* responsable) {
	this->responsable = responsable;
}

void Despacho::setCentroOrigen(string centroOrigen) {
	this->centroOrigen = centroOrigen;
}

void Despacho::setDestino(string destino) {
	this->destino = destino;
}

void Despacho::setFechaDespacho(string fechaDespacho) {
	this->fechaDespacho = fechaDespacho;
}

void Despacho::setHora(string hora) {
	this->hora = hora;
}

void Despacho::setEstado(string nuevoEstado) {
	this->estado = nuevoEstado;
}

void Despacho::mostrarDespacho() const {
	cout << "Codigo de Despacho: " << codigo << endl;
	if (solicitudAsociada != nullptr && paquete != nullptr && cliente != nullptr && responsable != nullptr)
	{
		cout << "Solicitud Asociada: " << solicitudAsociada->getCodigo() << endl;
		cout << "Paquete: " << paquete->getDescripcion() << endl;
		cout << "Cliente: " << cliente->getNombre() << endl;
		cout << "Responsable: " << responsable->getNombre() << endl;
	}
	cout << "Centro de Origen: " << centroOrigen << endl;
	cout << "Destino: " << destino << endl;
	cout << "Fecha de Despacho: " << fechaDespacho << endl;
	cout << "Hora: " << hora << endl;
	cout << "Estado: " << estado << endl;
}

bool Despacho::finalizarEntrega(Despacho* despacho, Paquete* paquete) {
	if (despacho->getEstado() == "En proceso" && paquete->getEstado() == "En tránsito") {
		despacho->setEstado("Finalizado");
		paquete->setEstado("Entregado");
		return true;
	}
	else {
		return false;
	}
}