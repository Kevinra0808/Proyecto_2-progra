#ifndef DESPACHO_H
#define DESPACHO_H
#include <iostream>
#include "solicitudEnvio.h"
#include "paquete.h"
#include "cliente.h"
#include "colaborador.h"

class Despacho
{
private:
	string codigo;
	SolicitudEnvio* solicitudAsociada;
	Paquete* paquete;
	Cliente* cliente;
	Colaborador* responsable;
	string centroOrigen;
	string destino;
	string fechaDespacho;
	string hora;                       
	string estado;                     

public:
	
	Despacho(string codigo, SolicitudEnvio* solicitudAsociada, Paquete* paquete, Cliente* cliente, Colaborador* responsable, string centroOrigen, string destino, string fechaDespacho, string hora);

	// Gets
	string getCodigo() const;
	SolicitudEnvio* getSolicitudAsociada() const;
	Paquete* getPaquete() const;
	Cliente* getCliente() const;
	Colaborador* getResponsable() const;
	string getCentroOrigen() const;
	string getDestino() const;
	string getFechaDespacho() const;
	string getHora() const;
	string getEstado() const;

	// Sets
	void setSolicitudAsociada(SolicitudEnvio* solicitudAsociada);
	void setPaquete(Paquete* paquete);
	void setCliente(Cliente* cliente);
	void setResponsable(Colaborador* responsable);
	void setCentroOrigen(string centroOrigen);
	void setDestino(string destino);
	void setFechaDespacho(string fechaDespacho);
	void setHora(string hora);
	void setEstado(string nuevoEstado);

	void mostrarDespacho() const;
	bool finalizarEntrega(Despacho* despacho, Paquete* paquete);
};

#endif // !DESPACHO_H