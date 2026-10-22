#ifndef CLIENTE_H
#define CLIENTE_H
#include <iostream>

using namespace std;

class Cliente 
{
protected:

	string identificacion;
	string nombre;
	string telefono;
	string correo;

public:

	Cliente(string identificacion, string nombre, string telefono, string correo);

	//Gets
	string getIdentificacion();
	string getNombre();
	string getTelefono();
	string getCorreo();

	//Sets
	void setIdentificacion();
	void setNombre();
	void setTelefono();
	void setCorreo();

	//Metodos

	virtual void mostrarInfo();


};

#endif // !CLIENTE_H



