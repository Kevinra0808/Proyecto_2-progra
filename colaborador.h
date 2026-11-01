#ifndef COLABORADOR_H
#define COLABORADOR_H
#include <iostream>
#include <string>

using namespace std;

class Colaborador
{
private:

		string identi;
		string nombre;
		string fechaIngreso;
		string puesto;

public:
	Colaborador(string identi, string nombre, string fechaIngreso, string puesto);

	//Gets
	string getIdenti() const;
	string getNombre() const;
	string getFechaIngreso() const;
	string getPuesto() const;

	//Sets
	void setNombre(string nombre);
	void setFechaIngreso(string fechaIngreso);
	void setPuesto(string puesto);

	void mostrarInfo() const;
};


#endif // !COLABORADOR_H



