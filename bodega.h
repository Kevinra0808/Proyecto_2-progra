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

	// Metodos
	void mostrarBodega() const;
	bool colocarPaquete(Paquete* paquete, int fila, int columna);
	Paquete* obtenerPaquete(int fila, int columna) const;
	float porcentajeOcupacion() const;
	float porcentajeDisponible() const;
	bool estaVacia() const;
};

#endif // !BODEGA_H