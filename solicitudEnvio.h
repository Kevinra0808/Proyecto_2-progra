#ifndef SOLICITUDENVIO_H
#define SOLICITUDENVIO_H
#include <iostream>
#include "cliente.h"
#include "paquete.h"
#include "colaborador.h"
#include "empresa.h"

class SolicitudEnvio
{
private:
	string codigo;
	Cliente* soliCliente;
	Paquete* paquete;
	Colaborador* responsable;
	string centroOrigen;
	string destinoEntrega;
	string fechaSoli;
	double costoEstimado;
	string estado;


public:
	SolicitudEnvio(string codigo, Cliente* soliCliente, Paquete* paquete, Colaborador* responsable, string centroOrigen, string destinoEntrega, string fechaSoli);
	
	//Gets
	string getCodigo() const;
	Cliente* getSoliCliente() const;
	Paquete* getPaquete() const;
	Colaborador* getResponsable() const;
	string getCentroOrigen() const;
	string getDestinoEntrega() const;
	string getFechaSoli() const;
	double getCostoEstimado() const;
	string getEstado() const;

	//Sets
	void setSoliCliente(Cliente* soliCliente);
	void setPaquete(Paquete* paquete);
	void setResponsable(Colaborador* responsable);
	void setCentroOrigen(string centroOrigen);
	void setDestinoEntrega(string destinoEntrega);
	void setFechaSoli(string fechaSoli);
	void setCostoEstimado(double costoEstimado);
	void setEstado(string nuevoEstado);

	void mostrarSolicitud() const;
	double calcularCostoBase(float peso, string categoria) const;
	void calcularCostoEstimado();
};

#endif // !SOLICITUDENVIO_H



