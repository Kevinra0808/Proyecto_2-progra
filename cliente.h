#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>
#include <string>

using namespace std;

// Clase base abstracta: los dos tipos de cliente (PersonaFisica y Empresa) heredan de ella
class Cliente
{
protected:

	string identi;
	string nombre;
	string telefono;
	string correo;

public:

	Cliente(string identi, string nombre, string telefono, string correo);
	virtual ~Cliente();

	//Gets
	string getIdentificacion() const;
	string getNombre() const;
	string getTelefono() const;
	string getCorreo() const;

	//Sets
	void setNombre(string nombre);
	void setTelefono(string telefono);
	void setCorreo(string correo);

	//Metodos
	virtual string getTipo() const = 0;
	virtual float getDescuento() const; // las personas fisicas no tienen descuento
	virtual void mostrarInfo() const;

};

class PersonaFisica : public Cliente
{
public:
	PersonaFisica(string identi, string nombre, string telefono, string correo);

	string getTipo() const override;
	void mostrarInfo() const override;
};

#endif // !CLIENTE_H
