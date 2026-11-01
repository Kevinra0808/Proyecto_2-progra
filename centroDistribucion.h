#ifndef CENTRODISTRIBUCION_H
#define CENTRODISTRIBUCION_H
#include <iostream>
#include "listaClientes.h"
#include "listaColaboradores.h"
#include "listaBodegas.h"
#include "listaPaquetes.h"
#include "listaSolicitudes.h"
#include "listaDespachos.h"
#include "listaBitacora.h"

using namespace std;

class CentroDistribucion
{
private:
	string codigo;
	string nombre;
	string provincia;
	string direccionDescriptiva;
	string telefono;

	ListaBodegas listaBodegas;
	ListaSolicitudes listaSolicitudes;
	ListaDespachos listaDespachos;
	ListaPaquetes listaPaquetes;
	ListaCliente listaClientes;
	ListaColaboradores listaColaboradores;

public:

	CentroDistribucion(string codigo, string nombre, string provincia, string direccionDescriptiva, string telefono);

	//Gets
	string getCodigo();
	string getNombre();
	string getProvincia();
	string getDireccionDescriptiva();
	string getTelefono();

	//Gets listas
	ListaBodegas* getListaBodegas();
	ListaSolicitudes* getListaSolicitudes();
	ListaDespachos* getListaDespachos();
	ListaPaquetes* getListaPaquetes();
	ListaCliente* getListaClientes();
	ListaColaboradores* getListaColaboradores();

	void mostrarCentro() const;
	bool estaVacio() const;
};

#endif // !CENTRODISTRIBUCION_H


