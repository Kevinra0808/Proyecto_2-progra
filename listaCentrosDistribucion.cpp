#include "listaCentrosDistribucion.h"
#include <string>

using namespace std;

ListaCentrosDistribucion::ListaCentrosDistribucion() {
	primero = nullptr;
	actual = nullptr;
}

ListaCentrosDistribucion::~ListaCentrosDistribucion() {
	while (primero != nullptr)
	{
		NodoCentroDistribucion* borrar = primero;
		primero = primero->getSiguiente();
		delete borrar->getDato();
		delete borrar;
	}
}

void ListaCentrosDistribucion::insertarCentro(CentroDistribucion* nuevoCentro) {
	NodoCentroDistribucion* nuevo = new NodoCentroDistribucion(nuevoCentro);
	if (primero == nullptr)
	{
		primero = nuevo;
	}
	else
	{
		NodoCentroDistribucion* aux = primero;
		while (aux->getSiguiente() != nullptr)
		{
			aux = aux->getSiguiente();
		}
		aux->setSiguiente(nuevo);
	}
}

void ListaCentrosDistribucion::mostrarCentros() const {
	NodoCentroDistribucion* aux = primero;

	if (aux == nullptr)
	{
		cout << "No hay centros de distribucion registrados." << endl;
	}

	while (aux != nullptr)
	{
		aux->getDato()->mostrarCentro();
		cout << endl;

		aux = aux->getSiguiente();
	}
}

CentroDistribucion* ListaCentrosDistribucion::buscar(string codigo) const {
	NodoCentroDistribucion* aux = primero;

	while (aux != nullptr)
	{
		if (aux->getDato()->getCodigo() == codigo)
		{
			return aux->getDato();
		}
		else
		{
			aux = aux->getSiguiente();
		}
	}
	return nullptr;
}

bool ListaCentrosDistribucion::eliminarCentro(string codigo) {
	NodoCentroDistribucion* aux = primero;
	NodoCentroDistribucion* anterior = nullptr;

	while (aux != nullptr)
	{
		if (aux->getDato()->getCodigo() == codigo)
		{
			if (!aux->getDato()->estaVacio()) {	
				return false;
			}

			if (anterior == nullptr)
			{
				primero = aux->getSiguiente();
			}
			else
			{
				anterior->setSiguiente(aux->getSiguiente());
			}

			delete aux->getDato();
			delete aux;
			
			return true;
		}
		anterior = aux;
		aux = aux->getSiguiente();
	}
	return false;
}

bool ListaCentrosDistribucion::estaVacia() const {
	return primero == nullptr;
}

NodoCentroDistribucion* ListaCentrosDistribucion::getPrimero() const {
	return primero;
}

Paquete* ListaCentrosDistribucion::buscarPaquete(string codigo) const {
	NodoCentroDistribucion* aux = primero;

	while (aux != nullptr)
	{
		Paquete* encontrado = aux->getDato()->getListaPaquetes()->buscar(codigo);
		if (encontrado != nullptr)
		{
			return encontrado;
		}
		aux = aux->getSiguiente();
	}
	return nullptr;
}

SolicitudEnvio* ListaCentrosDistribucion::buscarSolicitud(string codigo) const {
	NodoCentroDistribucion* aux = primero;

	while (aux != nullptr)
	{
		SolicitudEnvio* encontrada = aux->getDato()->getListaSolicitudes()->buscar(codigo);
		if (encontrada != nullptr)
		{
			return encontrada;
		}
		aux = aux->getSiguiente();
	}
	return nullptr;
}

Despacho* ListaCentrosDistribucion::buscarDespacho(string codigo) const {
	NodoCentroDistribucion* aux = primero;

	while (aux != nullptr)
	{
		Despacho* encontrado = aux->getDato()->getListaDespachos()->buscar(codigo);
		if (encontrado != nullptr)
		{
			return encontrado;
		}
		aux = aux->getSiguiente();
	}
	return nullptr;
}
