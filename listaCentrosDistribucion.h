#ifndef LISTACENTROSDISTRIBUCION_H
#define LISTACENTROSDISTRIBUCION_H
#include "nodoCentroDistribucion.h"
#include <iostream>

class ListaCentrosDistribucion
{
private:
	NodoCentroDistribucion* primero;
	NodoCentroDistribucion* actual;

public:
	ListaCentrosDistribucion();
	~ListaCentrosDistribucion();

	void insertarCentro(CentroDistribucion* dato);
	void mostrarCentros() const;
	CentroDistribucion* buscar(string codigo) const;
	bool eliminarCentro(string codigo); // solo si el centro no tiene datos asociados
	bool estaVacia() const;
	NodoCentroDistribucion* getPrimero() const;


	Paquete* buscarPaquete(string codigo) const;
	SolicitudEnvio* buscarSolicitud(string codigo) const;
	Despacho* buscarDespacho(string codigo) const;

};

#endif // !LISTACENTROSDISTRIBUCION_H
