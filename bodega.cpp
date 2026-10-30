#include "bodega.h"

using namespace std;

Bodega::Bodega(string codigo, string nombre, int tipo, int filas, int columnas) {
	this->codigo = codigo;
	this->nombre = nombre;
	this->tipo = tipo;
	this->filas = filas;
	this->columnas = columnas;

	matriz = new Paquete** [filas];
	for (int i = 0; i < filas; i++) {
		matriz[i] = new Paquete* [columnas]; 

		for (int j = 0; j < columnas; j++) {
			matriz[i][j] = nullptr;
		}
	}
}

Bodega::~Bodega() {
	for (int i = 0; i < filas; i++) {
		delete[] matriz[i];
	}

	delete[] matriz;
	matriz = nullptr;
}

// Gets
string Bodega::getCodigo() const {
	return codigo;
}

string Bodega::getNombre() const {
	return nombre;
}

int Bodega::getTipo() const {
	return tipo;
}

int Bodega::getFilas() const {
	return filas;
}

int Bodega::getColumnas() const {
	return columnas;
}

void Bodega::mostrarBodega() const {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (matriz[i][j] == nullptr) {
				cout << "LIBRE ";
			}
			else {
				cout << matriz[i][j]->getCodigo() << " ";
			}
		}
		cout << endl;
	}
}

bool Bodega::colocarPaquete(Paquete* paquete, int fila, int columna) {
	if (paquete == nullptr || fila < 0 || fila >= filas || columna < 0 || columna >= columnas || matriz[fila][columna] != nullptr) {
		return false;
	}
	matriz[fila][columna] = paquete;
	return true;
}

Paquete* Bodega::obtenerPaquete(int fila, int columna) const {
	if (fila < 0 || fila >= filas || columna < 0 || columna >= columnas || matriz[fila][columna] == nullptr) {
		return nullptr;
	}

	
	return matriz[fila][columna];
}

float Bodega::porcentajeOcupacion() const {
	int paquetesColocados = 0;
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			if (matriz[i][j] != nullptr)
			{
				paquetesColocados++;
			}
		}
	}
	return (paquetesColocados * 100.0) / (filas * columnas);
}

float Bodega::porcentajeDisponible() const {
	int paquetesNoColocados = 0;
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			if (matriz[i][j] == nullptr)
			{
				paquetesNoColocados++;
			}
		}
	}
	
	return (paquetesNoColocados * 100.0) / (filas * columnas);
}

bool Bodega::estaVacia() const {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (matriz[i][j] != nullptr) {
				return false;
			}
		}
	}
	return true;
}