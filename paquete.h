#ifndef PAQUETE_H
#define PAQUETE_H
#include <iostream>
#include <string>
#include "cliente.h"
#include "colaborador.h"
#include "listaBitacora.h"

class Paquete
{
private:
	string codigo;
	string descripcion;
	float peso;
	string categoria;
	Cliente* clientePrope;
	string centroDis;
	string estado;

	string estadoAntesIncidencia; 

	string bodegaAsignada;
	int fila;
	int columna;

	ListaBitacora bitacora;

public:
	Paquete();
	Paquete(string codigo, string descripcion, float peso, string categoria, Cliente* clientePrope, string centroDis);

	//Gets
	string getCodigo() const;
	string getDescripcion() const;
	float getPeso() const;
	string getCategoria() const;
	Cliente* getClientePrope() const;
	string getCentroDis() const;
	string getEstado() const;
	string getEstadoAntesIncidencia() const;
	string getBodegaAsignada() const;
	int getFila() const;
	int getColumna() const;
	ListaBitacora* getBitacora();

	//Sets
	void setDescripcion(string descripcion);
	void setPeso(float peso);
	void setCategoria(string categoria);	
	void setCentroDis(string centroDis);

	bool tieneUbicacion() const;
	void asignarUbicacion(string codigoBodega, int fila, int columna);
	void liberarUbicacion();

	//valida la tabla de transiciones y registra el cambio en la bitacora
	bool cambiarEstado(string nuevoEstado, Colaborador* responsable, string fecha);
	static bool transicionValida(string actual, string nuevo);
	static string normalizarCategoria(string categoria); 

	void mostrarInfo() const;

};

#endif // !PAQUETE_H
