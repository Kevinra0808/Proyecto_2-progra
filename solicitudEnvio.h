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

	// Tarifas por kilogramo: datos compartidos de la aplicacion (no se escriben dentro de cada calculo)
	static const double TARIFA_GENERAL;
	static const double TARIFA_FRAGIL;
	static const double TARIFA_TECNOLOGIA;
	static const double TARIFA_DOCUMENTOS;

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

	// Pendiente -> Aprobada / Rechazada / Anulada. Estos tres estados son finales.
	bool cambiarEstado(string nuevoEstado);

	void mostrarSolicitud() const;
	static double getTarifa(string categoria); // -1 si la categoria no es valida
	double calcularCostoBase(float peso, string categoria) const;
	void calcularCostoEstimado();
};

#endif // !SOLICITUDENVIO_H



