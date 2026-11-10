#ifndef EMPRESA_H
#define EMPRESA_H
#include "cliente.h"

class Empresa : public Cliente
{
private:

	//los demas atributo al usar herencia ya los tengo en la clase hija asi ya no los vuelvo a declarar
	string activiEco;
	float descuento;

public:
	Empresa(string identi, string nombre, string telefono, 
		string correo, string activiEco, float descuento);

	//Gets
	string getActiviEco() const;
	float getDescuento() const override;
	string getTipo() const override;

	//Sets
	void setActiviEco(string activiEco);
	void setDescuento(float descuento);

	//metodos
	void mostrarInfo() const override;
};

#endif // !EMPRESA_H



