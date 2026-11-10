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


	bool perteneceCliente(Cliente* cliente);
	bool perteneceColaborador(Colaborador* colaborador);
	Despacho* buscarDespachoDePaquete(Paquete* paquete);
	SolicitudEnvio* buscarSolicitudPendienteDePaquete(Paquete* paquete);
	SolicitudEnvio* buscarSolicitudAprobadaDePaquete(Paquete* paquete);

	
	Bodega* recomendarBodega(Paquete* paquete);
	bool hayBodegaCompatibleConEspacio(Paquete* paquete);
	bool almacenarPaquete(Paquete* paquete, Bodega* bodega, int fila, int columna, Colaborador* responsable, string fecha, string& error);
	bool reubicarPaquete(Paquete* paquete, Bodega* destino, int fila, int columna, string& error);
	bool registrarIncidencia(Paquete* paquete, Colaborador* responsable, string fecha, string& error);
	bool resolverIncidencia(Paquete* paquete, Colaborador* responsable, string fecha, string& error);

	
	SolicitudEnvio* crearSolicitud(string codigo, Cliente* cliente, Paquete* paquete, Colaborador* responsable, string destino, string fecha, string& error);
	Despacho* aprobarSolicitud(SolicitudEnvio* solicitud, string codigoDespacho, string fecha, string hora, string& error);
	bool finalizarDespacho(Despacho* despacho, string fecha, string& error);

	
	bool eliminarCliente(string identificacion, string& error);
	bool eliminarColaborador(string identificacion, string& error);
	bool eliminarPaquete(string codigo, string& error);
	bool eliminarBodega(string codigo, string& error);

	
	void reporteHistorialCliente(Cliente* cliente);
	void reporteClientesPorEnvios();
	void reporteDespachoDePaquete(Paquete* paquete);
	void reporteOcupacionBodegas();
	void reporteDespachosPorColaborador(Colaborador* colaborador);
};

#endif // !CENTRODISTRIBUCION_H


