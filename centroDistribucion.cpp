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

// ================== Busquedas auxiliares ==================
bool CentroDistribucion::perteneceCliente(Cliente* cliente) {
	return cliente != nullptr && listaClientes.buscar(cliente->getIdentificacion()) == cliente;
}

bool CentroDistribucion::perteneceColaborador(Colaborador* colaborador) {
	return colaborador != nullptr && listaColaboradores.buscar(colaborador->getIdenti()) == colaborador;
}

Despacho* CentroDistribucion::buscarDespachoDePaquete(Paquete* paquete) {
	NodoDespacho* aux = listaDespachos.getPrimero();

	while (aux != nullptr)
	{
		if (aux->getDato()->getPaquete() == paquete)
		{
			return aux->getDato();
		}
		aux = aux->getSiguiente();
	}
	return nullptr;
}

SolicitudEnvio* CentroDistribucion::buscarSolicitudPendienteDePaquete(Paquete* paquete) {
	NodoSolicitud* aux = listaSolicitudes.getPrimero();

	while (aux != nullptr)
	{
		if (aux->getDato()->getPaquete() == paquete && aux->getDato()->getEstado() == "Pendiente")
		{
			return aux->getDato();
		}
		aux = aux->getSiguiente();
	}
	return nullptr;
}

SolicitudEnvio* CentroDistribucion::buscarSolicitudAprobadaDePaquete(Paquete* paquete) {
	NodoSolicitud* aux = listaSolicitudes.getPrimero();

	while (aux != nullptr)
	{
		if (aux->getDato()->getPaquete() == paquete && aux->getDato()->getEstado() == "Aprobada")
		{
			return aux->getDato();
		}
		aux = aux->getSiguiente();
	}
	return nullptr;
}

// ================== Almacenamiento de paquetes ==================
Bodega* CentroDistribucion::recomendarBodega(Paquete* paquete) {
	Bodega* mejor = nullptr;
	NodoBodega* aux = listaBodegas.getPrimero();

	while (aux != nullptr)
	{
		Bodega* b = aux->getDato();
		if (b->esCompatible(paquete->getCategoria()) && b->celdasLibres() > 0)
		{
			if (mejor == nullptr || b->porcentajeDisponible() > mejor->porcentajeDisponible())
			{
				mejor = b;
			}
		}
		aux = aux->getSiguiente();
	}
	return mejor;
}

bool CentroDistribucion::hayBodegaCompatibleConEspacio(Paquete* paquete) {
	return recomendarBodega(paquete) != nullptr;
}

bool CentroDistribucion::almacenarPaquete(Paquete* paquete, Bodega* bodega, int fila, int columna, Colaborador* responsable, string fecha, string& error) {
	bool recibido = paquete->getEstado() == "Recibido";
	// Una incidencia ocurrida antes del almacenamiento sigue el mismo procedimiento al resolverse
	bool incidenciaSinCelda = paquete->getEstado() == "Incidencia" && !paquete->tieneUbicacion()
		&& paquete->getEstadoAntesIncidencia() == "Recibido";

	if (!recibido && !incidenciaSinCelda)
	{
		error = "Solo se pueden almacenar paquetes en estado Recibido (o con incidencia previa al almacenamiento).";
		return false;
	}
	if (paquete->getCentroDis() != codigo)
	{
		error = "El paquete no pertenece a este centro de distribucion.";
		return false;
	}
	if (bodega == nullptr || listaBodegas.buscar(bodega->getCodigo()) != bodega)
	{
		error = "La bodega no existe en este centro.";
		return false;
	}
	if (!bodega->esCompatible(paquete->getCategoria()))
	{
		error = "La bodega no es compatible con la categoria del paquete (" + paquete->getCategoria() + ").";
		return false;
	}
	if (!bodega->existeCelda(fila, columna))
	{
		error = "La celda indicada no existe en la bodega.";
		return false;
	}
	if (!bodega->estaLibre(fila, columna))
	{
		error = "La celda indicada esta ocupada.";
		return false;
	}
	if (!perteneceColaborador(responsable))
	{
		error = "El colaborador responsable no pertenece a este centro.";
		return false;
	}
	if (fecha == "")
	{
		error = "La fecha no puede estar vacia.";
		return false;
	}

	bodega->colocarPaquete(paquete, fila, columna);
	paquete->asignarUbicacion(bodega->getCodigo(), fila, columna);

	if (!paquete->cambiarEstado("Almacenado", responsable, fecha))
	{
		// se deshace la asignacion para no dejar el paquete a medias
		bodega->liberarCelda(fila, columna);
		paquete->liberarUbicacion();
		error = "No se pudo cambiar el estado a Almacenado.";
		return false;
	}
	return true;
}

bool CentroDistribucion::reubicarPaquete(Paquete* paquete, Bodega* destino, int fila, int columna, string& error) {
	if (paquete->getEstado() != "Almacenado" || !paquete->tieneUbicacion())
	{
		error = "Solo se pueden reubicar paquetes en estado Almacenado.";
		return false;
	}
	Bodega* origen = listaBodegas.buscar(paquete->getBodegaAsignada());
	if (origen == nullptr)
	{
		error = "No se encontro la bodega actual del paquete.";
		return false;
	}

	// Primero se valida todo el destino; la celda actual no se toca hasta que sea seguro
	if (destino == nullptr || listaBodegas.buscar(destino->getCodigo()) != destino)
	{
		error = "La bodega destino no existe en este centro.";
		return false;
	}
	if (!destino->esCompatible(paquete->getCategoria()))
	{
		error = "La bodega destino no es compatible con la categoria del paquete.";
		return false;
	}
	if (!destino->existeCelda(fila, columna))
	{
		error = "La celda destino no existe.";
		return false;
	}
	if (!destino->estaLibre(fila, columna))
	{
		error = (destino == origen && fila == paquete->getFila() && columna == paquete->getColumna())
			? "El paquete ya se encuentra en esa celda."
			: "La celda destino esta ocupada.";
		return false;
	}

	int filaAnterior = paquete->getFila();
	int columnaAnterior = paquete->getColumna();

	destino->colocarPaquete(paquete, fila, columna);
	origen->liberarCelda(filaAnterior, columnaAnterior);
	paquete->asignarUbicacion(destino->getCodigo(), fila, columna);
	return true;
}

bool CentroDistribucion::registrarIncidencia(Paquete* paquete, Colaborador* responsable, string fecha, string& error) {
	if (!perteneceColaborador(responsable))
	{
		error = "El colaborador responsable no pertenece a este centro.";
		return false;
	}
	if (fecha == "")
	{
		error = "La fecha no puede estar vacia.";
		return false;
	}
	// La celda (si la tiene) permanece asignada; si esta En transito, el despacho sigue En proceso
	if (!paquete->cambiarEstado("Incidencia", responsable, fecha))
	{
		error = "Desde el estado " + paquete->getEstado() + " no se puede registrar una incidencia.";
		return false;
	}
	return true;
}

bool CentroDistribucion::resolverIncidencia(Paquete* paquete, Colaborador* responsable, string fecha, string& error) {
	if (paquete->getEstado() != "Incidencia")
	{
		error = "El paquete no esta en estado Incidencia.";
		return false;
	}
	if (!perteneceColaborador(responsable))
	{
		error = "El colaborador responsable no pertenece a este centro.";
		return false;
	}
	if (fecha == "")
	{
		error = "La fecha no puede estar vacia.";
		return false;
	}

	string anterior = paquete->getEstadoAntesIncidencia();

	if (anterior == "Almacenado")
	{
		// la celda sigue asignada
		return paquete->cambiarEstado("Almacenado", responsable, fecha);
	}
	if (anterior == "En transito")
	{
		Despacho* despacho = buscarDespachoDePaquete(paquete);
		if (despacho == nullptr || despacho->getEstado() != "En proceso")
		{
			error = "El paquete no pertenece a un despacho En proceso.";
			return false;
		}
		return paquete->cambiarEstado("En transito", responsable, fecha);
	}

	// La incidencia ocurrio estando Recibido: no tiene celda y debe almacenarse con el procedimiento normal
	error = "La incidencia ocurrio antes del almacenamiento: use la opcion Almacenar paquete para resolverla.";
	return false;
}

// ================== Solicitudes y despachos ==================
SolicitudEnvio* CentroDistribucion::crearSolicitud(string codigoSolicitud, Cliente* cliente, Paquete* paquete, Colaborador* responsable, string destino, string fecha, string& error) {
	if (codigoSolicitud == "" || destino == "" || fecha == "")
	{
		error = "El codigo, el destino y la fecha no pueden estar vacios.";
		return nullptr;
	}
	if (paquete == nullptr || listaPaquetes.buscar(paquete->getCodigo()) != paquete)
	{
		error = "El paquete no existe en este centro.";
		return nullptr;
	}
	if (paquete->getEstado() != "Almacenado")
	{
		error = "Solo se puede crear una solicitud para un paquete Almacenado.";
		return nullptr;
	}
	if (!perteneceCliente(cliente) || paquete->getClientePrope() != cliente)
	{
		error = "El cliente debe ser el propietario del paquete y pertenecer a este centro.";
		return nullptr;
	}
	if (!perteneceColaborador(responsable))
	{
		error = "El colaborador responsable no pertenece a este centro.";
		return nullptr;
	}
	if (buscarSolicitudPendienteDePaquete(paquete) != nullptr)
	{
		error = "El paquete ya tiene una solicitud Pendiente.";
		return nullptr;
	}
	if (buscarSolicitudAprobadaDePaquete(paquete) != nullptr || buscarDespachoDePaquete(paquete) != nullptr)
	{
		error = "El paquete ya tiene una solicitud Aprobada y un despacho asociado.";
		return nullptr;
	}

	SolicitudEnvio* nueva = new SolicitudEnvio(codigoSolicitud, cliente, paquete, responsable, codigo, destino, fecha);
	listaSolicitudes.insertarSolicitud(nueva);
	return nueva;
}

Despacho* CentroDistribucion::aprobarSolicitud(SolicitudEnvio* solicitud, string codigoDespacho, string fecha, string hora, string& error) {
	if (solicitud == nullptr || listaSolicitudes.buscar(solicitud->getCodigo()) != solicitud)
	{
		error = "La solicitud no existe en este centro.";
		return nullptr;
	}
	if (codigoDespacho == "" || fecha == "" || hora == "")
	{
		error = "El codigo, la fecha y la hora del despacho no pueden estar vacios.";
		return nullptr;
	}
	if (solicitud->getEstado() != "Pendiente")
	{
		error = "Solo se puede aprobar una solicitud Pendiente.";
		return nullptr;
	}

	Paquete* paquete = solicitud->getPaquete();

	if (paquete->getEstado() != "Almacenado")
	{
		error = (paquete->getEstado() == "Incidencia")
			? "El paquete tiene una incidencia: no se puede aprobar la solicitud."
			: "El paquete debe estar Almacenado para aprobar la solicitud.";
		return nullptr;
	}
	if (buscarDespachoDePaquete(paquete) != nullptr)
	{
		error = "Ya existe un despacho asociado a ese paquete.";
		return nullptr;
	}
	if (!perteneceColaborador(solicitud->getResponsable()))
	{
		error = "El colaborador de la solicitud no pertenece a este centro.";
		return nullptr;
	}

	// El paquete pasa a En transito y libera inmediatamente su celda
	string codigoBodega = paquete->getBodegaAsignada();
	int fila = paquete->getFila();
	int columna = paquete->getColumna();

	if (!paquete->cambiarEstado("En transito", solicitud->getResponsable(), fecha))
	{
		error = "No se pudo cambiar el estado del paquete a En transito.";
		return nullptr;
	}

	Bodega* bodega = listaBodegas.buscar(codigoBodega);
	if (bodega != nullptr)
	{
		bodega->liberarCelda(fila, columna);
	}
	paquete->liberarUbicacion();

	solicitud->cambiarEstado("Aprobada");

	Despacho* despacho = new Despacho(codigoDespacho, solicitud, paquete, solicitud->getSoliCliente(),
		solicitud->getResponsable(), solicitud->getCentroOrigen(), solicitud->getDestinoEntrega(), fecha, hora);
	listaDespachos.insertarDespacho(despacho);
	return despacho;
}

bool CentroDistribucion::finalizarDespacho(Despacho* despacho, string fecha, string& error) {
	if (despacho == nullptr || listaDespachos.buscar(despacho->getCodigo()) != despacho)
	{
		error = "El despacho no existe en este centro.";
		return false;
	}
	if (fecha == "")
	{
		error = "La fecha no puede estar vacia.";
		return false;
	}
	if (despacho->getEstado() != "En proceso")
	{
		error = "El despacho no esta En proceso.";
		return false;
	}
	if (despacho->getPaquete()->getEstado() == "Incidencia")
	{
		error = "El paquete tiene una incidencia pendiente: resuelvala antes de finalizar la entrega.";
		return false;
	}
	if (!despacho->finalizarEntrega(fecha))
	{
		error = "El paquete debe estar En transito para finalizar la entrega.";
		return false;
	}
	return true;
}

// ================== Eliminaciones ==================
bool CentroDistribucion::eliminarCliente(string identificacion, string& error) {
	Cliente* cliente = listaClientes.buscar(identificacion);

	if (cliente == nullptr)
	{
		error = "El cliente no existe.";
		return false;
	}

	NodoPaquete* p = listaPaquetes.getPrimero();
	while (p != nullptr)
	{
		if (p->getDato()->getClientePrope() == cliente)
		{
			error = "El cliente tiene paquetes asociados.";
			return false;
		}
		p = p->getSiguiente();
	}

	NodoSolicitud* s = listaSolicitudes.getPrimero();
	while (s != nullptr)
	{
		if (s->getDato()->getSoliCliente() == cliente)
		{
			error = "El cliente tiene solicitudes asociadas.";
			return false;
		}
		s = s->getSiguiente();
	}

	NodoDespacho* d = listaDespachos.getPrimero();
	while (d != nullptr)
	{
		if (d->getDato()->getCliente() == cliente)
		{
			error = "El cliente tiene despachos asociados.";
			return false;
		}
		d = d->getSiguiente();
	}

	return listaClientes.eliminar(identificacion);
}

bool CentroDistribucion::eliminarColaborador(string identificacion, string& error) {
	Colaborador* colaborador = listaColaboradores.buscar(identificacion);

	if (colaborador == nullptr)
	{
		error = "El colaborador no existe.";
		return false;
	}

	NodoSolicitud* s = listaSolicitudes.getPrimero();
	while (s != nullptr)
	{
		if (s->getDato()->getResponsable() == colaborador)
		{
			error = "El colaborador es responsable en solicitudes.";
			return false;
		}
		s = s->getSiguiente();
	}

	NodoDespacho* d = listaDespachos.getPrimero();
	while (d != nullptr)
	{
		if (d->getDato()->getResponsable() == colaborador)
		{
			error = "El colaborador es responsable en despachos.";
			return false;
		}
		d = d->getSiguiente();
	}

	NodoPaquete* p = listaPaquetes.getPrimero();
	while (p != nullptr)
	{
		if (p->getDato()->getBitacora()->contieneResponsable(colaborador))
		{
			error = "El colaborador aparece como responsable en la bitacora de un paquete.";
			return false;
		}
		p = p->getSiguiente();
	}

	return listaColaboradores.eliminar(identificacion);
}

bool CentroDistribucion::eliminarPaquete(string codigoPaquete, string& error) {
	Paquete* paquete = listaPaquetes.buscar(codigoPaquete);

	if (paquete == nullptr)
	{
		error = "El paquete no existe.";
		return false;
	}
	if (paquete->getEstado() != "Recibido" || paquete->tieneUbicacion())
	{
		error = "Solo se puede eliminar un paquete en estado Recibido y sin celda asignada.";
		return false;
	}

	NodoSolicitud* s = listaSolicitudes.getPrimero();
	while (s != nullptr)
	{
		if (s->getDato()->getPaquete() == paquete)
		{
			error = "El paquete tiene solicitudes asociadas.";
			return false;
		}
		s = s->getSiguiente();
	}

	if (buscarDespachoDePaquete(paquete) != nullptr)
	{
		error = "El paquete tiene un despacho asociado.";
		return false;
	}

	return listaPaquetes.eliminar(codigoPaquete);
}

bool CentroDistribucion::eliminarBodega(string codigoBodega, string& error) {
	Bodega* bodega = listaBodegas.buscar(codigoBodega);

	if (bodega == nullptr)
	{
		error = "La bodega no existe.";
		return false;
	}

	NodoPaquete* p = listaPaquetes.getPrimero();
	while (p != nullptr)
	{
		if (p->getDato()->getBodegaAsignada() == codigoBodega)
		{
			error = "Hay paquetes con celdas asignadas en esta bodega.";
			return false;
		}
		p = p->getSiguiente();
	}

	if (!bodega->estaVacia())
	{
		error = "La bodega tiene celdas ocupadas.";
		return false;
	}

	return listaBodegas.eliminarBodega(codigoBodega);
}

// ================== Reportes ==================
void CentroDistribucion::reporteHistorialCliente(Cliente* cliente) {
	cout << "\n=== HISTORIAL DEL CLIENTE " << cliente->getIdentificacion() << " - " << cliente->getNombre() << " ===" << endl;

	cout << "\n-- Solicitudes --" << endl;
	bool hay = false;
	NodoSolicitud* s = listaSolicitudes.getPrimero();
	while (s != nullptr)
	{
		SolicitudEnvio* sol = s->getDato();
		if (sol->getSoliCliente() == cliente)
		{
			cout << "Solicitud " << sol->getCodigo() << " | Paquete: " << sol->getPaquete()->getCodigo()
				<< " | Fecha: " << sol->getFechaSoli() << " | Estado: " << sol->getEstado() << endl;
			hay = true;
		}
		s = s->getSiguiente();
	}
	if (!hay) cout << "El cliente no tiene solicitudes." << endl;

	cout << "\n-- Despachos --" << endl;
	hay = false;
	NodoDespacho* d = listaDespachos.getPrimero();
	while (d != nullptr)
	{
		Despacho* desp = d->getDato();
		if (desp->getCliente() == cliente)
		{
			cout << "Despacho " << desp->getCodigo() << " | Paquete: " << desp->getPaquete()->getCodigo()
				<< " | Fecha: " << desp->getFechaDespacho() << " | Estado: " << desp->getEstado() << endl;
			hay = true;
		}
		d = d->getSiguiente();
	}
	if (!hay) cout << "El cliente no tiene despachos." << endl;
}

void CentroDistribucion::reporteClientesPorEnvios() {
	// Se cuentan los clientes y se guardan en arreglos dinamicos (sin contenedores de la STL)
	int n = 0;
	NodoCliente* c = listaClientes.getPrimero();
	while (c != nullptr)
	{
		n++;
		c = c->getSiguiente();
	}

	cout << "\n=== CLIENTES POR CANTIDAD DE ENVIOS FINALIZADOS (" << nombre << ") ===" << endl;
	if (n == 0)
	{
		cout << "El centro no tiene clientes." << endl;
		return;
	}

	Cliente** clientes = new Cliente*[n];
	int* envios = new int[n];

	int i = 0;
	c = listaClientes.getPrimero();
	while (c != nullptr)
	{
		clientes[i] = c->getCliente();
		envios[i] = 0;

		NodoDespacho* d = listaDespachos.getPrimero();
		while (d != nullptr)
		{
			if (d->getDato()->getCliente() == clientes[i] && d->getDato()->getEstado() == "Finalizado")
			{
				envios[i]++;
			}
			d = d->getSiguiente();
		}
		i++;
		c = c->getSiguiente();
	}

	// Ordenamiento por insercion (estable): en caso de empate se conserva el orden de la lista
	for (int j = 1; j < n; j++)
	{
		Cliente* clienteActual = clientes[j];
		int enviosActual = envios[j];
		int k = j - 1;

		while (k >= 0 && envios[k] < enviosActual)
		{
			clientes[k + 1] = clientes[k];
			envios[k + 1] = envios[k];
			k--;
		}
		clientes[k + 1] = clienteActual;
		envios[k + 1] = enviosActual;
	}

	for (int j = 0; j < n; j++)
	{
		cout << (j + 1) << ". " << clientes[j]->getIdentificacion() << " - " << clientes[j]->getNombre()
			<< " | Despachos finalizados: " << envios[j] << endl;
	}

	delete[] clientes;
	delete[] envios;
}

void CentroDistribucion::reporteDespachoDePaquete(Paquete* paquete) {
	cout << "\n=== DESPACHO DEL PAQUETE " << paquete->getCodigo() << " ===" << endl;

	SolicitudEnvio* solicitud = buscarSolicitudAprobadaDePaquete(paquete);
	Despacho* despacho = buscarDespachoDePaquete(paquete);

	if (despacho == nullptr)
	{
		cout << "El paquete no posee despacho." << endl;
		return;
	}

	if (solicitud != nullptr)
	{
		cout << "Solicitud aprobada: " << solicitud->getCodigo() << " | Fecha: " << solicitud->getFechaSoli()
			<< " | Estado: " << solicitud->getEstado() << endl;
	}
	cout << "Despacho: " << despacho->getCodigo() << " | Fecha: " << despacho->getFechaDespacho()
		<< " | Estado: " << despacho->getEstado() << endl;
}

void CentroDistribucion::reporteOcupacionBodegas() {
	cout << "\n=== OCUPACION DE BODEGAS: " << codigo << " - " << nombre << " ===" << endl;

	NodoBodega* b = listaBodegas.getPrimero();
	if (b == nullptr)
	{
		cout << "El centro no tiene bodegas." << endl;
		return;
	}

	while (b != nullptr)
	{
		Bodega* bodega = b->getDato();
		cout << "Bodega " << bodega->getCodigo() << " (" << bodega->getNombre() << ")"
			<< " | Total: " << bodega->totalCeldas()
			<< " | Ocupadas: " << bodega->celdasOcupadas()
			<< " | Disponibles: " << bodega->celdasLibres()
			<< " | Ocupacion: " << bodega->porcentajeOcupacion() << "%" << endl;
		b = b->getSiguiente();
	}
}

void CentroDistribucion::reporteDespachosPorColaborador(Colaborador* colaborador) {
	cout << "\n=== DESPACHOS GESTIONADOS POR " << colaborador->getIdenti() << " - " << colaborador->getNombre() << " ===" << endl;

	bool hay = false;
	NodoDespacho* d = listaDespachos.getPrimero();
	while (d != nullptr)
	{
		Despacho* desp = d->getDato();
		if (desp->getResponsable() == colaborador)
		{
			cout << "Despacho " << desp->getCodigo() << " | Paquete: " << desp->getPaquete()->getCodigo()
				<< " | Fecha: " << desp->getFechaDespacho() << " | Estado: " << desp->getEstado() << endl;
			hay = true;
		}
		d = d->getSiguiente();
	}
	if (!hay) cout << "El colaborador no ha gestionado despachos." << endl;
}
