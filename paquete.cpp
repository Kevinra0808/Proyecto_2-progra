#include "paquete.h"
#include <string>

using namespace std;

Paquete::Paquete() {
	codigo = "";
	descripcion = "";
	peso = 0;
	categoria = "";
	clientePrope = nullptr;
	centroDis = "";
	estado = "";
	estadoAntesIncidencia = "";
	bodegaAsignada = "";
	fila = -1;
	columna = -1;
}

Paquete::Paquete(string codigo, string descripcion, float peso, string categoria, Cliente* clientePrope, string centroDis) {
	this->codigo = codigo;
	this->descripcion = descripcion;
	this->peso = peso;
	this->categoria = categoria;
	this->clientePrope = clientePrope;
	this->centroDis = centroDis;
	estado = "Recibido";
	estadoAntesIncidencia = "";
	bodegaAsignada = "";
	fila = -1;
	columna = -1;
}

//Gets
string Paquete::getCodigo() const {
	return codigo;
}

string Paquete::getDescripcion() const {
	return descripcion;
}

float Paquete::getPeso() const {
	return peso;
}

string Paquete::getCategoria() const {
	return categoria;
}

Cliente* Paquete::getClientePrope() const {
	return clientePrope;
}

string Paquete::getCentroDis() const {
	return centroDis;
}

string Paquete::getEstado() const {
	return estado;
}

string Paquete::getEstadoAntesIncidencia() const {
	return estadoAntesIncidencia;
}

string Paquete::getBodegaAsignada() const {
	return bodegaAsignada;
}

int Paquete::getFila() const {
	return fila;
}

int Paquete::getColumna() const {
	return columna;
}

ListaBitacora* Paquete::getBitacora() {
	return &bitacora;
}

//Sets
void Paquete::setDescripcion(string descripcion) {
	this->descripcion = descripcion;
}

void Paquete::setPeso(float peso) {
	this->peso = peso;
}

void Paquete::setCategoria(string categoria) {
	this->categoria = categoria;
}

void Paquete::setCentroDis(string centroDis) {
	this->centroDis = centroDis;
}


bool Paquete::tieneUbicacion() const {
	return bodegaAsignada != "";
}

void Paquete::asignarUbicacion(string codigoBodega, int fila, int columna) {
	bodegaAsignada = codigoBodega;
	this->fila = fila;
	this->columna = columna;
}

void Paquete::liberarUbicacion() {
	bodegaAsignada = "";
	fila = -1;
	columna = -1;
}


bool Paquete::transicionValida(string actual, string nuevo) {
	const int n = 5;
	string nombres[n] = { "Recibido", "Almacenado", "En transito", "Entregado", "Incidencia" };
	int tabla[n][n] = {
		{ 0, 1, 0, 0, 1 },
		{ 0, 0, 1, 0, 1 },
		{ 0, 0, 0, 1, 1 },
		{ 0, 0, 0, 0, 0 },
		{ 0, 1, 1, 0, 0 }
	};

	int i = -1, j = -1;
	for (int k = 0; k < n; k++) {
		if (nombres[k] == actual) i = k;
		if (nombres[k] == nuevo) j = k;
	}
	if (i == -1 || j == -1) {
		return false;
	}
	return tabla[i][j] == 1;
}

string Paquete::normalizarCategoria(string categoria) {
	for (size_t i = 0; i < categoria.length(); i++) {
		categoria[i] = tolower(categoria[i]);
	}

	if (categoria == "general") return "General";
	if (categoria == "fragil") return "Fragil";
	if (categoria == "tecnologia") return "Tecnologia";
	if (categoria == "documentos") return "Documentos";
	return "";
}

bool Paquete::cambiarEstado(string nuevoEstado, Colaborador* responsable, string fecha) {
	if (responsable == nullptr || fecha == "" || !transicionValida(estado, nuevoEstado)) {
		return false;
	}

	if (nuevoEstado == "Incidencia") {
		estadoAntesIncidencia = estado;
	}

	bitacora.insertarBitacora(new Bitacora(estado, nuevoEstado, fecha, responsable));
	estado = nuevoEstado;
	return true;
}

void Paquete::mostrarInfo() const{
	cout << "Codigo: " << codigo << endl;
	cout << "Descripcion: " << descripcion << endl;
	cout << "Peso: " << peso << endl;
	cout << "Categoria: " << categoria << endl;
	cout << "Cliente Propietario: " << clientePrope->getIdentificacion() << " - " << clientePrope->getNombre() << endl;
	cout << "Centro de distribucion: " << centroDis << endl;
	cout << "Estado: " << estado << endl;
	if (tieneUbicacion()) {
		cout << "Ubicacion: bodega " << bodegaAsignada << ", fila " << fila << ", columna " << columna << endl;
	}
	else {
		cout << "Ubicacion: sin asignar" << endl;
	}
}
