#ifndef BODEGA_H
#define BODEGA_H

#include "paquete.h"
#include <iostream>
#include <string>

using namespace std;

class Bodega {
private:
	string codigo;
	string nombre;
	int tipo;
	int filas, columnas;

	Paquete*** matriz; 

public:
	Bodega(string codigo, string nombre, int tipo, int filas, int columnas);
	~Bodega();

	// Gets
	string getCodigo() const;
	string getNombre() const;
	int getTipo() const;
	int getFilas() const;
	int getColumnas() const;

	// Tipos de bodega
	static bool tipoValido(int tipo);
	static string nombreTipo(int tipo);
	string getNombreTipo() const;
	bool esCompatible(string categoria) const; 

	// Celdas
	bool existeCelda(int fila, int columna) const;
	bool estaLibre(int fila, int columna) const;
	string codigoCelda(int fila, int columna) const; 
	bool colocarPaquete(Paquete* paquete, int fila, int columna);
	bool liberarCelda(int fila, int columna);
	Paquete* obtenerPaquete(int fila, int columna) const;
	bool primeraCeldaLibre(int& fila, int& columna) const;

	// Ocupacion
	int totalCeldas() const;
	int celdasOcupadas() const;
	int celdasLibres() const;
	float porcentajeOcupacion() const;
	float porcentajeDisponible() const;
	bool estaVacia() const;

	// Vistas en consola
	void mostrarResumen() const;
	void mostrarBodega() const;      
	void mostrarCeldasLibres() const; 
};

#endif // !BODEGA_H
