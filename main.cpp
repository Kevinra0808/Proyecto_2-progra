#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include "bitacora.h"
#include "bodega.h"
#include "cliente.h"
#include "colaborador.h"
#include "despacho.h"
#include "empresa.h"
#include "paquete.h"
#include "centroDistribucion.h"
#include "solicitudEnvio.h"
#include "listaBitacora.h"
#include "listaCentrosDistribucion.h"

using namespace std;

// =====================================================================
//  Lectura y validacion de datos (el programa nunca debe terminar
//  abruptamente por una entrada invalida)
// =====================================================================

static string leerLinea(const string& mensaje)
{
	string texto;
	while (true)
	{
		cout << mensaje;
		getline(cin, texto);
		if (cin.eof())
		{
			cout << "\nFin de la entrada. Saliendo del sistema...\n";
			exit(0);
		}
		// se eliminan los espacios al inicio y al final
		size_t inicio = texto.find_first_not_of(" \t\r");
		if (inicio != string::npos)
		{
			size_t fin = texto.find_last_not_of(" \t\r");
			return texto.substr(inicio, fin - inicio + 1);
		}
		cout << "Este dato no puede quedar vacio.\n";
	}
}

static int leerEntero(const string& mensaje, int minimo, int maximo)
{
	while (true)
	{
		string texto = leerLinea(mensaje);
		char* fin = nullptr;
		long valor = strtol(texto.c_str(), &fin, 10);
		if (*fin == '\0' && valor >= minimo && valor <= maximo)
		{
			return (int)valor;
		}
		cout << "Ingrese un numero entero entre " << minimo << " y " << maximo << ".\n";
	}
}

static double leerDecimal(const string& mensaje, double minimo, double maximo, bool incluyeMinimo)
{
	while (true)
	{
		string texto = leerLinea(mensaje);
		for (size_t i = 0; i < texto.length(); i++)
		{
			if (texto[i] == ',') texto[i] = '.';
		}
		char* fin = nullptr;
		double valor = strtod(texto.c_str(), &fin);
		bool enRango = (incluyeMinimo ? valor >= minimo : valor > minimo) && valor <= maximo;
		if (*fin == '\0' && enRango)
		{
			return valor;
		}
		cout << "Ingrese un numero " << (incluyeMinimo ? "mayor o igual a " : "mayor que ") << minimo
			<< " y menor o igual a " << maximo << ".\n";
	}
}

static bool fechaValida(const string& f)
{
	if (f.length() != 10 || f[2] != '/' || f[5] != '/')
	{
		return false;
	}
	for (int i = 0; i < 10; i++)
	{
		if (i != 2 && i != 5 && !isdigit((unsigned char)f[i]))
		{
			return false;
		}
	}
	int dia = atoi(f.substr(0, 2).c_str());
	int mes = atoi(f.substr(3, 2).c_str());
	int anio = atoi(f.substr(6, 4).c_str());
	int diasMes[12] = { 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
	return mes >= 1 && mes <= 12 && dia >= 1 && dia <= diasMes[mes - 1] && anio >= 1900 && anio <= 2100;
}

static string leerFecha(const string& mensaje)
{
	while (true)
	{
		string f = leerLinea(mensaje + " (dd/mm/aaaa): ");
		if (fechaValida(f))
		{
			return f;
		}
		cout << "Fecha no valida. Use el formato dd/mm/aaaa.\n";
	}
}

static string leerHora(const string& mensaje)
{
	while (true)
	{
		string h = leerLinea(mensaje + " (hh:mm): ");
		if (h.length() == 5 && h[2] == ':' && isdigit((unsigned char)h[0]) && isdigit((unsigned char)h[1])
			&& isdigit((unsigned char)h[3]) && isdigit((unsigned char)h[4]))
		{
			int hh = atoi(h.substr(0, 2).c_str());
			int mm = atoi(h.substr(3, 2).c_str());
			if (hh <= 23 && mm <= 59)
			{
				return h;
			}
		}
		cout << "Hora no valida. Use el formato hh:mm (24 horas).\n";
	}
}

static string leerCorreo()
{
	while (true)
	{
		string correo = leerLinea("Correo electronico: ");
		if (correo.find('@') != string::npos && correo.find(' ') == string::npos)
		{
			return correo;
		}
		cout << "Correo no valido (debe contener @ y no tener espacios).\n";
	}
}

// =====================================================================
//  Seleccion de objetos (siempre se verifica que existan y pertenezcan
//  al centro correspondiente)
// =====================================================================

static CentroDistribucion* pedirCentro(ListaCentrosDistribucion& centros)
{
	if (centros.estaVacia())
	{
		cout << "No hay centros de distribucion registrados. Registre uno primero.\n";
		return nullptr;
	}

	cout << "\nCentros disponibles:\n";
	NodoCentroDistribucion* aux = centros.getPrimero();
	while (aux != nullptr)
	{
		cout << "  " << aux->getDato()->getCodigo() << " - " << aux->getDato()->getNombre() << endl;
		aux = aux->getSiguiente();
	}

	CentroDistribucion* centro = centros.buscar(leerLinea("Codigo del centro: "));
	if (centro == nullptr)
	{
		cout << "Centro no encontrado.\n";
	}
	return centro;
}

static Cliente* pedirCliente(CentroDistribucion* centro)
{
	Cliente* cliente = centro->getListaClientes()->buscar(leerLinea("Identificacion del cliente: "));
	if (cliente == nullptr)
	{
		cout << "Cliente no encontrado en este centro.\n";
	}
	return cliente;
}

static Colaborador* pedirColaborador(CentroDistribucion* centro, const string& mensaje)
{
	Colaborador* colaborador = centro->getListaColaboradores()->buscar(leerLinea(mensaje));
	if (colaborador == nullptr)
	{
		cout << "Colaborador no encontrado en este centro.\n";
	}
	return colaborador;
}

static Paquete* pedirPaquete(CentroDistribucion* centro)
{
	Paquete* paquete = centro->getListaPaquetes()->buscar(leerLinea("Codigo del paquete: "));
	if (paquete == nullptr)
	{
		cout << "Paquete no encontrado en este centro.\n";
	}
	return paquete;
}

static Bodega* pedirBodega(CentroDistribucion* centro)
{
	Bodega* bodega = centro->getListaBodegas()->buscar(leerLinea("Codigo de la bodega: "));
	if (bodega == nullptr)
	{
		cout << "Bodega no encontrada en este centro.\n";
	}
	return bodega;
}

// =====================================================================
//  Flujos interactivos de almacenamiento
// =====================================================================

static void mostrarBodegasCompatibles(CentroDistribucion* centro, Paquete* paquete)
{
	cout << "\nBodegas compatibles con la categoria " << paquete->getCategoria() << ":\n";
	bool hay = false;
	NodoBodega* aux = centro->getListaBodegas()->getPrimero();
	while (aux != nullptr)
	{
		Bodega* b = aux->getDato();
		if (b->esCompatible(paquete->getCategoria()))
		{
			cout << "  " << b->getCodigo() << " - " << b->getNombre() << " | libres: " << b->celdasLibres()
				<< " de " << b->totalCeldas() << " (" << b->porcentajeDisponible() << "% disponible)\n";
			hay = true;
		}
		aux = aux->getSiguiente();
	}
	if (!hay)
	{
		cout << "  (ninguna)\n";
	}
}

static void flujoAlmacenar(CentroDistribucion* centro, Paquete* paquete)
{
	bool incidenciaPrevia = paquete->getEstado() == "Incidencia" && !paquete->tieneUbicacion()
		&& paquete->getEstadoAntesIncidencia() == "Recibido";

	if (paquete->getEstado() != "Recibido" && !incidenciaPrevia)
	{
		cout << "El paquete esta en estado " << paquete->getEstado() << ": solo se almacenan paquetes Recibidos"
			<< " (o con una incidencia ocurrida antes del almacenamiento).\n";
		return;
	}

	Bodega* recomendada = centro->recomendarBodega(paquete);
	if (recomendada == nullptr)
	{
		cout << "No existe una bodega compatible con espacio disponible. No se modifico el paquete.\n";
		return;
	}

	int filaRec = 0, colRec = 0;
	recomendada->primeraCeldaLibre(filaRec, colRec);

	mostrarBodegasCompatibles(centro, paquete);
	cout << "\nRECOMENDACION: bodega " << recomendada->getCodigo() << " (la de mayor porcentaje disponible), celda "
		<< recomendada->codigoCelda(filaRec, colRec) << ".\n";
	recomendada->mostrarBodega();

	Bodega* bodega = recomendada;
	int fila = filaRec;
	int columna = colRec;

	cout << "\n1. Aceptar la recomendacion\n2. Elegir otra celda\n3. Cancelar\n";
	int opcion = leerEntero("Opcion: ", 1, 3);
	if (opcion == 3)
	{
		cout << "Operacion cancelada.\n";
		return;
	}
	if (opcion == 2)
	{
		bodega = pedirBodega(centro);
		if (bodega == nullptr) return;
		if (!bodega->esCompatible(paquete->getCategoria()))
		{
			cout << "Esa bodega no es compatible con la categoria del paquete.\n";
			return;
		}
		bodega->mostrarBodega();
		cout << "Celdas disponibles: ";
		bodega->mostrarCeldasLibres();
		fila = leerEntero("Fila destino: ", 0, 100000);
		columna = leerEntero("Columna destino: ", 0, 100000);
	}

	Colaborador* responsable = pedirColaborador(centro, "Identificacion del colaborador responsable: ");
	if (responsable == nullptr) return;
	string fecha = leerFecha("Fecha del cambio");

	string error;
	if (centro->almacenarPaquete(paquete, bodega, fila, columna, responsable, fecha, error))
	{
		cout << "Paquete almacenado en la celda " << bodega->codigoCelda(fila, columna) << ". Estado: Almacenado.\n";
	}
	else
	{
		cout << "No se pudo almacenar: " << error << endl;
	}
}

static void flujoReubicar(CentroDistribucion* centro, Paquete* paquete)
{
	if (paquete->getEstado() != "Almacenado")
	{
		cout << "Solo se pueden reubicar paquetes Almacenados.\n";
		return;
	}

	cout << "Ubicacion actual: bodega " << paquete->getBodegaAsignada() << ", fila " << paquete->getFila()
		<< ", columna " << paquete->getColumna() << endl;
	mostrarBodegasCompatibles(centro, paquete);

	Bodega* destino = pedirBodega(centro);
	if (destino == nullptr) return;

	destino->mostrarBodega();
	cout << "Celdas disponibles: ";
	destino->mostrarCeldasLibres();
	int fila = leerEntero("Fila destino: ", 0, 100000);
	int columna = leerEntero("Columna destino: ", 0, 100000);

	string error;
	if (centro->reubicarPaquete(paquete, destino, fila, columna, error))
	{
		cout << "Paquete reubicado en la celda " << destino->codigoCelda(fila, columna) << ".\n";
	}
	else
	{
		cout << "No se pudo reubicar (la ubicacion original se conserva): " << error << endl;
	}
}

// =====================================================================
//  Datos quemados para agilizar las pruebas
// =====================================================================

static void cargarDatosQuemados(ListaCentrosDistribucion& centros)
{
	string error;

	CentroDistribucion* cd1 = new CentroDistribucion("CD01", "Centro San Jose", "San Jose", "Avenida Segunda, 200 m norte del Correo", "2222-0001");
	CentroDistribucion* cd2 = new CentroDistribucion("CD02", "Centro Cartago", "Cartago", "Frente a la Basilica, Cartago centro", "2550-0002");
	centros.insertarCentro(cd1);
	centros.insertarCentro(cd2);

	// Clientes (persona fisica y empresa)
	cd1->getListaClientes()->insertar(new PersonaFisica("1-1111-1111", "Maria Rojas", "8888-1111", "maria@correo.com"));
	cd1->getListaClientes()->insertar(new Empresa("3-101-555555", "Tecnologias del Sur S.A.", "2222-5555", "info@tecsur.com", "Venta de equipo", 10));
	cd1->getListaClientes()->insertar(new PersonaFisica("2-2222-2222", "Luis Mora", "8888-2222", "luis@correo.com"));
	cd2->getListaClientes()->insertar(new PersonaFisica("1-1111-1111", "Maria Rojas", "8888-1111", "maria@correo.com"));
	cd2->getListaClientes()->insertar(new Empresa("3-101-777777", "Cafe Tierra Viva S.A.", "2550-7777", "ventas@tierraviva.com", "Exportacion", 25));

	// Colaboradores
	cd1->getListaColaboradores()->insertarColaborador(new Colaborador("C-01", "Ana Vargas", "15/01/2022", "Supervisora"));
	cd1->getListaColaboradores()->insertarColaborador(new Colaborador("C-02", "Pedro Solis", "03/05/2023", "Despachador"));
	cd2->getListaColaboradores()->insertarColaborador(new Colaborador("C-01", "Carla Jimenez", "20/08/2021", "Supervisora"));

	// Bodegas
	cd1->getListaBodegas()->insertarBodega(new Bodega("A", "Bodega General", 1, 3, 4));
	cd1->getListaBodegas()->insertarBodega(new Bodega("B", "Bodega Fragil", 2, 2, 3));
	cd1->getListaBodegas()->insertarBodega(new Bodega("T", "Bodega Tecnologia", 3, 2, 2));
	cd1->getListaBodegas()->insertarBodega(new Bodega("D", "Bodega Documentos", 4, 2, 3));
	cd2->getListaBodegas()->insertarBodega(new Bodega("A", "Bodega General Cartago", 1, 2, 3));

	// Paquetes
	Cliente* maria = cd1->getListaClientes()->buscar("1-1111-1111");
	Cliente* empresa = cd1->getListaClientes()->buscar("3-101-555555");
	Cliente* luis = cd1->getListaClientes()->buscar("2-2222-2222");
	Colaborador* ana = cd1->getListaColaboradores()->buscar("C-01");
	Colaborador* pedro = cd1->getListaColaboradores()->buscar("C-02");

	cd1->getListaPaquetes()->insertarPaquete(new Paquete("PK101", "Caja con ropa", 2.5f, "General", maria, "CD01"));
	cd1->getListaPaquetes()->insertarPaquete(new Paquete("PK102", "Juego de copas de cristal", 4.0f, "Fragil", luis, "CD01"));
	cd1->getListaPaquetes()->insertarPaquete(new Paquete("PK103", "Laptop", 3.0f, "Tecnologia", empresa, "CD01"));
	cd1->getListaPaquetes()->insertarPaquete(new Paquete("PK104", "Contratos legales", 0.5f, "Documentos", maria, "CD01"));
	cd1->getListaPaquetes()->insertarPaquete(new Paquete("PK105", "Repuestos de bicicleta", 6.0f, "General", luis, "CD01"));
	cd1->getListaPaquetes()->insertarPaquete(new Paquete("PK106", "Impresora", 8.0f, "Tecnologia", empresa, "CD01"));
	cd2->getListaPaquetes()->insertarPaquete(new Paquete("PK201", "Sacos de cafe", 20.0f, "General", cd2->getListaClientes()->buscar("3-101-777777"), "CD02"));

	// Estados: PK101-PK104 y PK106 almacenados, PK105 queda Recibido
	cd1->almacenarPaquete(cd1->getListaPaquetes()->buscar("PK101"), cd1->getListaBodegas()->buscar("A"), 0, 1, ana, "10/10/2026", error);
	cd1->almacenarPaquete(cd1->getListaPaquetes()->buscar("PK102"), cd1->getListaBodegas()->buscar("B"), 0, 0, ana, "10/10/2026", error);
	cd1->almacenarPaquete(cd1->getListaPaquetes()->buscar("PK103"), cd1->getListaBodegas()->buscar("T"), 1, 1, pedro, "11/10/2026", error);
	cd1->almacenarPaquete(cd1->getListaPaquetes()->buscar("PK104"), cd1->getListaBodegas()->buscar("D"), 0, 2, pedro, "11/10/2026", error);
	cd1->almacenarPaquete(cd1->getListaPaquetes()->buscar("PK106"), cd1->getListaBodegas()->buscar("T"), 0, 0, ana, "12/10/2026", error);

	// Solicitudes: PK101 pendiente, PK103 aprobada (con despacho En proceso), PK102 aprobada y entregada
	cd1->crearSolicitud("SOL-001", maria, cd1->getListaPaquetes()->buscar("PK101"), ana, "Heredia, 100 m sur de la iglesia", "13/10/2026", error);

	cd1->crearSolicitud("SOL-002", empresa, cd1->getListaPaquetes()->buscar("PK103"), pedro, "Alajuela, Zona Franca", "13/10/2026", error);
	cd1->aprobarSolicitud(cd1->getListaSolicitudes()->buscar("SOL-002"), "DES-001", "14/10/2026", "09:30", error);

	cd1->crearSolicitud("SOL-003", luis, cd1->getListaPaquetes()->buscar("PK102"), ana, "Cartago, Barrio Los Angeles", "13/10/2026", error);
	cd1->aprobarSolicitud(cd1->getListaSolicitudes()->buscar("SOL-003"), "DES-002", "14/10/2026", "10:15", error);
	cd1->finalizarDespacho(cd1->getListaDespachos()->buscar("DES-002"), "15/10/2026", error);

	cout << "Datos de prueba cargados: 2 centros, clientes, colaboradores, bodegas, paquetes, solicitudes y despachos.\n";
}

// =====================================================================
//  Menus
// =====================================================================

static void menuCentros(ListaCentrosDistribucion& centros)
{
	int opcion = 0;
	do
	{
		cout << "\n--- CENTROS DE DISTRIBUCION ---\n";
		cout << "1. Registrar centro\n2. Buscar centro\n3. Mostrar centros\n4. Eliminar centro\n5. Regresar\n";
		opcion = leerEntero("Opcion: ", 1, 5);

		if (opcion == 1)
		{
			string codigo = leerLinea("Codigo (unico en todo el sistema): ");
			if (centros.buscar(codigo) != nullptr)
			{
				cout << "Ya existe un centro con ese codigo.\n";
				continue;
			}
			string nombre = leerLinea("Nombre: ");
			string provincia = leerLinea("Provincia: ");
			string direccion = leerLinea("Direccion descriptiva: ");
			string telefono = leerLinea("Telefono: ");
			centros.insertarCentro(new CentroDistribucion(codigo, nombre, provincia, direccion, telefono));
			cout << "Centro registrado. Aun no tiene bodegas: agreguelas desde el menu de Bodegas.\n";
		}
		else if (opcion == 2)
		{
			CentroDistribucion* centro = centros.buscar(leerLinea("Codigo del centro: "));
			if (centro != nullptr) centro->mostrarCentro();
			else cout << "Centro no encontrado.\n";
		}
		else if (opcion == 3)
		{
			centros.mostrarCentros();
		}
		else if (opcion == 4)
		{
			string codigo = leerLinea("Codigo del centro a eliminar: ");
			CentroDistribucion* centro = centros.buscar(codigo);
			if (centro == nullptr)
			{
				cout << "Centro no encontrado.\n";
			}
			else if (!centro->estaVacio())
			{
				cout << "No se puede eliminar: el centro tiene clientes, colaboradores, bodegas, paquetes, solicitudes o despachos asociados.\n";
			}
			else if (centros.eliminarCentro(codigo))
			{
				cout << "Centro eliminado.\n";
			}
		}
	} while (opcion != 5);
}

static void menuClientes(ListaCentrosDistribucion& centros)
{
	CentroDistribucion* centro = pedirCentro(centros);
	if (centro == nullptr) return;

	int opcion = 0;
	do
	{
		cout << "\n--- CLIENTES (" << centro->getNombre() << ") ---\n";
		cout << "1. Registrar\n2. Buscar\n3. Mostrar todos\n4. Eliminar\n5. Regresar\n";
		opcion = leerEntero("Opcion: ", 1, 5);

		if (opcion == 1)
		{
			string identificacion = leerLinea("Identificacion: ");
			if (centro->getListaClientes()->buscar(identificacion) != nullptr)
			{
				cout << "Ya existe un cliente con esa identificacion en este centro.\n";
				continue;
			}
			string nombre = leerLinea("Nombre: ");
			string telefono = leerLinea("Telefono: ");
			string correo = leerCorreo();
			cout << "1. Persona fisica\n2. Empresa\n";
			int tipo = leerEntero("Tipo de cliente: ", 1, 2);

			if (tipo == 1)
			{
				centro->getListaClientes()->insertar(new PersonaFisica(identificacion, nombre, telefono, correo));
			}
			else
			{
				string actividad = leerLinea("Actividad economica: ");
				float descuento = (float)leerDecimal("Porcentaje de descuento autorizado (0-100): ", 0, 100, true);
				centro->getListaClientes()->insertar(new Empresa(identificacion, nombre, telefono, correo, actividad, descuento));
			}
			cout << "Cliente registrado.\n";
		}
		else if (opcion == 2)
		{
			Cliente* cliente = pedirCliente(centro);
			if (cliente != nullptr) cliente->mostrarInfo();
		}
		else if (opcion == 3)
		{
			centro->getListaClientes()->mostrarTodos();
		}
		else if (opcion == 4)
		{
			string error;
			if (centro->eliminarCliente(leerLinea("Identificacion del cliente a eliminar: "), error))
				cout << "Cliente eliminado.\n";
			else
				cout << "No se pudo eliminar: " << error << endl;
		}
	} while (opcion != 5);
}

static void menuColaboradores(ListaCentrosDistribucion& centros)
{
	CentroDistribucion* centro = pedirCentro(centros);
	if (centro == nullptr) return;

	int opcion = 0;
	do
	{
		cout << "\n--- COLABORADORES (" << centro->getNombre() << ") ---\n";
		cout << "1. Registrar\n2. Buscar\n3. Mostrar todos\n4. Eliminar\n5. Regresar\n";
		opcion = leerEntero("Opcion: ", 1, 5);

		if (opcion == 1)
		{
			string identificacion = leerLinea("Identificacion: ");
			if (centro->getListaColaboradores()->buscar(identificacion) != nullptr)
			{
				cout << "Ya existe un colaborador con esa identificacion en este centro.\n";
				continue;
			}
			string nombre = leerLinea("Nombre completo: ");
			string fecha = leerFecha("Fecha de ingreso");
			string puesto = leerLinea("Puesto: ");
			centro->getListaColaboradores()->insertarColaborador(new Colaborador(identificacion, nombre, fecha, puesto));
			cout << "Colaborador registrado.\n";
		}
		else if (opcion == 2)
		{
			Colaborador* colaborador = pedirColaborador(centro, "Identificacion: ");
			if (colaborador != nullptr) colaborador->mostrarInfo();
		}
		else if (opcion == 3)
		{
			centro->getListaColaboradores()->mostrar();
		}
		else if (opcion == 4)
		{
			string error;
			if (centro->eliminarColaborador(leerLinea("Identificacion del colaborador a eliminar: "), error))
				cout << "Colaborador eliminado.\n";
			else
				cout << "No se pudo eliminar: " << error << endl;
		}
	} while (opcion != 5);
}

static void menuBodegas(ListaCentrosDistribucion& centros)
{
	CentroDistribucion* centro = pedirCentro(centros);
	if (centro == nullptr) return;

	int opcion = 0;
	do
	{
		cout << "\n--- BODEGAS (" << centro->getNombre() << ") ---\n";
		cout << "1. Registrar bodega\n2. Buscar bodega\n3. Mostrar bodegas\n4. Consultar matriz de una bodega\n";
		cout << "5. Consultar el paquete de una celda\n6. Eliminar bodega\n7. Regresar\n";
		opcion = leerEntero("Opcion: ", 1, 7);

		if (opcion == 1)
		{
			string codigo = leerLinea("Codigo de la bodega (unico en el centro): ");
			if (centro->getListaBodegas()->buscar(codigo) != nullptr)
			{
				cout << "Ya existe una bodega con ese codigo en este centro.\n";
				continue;
			}
			string nombre = leerLinea("Nombre: ");
			cout << "Tipos: 1. General  2. Fragil  3. Tecnologia  4. Documentos\n";
			int tipo = leerEntero("Codigo de tipo (1-4): ", 1, 4);
			int filas = leerEntero("Cantidad de filas (mayor que 0): ", 1, 100);
			int columnas = leerEntero("Cantidad de columnas (mayor que 0): ", 1, 100);
			centro->getListaBodegas()->insertarBodega(new Bodega(codigo, nombre, tipo, filas, columnas));
			cout << "Bodega registrada con una matriz de " << filas << " x " << columnas << " celdas.\n";
		}
		else if (opcion == 2)
		{
			Bodega* bodega = pedirBodega(centro);
			if (bodega != nullptr) bodega->mostrarResumen();
		}
		else if (opcion == 3)
		{
			centro->getListaBodegas()->mostrar();
		}
		else if (opcion == 4)
		{
			Bodega* bodega = pedirBodega(centro);
			if (bodega != nullptr) bodega->mostrarBodega();
		}
		else if (opcion == 5)
		{
			Bodega* bodega = pedirBodega(centro);
			if (bodega != nullptr)
			{
				int fila = leerEntero("Fila: ", 0, 100000);
				int columna = leerEntero("Columna: ", 0, 100000);
				if (!bodega->existeCelda(fila, columna))
				{
					cout << "La celda no existe en esta bodega.\n";
				}
				else
				{
					Paquete* p = bodega->obtenerPaquete(fila, columna);
					cout << "Celda " << bodega->codigoCelda(fila, columna) << ": ";
					if (p == nullptr) cout << "LIBRE\n";
					else { cout << "OCUPADA\n"; p->mostrarInfo(); }
				}
			}
		}
		else if (opcion == 6)
		{
			string error;
			if (centro->eliminarBodega(leerLinea("Codigo de la bodega a eliminar: "), error))
				cout << "Bodega eliminada.\n";
			else
				cout << "No se pudo eliminar: " << error << endl;
		}
	} while (opcion != 7);
}

static void registrarPaquete(ListaCentrosDistribucion& centros, CentroDistribucion* centro)
{
	string codigo = leerLinea("Codigo del paquete (unico en todo el sistema): ");
	if (centros.buscarPaquete(codigo) != nullptr)
	{
		cout << "Ya existe un paquete con ese codigo.\n";
		return;
	}
	string descripcion = leerLinea("Descripcion: ");
	float peso = (float)leerDecimal("Peso en kg (mayor que 0): ", 0, 100000, false);

	string categoria = "";
	while (categoria == "")
	{
		cout << "Categorias: General, Fragil, Tecnologia, Documentos\n";
		categoria = Paquete::normalizarCategoria(leerLinea("Categoria: "));
		if (categoria == "") cout << "Categoria no valida.\n";
	}

	Cliente* cliente = pedirCliente(centro);
	if (cliente == nullptr) return;

	centro->getListaPaquetes()->insertarPaquete(new Paquete(codigo, descripcion, peso, categoria, cliente, centro->getCodigo()));
	cout << "Paquete registrado en estado Recibido (sin bodega ni celda).\n";

	cout << "\n1. Almacenarlo ahora\n2. Almacenarlo despues\n";
	if (leerEntero("Opcion: ", 1, 2) == 1)
	{
		flujoAlmacenar(centro, centro->getListaPaquetes()->buscar(codigo));
	}
}

static void menuPaquetes(ListaCentrosDistribucion& centros)
{
	CentroDistribucion* centro = pedirCentro(centros);
	if (centro == nullptr) return;

	int opcion = 0;
	do
	{
		cout << "\n--- PAQUETES (" << centro->getNombre() << ") ---\n";
		cout << "1. Registrar paquete\n2. Buscar paquete\n3. Mostrar paquetes\n4. Eliminar paquete\n";
		cout << "5. Almacenar paquete (asignar celda)\n6. Reubicar paquete\n";
		cout << "7. Registrar incidencia\n8. Resolver incidencia\n9. Ver bitacora de un paquete\n10. Regresar\n";
		opcion = leerEntero("Opcion: ", 1, 10);

		if (opcion == 1)
		{
			registrarPaquete(centros, centro);
		}
		else if (opcion == 2)
		{
			// los paquetes se buscan por su codigo unico global
			Paquete* paquete = centros.buscarPaquete(leerLinea("Codigo del paquete: "));
			if (paquete != nullptr) paquete->mostrarInfo();
			else cout << "Paquete no encontrado.\n";
		}
		else if (opcion == 3)
		{
			centro->getListaPaquetes()->mostrar();
		}
		else if (opcion == 4)
		{
			string error;
			if (centro->eliminarPaquete(leerLinea("Codigo del paquete a eliminar: "), error))
				cout << "Paquete eliminado.\n";
			else
				cout << "No se pudo eliminar: " << error << endl;
		}
		else if (opcion == 5)
		{
			Paquete* paquete = pedirPaquete(centro);
			if (paquete != nullptr) flujoAlmacenar(centro, paquete);
		}
		else if (opcion == 6)
		{
			Paquete* paquete = pedirPaquete(centro);
			if (paquete != nullptr) flujoReubicar(centro, paquete);
		}
		else if (opcion == 7 || opcion == 8)
		{
			Paquete* paquete = pedirPaquete(centro);
			if (paquete == nullptr) continue;

			if (opcion == 8 && paquete->getEstado() == "Incidencia" && paquete->getEstadoAntesIncidencia() == "Recibido")
			{
				cout << "La incidencia ocurrio antes del almacenamiento: se resuelve almacenando el paquete.\n";
				flujoAlmacenar(centro, paquete);
				continue;
			}

			Colaborador* responsable = pedirColaborador(centro, "Identificacion del colaborador responsable: ");
			if (responsable == nullptr) continue;
			string fecha = leerFecha("Fecha del cambio");

			string error;
			bool exito = (opcion == 7)
				? centro->registrarIncidencia(paquete, responsable, fecha, error)
				: centro->resolverIncidencia(paquete, responsable, fecha, error);

			if (exito) cout << "Operacion realizada. Estado actual: " << paquete->getEstado() << endl;
			else cout << "No se pudo realizar la operacion: " << error << endl;
		}
		else if (opcion == 9)
		{
			Paquete* paquete = pedirPaquete(centro);
			if (paquete != nullptr)
			{
				if (paquete->getBitacora()->estaVacia()) cout << "El paquete aun no tiene cambios de estado.\n";
				else paquete->getBitacora()->mostrarBitacora();
			}
		}
	} while (opcion != 10);
}

static void menuSolicitudes(ListaCentrosDistribucion& centros)
{
	CentroDistribucion* centro = pedirCentro(centros);
	if (centro == nullptr) return;

	int opcion = 0;
	do
	{
		cout << "\n--- SOLICITUDES DE ENVIO (" << centro->getNombre() << ") ---\n";
		cout << "1. Crear solicitud\n2. Buscar solicitud\n3. Mostrar solicitudes\n";
		cout << "4. Aprobar solicitud (crea el despacho)\n5. Rechazar solicitud\n6. Anular solicitud\n7. Regresar\n";
		opcion = leerEntero("Opcion: ", 1, 7);

		if (opcion == 1)
		{
			string codigo = leerLinea("Codigo de la solicitud (unico en todo el sistema): ");
			if (centros.buscarSolicitud(codigo) != nullptr)
			{
				cout << "Ya existe una solicitud con ese codigo.\n";
				continue;
			}
			Cliente* cliente = pedirCliente(centro);
			if (cliente == nullptr) continue;
			Paquete* paquete = pedirPaquete(centro);
			if (paquete == nullptr) continue;
			Colaborador* responsable = pedirColaborador(centro, "Identificacion del colaborador responsable: ");
			if (responsable == nullptr) continue;
			string destino = leerLinea("Destino de entrega (direccion): ");
			string fecha = leerFecha("Fecha de la solicitud");

			string error;
			SolicitudEnvio* nueva = centro->crearSolicitud(codigo, cliente, paquete, responsable, destino, fecha, error);
			if (nueva != nullptr)
			{
				cout << "Solicitud creada en estado Pendiente.\n";
				cout << "Costo estimado (CRC): " << nueva->getCostoEstimado() << endl;
			}
			else
			{
				cout << "No se pudo crear la solicitud: " << error << endl;
			}
		}
		else if (opcion == 2)
		{
			SolicitudEnvio* solicitud = centros.buscarSolicitud(leerLinea("Codigo de la solicitud: "));
			if (solicitud != nullptr) solicitud->mostrarSolicitud();
			else cout << "Solicitud no encontrada.\n";
		}
		else if (opcion == 3)
		{
			centro->getListaSolicitudes()->mostrarSolicitudes();
		}
		else if (opcion == 4)
		{
			SolicitudEnvio* solicitud = centro->getListaSolicitudes()->buscar(leerLinea("Codigo de la solicitud a aprobar: "));
			if (solicitud == nullptr)
			{
				cout << "Solicitud no encontrada en este centro.\n";
				continue;
			}
			string codigoDespacho = leerLinea("Codigo del despacho (unico en todo el sistema): ");
			if (centros.buscarDespacho(codigoDespacho) != nullptr)
			{
				cout << "Ya existe un despacho con ese codigo.\n";
				continue;
			}
			string fecha = leerFecha("Fecha del despacho");
			string hora = leerHora("Hora del despacho");

			string error;
			Despacho* despacho = centro->aprobarSolicitud(solicitud, codigoDespacho, fecha, hora, error);
			if (despacho != nullptr)
			{
				cout << "Solicitud aprobada. Despacho " << despacho->getCodigo() << " creado En proceso; el paquete esta En transito y su celda fue liberada.\n";
			}
			else
			{
				cout << "No se pudo aprobar: " << error << endl;
			}
		}
		else if (opcion == 5 || opcion == 6)
		{
			string codigo = leerLinea(opcion == 5 ? "Codigo de la solicitud a rechazar: " : "Codigo de la solicitud a anular: ");
			SolicitudEnvio* solicitud = centro->getListaSolicitudes()->buscar(codigo);
			if (solicitud == nullptr)
			{
				cout << "Solicitud no encontrada en este centro.\n";
			}
			else if (centro->getListaSolicitudes()->cambiarEstado(codigo, opcion == 5 ? "Rechazada" : "Anulada"))
			{
				cout << "Solicitud " << (opcion == 5 ? "rechazada" : "anulada") << ".\n";
			}
			else
			{
				cout << "Solo se puede cambiar una solicitud Pendiente (estado actual: " << solicitud->getEstado() << ").\n";
			}
		}
	} while (opcion != 7);
}

static void menuDespachos(ListaCentrosDistribucion& centros)
{
	CentroDistribucion* centro = pedirCentro(centros);
	if (centro == nullptr) return;

	int opcion = 0;
	do
	{
		cout << "\n--- DESPACHOS (" << centro->getNombre() << ") ---\n";
		cout << "1. Buscar despacho\n2. Mostrar despachos\n3. Finalizar entrega\n4. Regresar\n";
		opcion = leerEntero("Opcion: ", 1, 4);

		if (opcion == 1)
		{
			Despacho* despacho = centros.buscarDespacho(leerLinea("Codigo del despacho: "));
			if (despacho != nullptr) despacho->mostrarDespacho();
			else cout << "Despacho no encontrado.\n";
		}
		else if (opcion == 2)
		{
			centro->getListaDespachos()->mostrarDespachos();
		}
		else if (opcion == 3)
		{
			Despacho* despacho = centro->getListaDespachos()->buscar(leerLinea("Codigo del despacho a finalizar: "));
			if (despacho == nullptr)
			{
				cout << "Despacho no encontrado en este centro.\n";
				continue;
			}
			string fecha = leerFecha("Fecha de la entrega");
			string error;
			if (centro->finalizarDespacho(despacho, fecha, error))
				cout << "Entrega finalizada: despacho Finalizado y paquete Entregado.\n";
			else
				cout << "No se pudo finalizar la entrega: " << error << endl;
		}
	} while (opcion != 4);
}

static void menuReportes(ListaCentrosDistribucion& centros)
{
	int opcion = 0;
	do
	{
		cout << "\n--- REPORTES ---\n";
		cout << "1. Historial de un cliente\n2. Clientes por cantidad de envios\n3. Bitacora de un paquete\n";
		cout << "4. Consulta de despacho de un paquete\n5. Ocupacion de bodegas\n6. Despachos por colaborador\n7. Regresar\n";
		opcion = leerEntero("Opcion: ", 1, 7);

		if (opcion == 1)
		{
			CentroDistribucion* centro = pedirCentro(centros);
			if (centro == nullptr) continue;
			Cliente* cliente = pedirCliente(centro);
			if (cliente != nullptr) centro->reporteHistorialCliente(cliente);
		}
		else if (opcion == 2)
		{
			CentroDistribucion* centro = pedirCentro(centros);
			if (centro != nullptr) centro->reporteClientesPorEnvios();
		}
		else if (opcion == 3)
		{
			Paquete* paquete = centros.buscarPaquete(leerLinea("Codigo del paquete: "));
			if (paquete == nullptr)
			{
				cout << "Paquete no encontrado.\n";
				continue;
			}
			cout << "\n=== BITACORA DEL PAQUETE " << paquete->getCodigo() << " (del mas antiguo al mas reciente) ===\n";
			if (paquete->getBitacora()->estaVacia()) cout << "El paquete aun no tiene cambios de estado.\n";
			else paquete->getBitacora()->mostrarBitacora();
		}
		else if (opcion == 4)
		{
			Paquete* paquete = centros.buscarPaquete(leerLinea("Codigo del paquete: "));
			if (paquete == nullptr)
			{
				cout << "Paquete no encontrado.\n";
				continue;
			}
			CentroDistribucion* centro = centros.buscar(paquete->getCentroDis());
			if (centro != nullptr) centro->reporteDespachoDePaquete(paquete);
		}
		else if (opcion == 5)
		{
			if (centros.estaVacia()) cout << "No hay centros registrados.\n";
			NodoCentroDistribucion* aux = centros.getPrimero();
			while (aux != nullptr)
			{
				aux->getDato()->reporteOcupacionBodegas();
				aux = aux->getSiguiente();
			}
		}
		else if (opcion == 6)
		{
			CentroDistribucion* centro = pedirCentro(centros);
			if (centro == nullptr) continue;
			Colaborador* colaborador = pedirColaborador(centro, "Identificacion del colaborador: ");
			if (colaborador != nullptr) centro->reporteDespachosPorColaborador(colaborador);
		}
	} while (opcion != 7);
}

int main()
{
	ListaCentrosDistribucion centros;

	cout << "=== TICOPACK LOGISTICS: RED DE CENTROS DE DISTRIBUCION ===\n";
	cout << "1. Cargar datos de prueba (datos quemados)\n2. Iniciar con el sistema vacio\n";
	if (leerEntero("Opcion: ", 1, 2) == 1)
	{
		cargarDatosQuemados(centros);
	}

	int opcion = 0;
	do
	{
		cout << "\n=== MENU PRINCIPAL ===\n";
		cout << "1. Centros de distribucion\n";
		cout << "2. Clientes\n";
		cout << "3. Colaboradores\n";
		cout << "4. Bodegas y consulta de matrices\n";
		cout << "5. Paquetes, almacenamiento, reubicacion y cambios de estado\n";
		cout << "6. Solicitudes de envio\n";
		cout << "7. Despachos\n";
		cout << "8. Reportes\n";
		cout << "9. Salir del sistema\n";
		opcion = leerEntero("Opcion: ", 1, 9);

		switch (opcion)
		{
		case 1: menuCentros(centros); break;
		case 2: menuClientes(centros); break;
		case 3: menuColaboradores(centros); break;
		case 4: menuBodegas(centros); break;
		case 5: menuPaquetes(centros); break;
		case 6: menuSolicitudes(centros); break;
		case 7: menuDespachos(centros); break;
		case 8: menuReportes(centros); break;
		case 9: cout << "Hasta pronto.\n"; break;
		}
	} while (opcion != 9);

	return 0;
}
