#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>

using namespace std;

class Cliente 
{
protected:

	string identi;
	string nombre;
	string telefono;
	string correo;

public:

	Cliente(string identi, string nombre, string telefono, string correo);

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
	virtual void mostrarInfo() const;

};

#endif // !CLIENTE_H



