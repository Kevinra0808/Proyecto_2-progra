#ifndef PAQUETE_H
#define PAQUETE_H
#include <iostream>
#include "cliente.h"

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

	//Sets
	void setDescripcion(string descripcion);
	void setPeso(float peso);
	void setCategoria(string categoria);	
	void setCentroDis(string centroDis);
	void setEstado(string nuevoEstado);

	void mostrarInfo() const;

};

#endif // !PAQUETE_H



