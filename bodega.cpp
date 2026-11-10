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

// Tipos de bodega
bool Bodega::tipoValido(int tipo) {
	return tipo >= 1 && tipo <= 4;
}

string Bodega::nombreTipo(int tipo) {
	switch (tipo) {
	case 1: return "General";
	case 2: return "Fragil";
	case 3: return "Tecnologia";
	case 4: return "Documentos";
	}
	return "Desconocido";
}

string Bodega::getNombreTipo() const {
	return nombreTipo(tipo);
}

bool Bodega::esCompatible(string categoria) const {
	return categoria == getNombreTipo();
}

// Celdas
bool Bodega::existeCelda(int fila, int columna) const {
	return fila >= 0 && fila < filas && columna >= 0 && columna < columnas;
}

bool Bodega::estaLibre(int fila, int columna) const {
	return existeCelda(fila, columna) && matriz[fila][columna] == nullptr;
}

string Bodega::codigoCelda(int fila, int columna) const {
	// Con indices de un digito: A-12. Con dos o mas digitos se usa un punto: A-12.03
	if (filas <= 10 && columnas <= 10) {
		return codigo + "-" + to_string(fila) + to_string(columna);
	}
	string f = to_string(fila);
	string c = to_string(columna);
	if (f.length() < 2) f = "0" + f;
	if (c.length() < 2) c = "0" + c;
	return codigo + "-" + f + "." + c;
}

bool Bodega::colocarPaquete(Paquete* paquete, int fila, int columna) {
	if (paquete == nullptr || !estaLibre(fila, columna)) {
		return false;
	}
	matriz[fila][columna] = paquete;
	return true;
}

bool Bodega::liberarCelda(int fila, int columna) {
	if (!existeCelda(fila, columna) || matriz[fila][columna] == nullptr) {
		return false;
	}
	matriz[fila][columna] = nullptr;
	return true;
}

Paquete* Bodega::obtenerPaquete(int fila, int columna) const {
	if (!existeCelda(fila, columna)) {
		return nullptr;
	}
	return matriz[fila][columna];
}

bool Bodega::primeraCeldaLibre(int& fila, int& columna) const {
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (matriz[i][j] == nullptr) {
				fila = i;
				columna = j;
				return true;
			}
		}
	}
	return false;
}

// Ocupacion
int Bodega::totalCeldas() const {
	return filas * columnas;
}

int Bodega::celdasOcupadas() const {
	int ocupadas = 0;
	for (int i = 0; i < filas; i++)
	{
		for (int j = 0; j < columnas; j++)
		{
			if (matriz[i][j] != nullptr)
			{
				ocupadas++;
			}
		}
	}
	return ocupadas;
}

int Bodega::celdasLibres() const {
	return totalCeldas() - celdasOcupadas();
}

float Bodega::porcentajeOcupacion() const {
	return (celdasOcupadas() * 100.0f) / totalCeldas();
}

float Bodega::porcentajeDisponible() const {
	return (celdasLibres() * 100.0f) / totalCeldas();
}

bool Bodega::estaVacia() const {
	return celdasOcupadas() == 0;
}

// Vistas en consola
void Bodega::mostrarResumen() const {
	cout << "Codigo: " << codigo << endl;
	cout << "Nombre: " << nombre << endl;
	cout << "Tipo: " << tipo << " - " << getNombreTipo() << endl;
	cout << "Distribucion: " << filas << " filas x " << columnas << " columnas" << endl;
	cout << "Celdas ocupadas: " << celdasOcupadas() << " de " << totalCeldas() << endl;
}

void Bodega::mostrarBodega() const {
	// Ancho de cada celda segun el texto mas largo que se va a mostrar
	size_t ancho = 5; // "LIBRE"
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			size_t largo = codigoCelda(i, j).length();
			if (largo > ancho) ancho = largo;
			if (matriz[i][j] != nullptr && matriz[i][j]->getCodigo().length() > ancho) {
				ancho = matriz[i][j]->getCodigo().length();
			}
		}
	}

	cout << "Bodega " << codigo << " - " << nombre << " (" << getNombreTipo() << ")" << endl;
	cout << "[ ] = libre   [X] = ocupada" << endl;

	string linea = "+";
	for (int j = 0; j < columnas; j++) {
		linea += string(ancho + 2, '-') + "+";
	}

	for (int i = 0; i < filas; i++) {
		cout << linea << endl;

		// primera linea: codigo de celda
		cout << "|";
		for (int j = 0; j < columnas; j++) {
			string texto = codigoCelda(i, j);
			cout << " " << texto << string(ancho - texto.length(), ' ') << " |";
		}
		cout << endl;

		// segunda linea: LIBRE o codigo del paquete
		cout << "|";
		for (int j = 0; j < columnas; j++) {
			string texto = (matriz[i][j] == nullptr) ? "LIBRE" : matriz[i][j]->getCodigo();
			cout << " " << texto << string(ancho - texto.length(), ' ') << " |";
		}
		cout << endl;
	}
	cout << linea << endl;
	cout << "Ocupacion: " << celdasOcupadas() << "/" << totalCeldas() << " celdas ("
		<< porcentajeOcupacion() << "%)" << endl;
}

void Bodega::mostrarCeldasLibres() const {
	bool hay = false;
	for (int i = 0; i < filas; i++) {
		for (int j = 0; j < columnas; j++) {
			if (matriz[i][j] == nullptr) {
				cout << codigoCelda(i, j) << "  ";
				hay = true;
			}
		}
	}
	if (!hay) {
		cout << "(sin celdas disponibles)";
	}
	cout << endl;
}
