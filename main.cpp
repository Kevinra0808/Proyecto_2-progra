#include <iostream>
#include <string>
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

int main()
{
	ListaCentrosDistribucion centros;
	ListaBitacora bitacora;
	int opcion = 0;

	do
	{
		cout << "\n=== TICOPACKS LOGISTICS ===\n";
		cout << "1. Centros de distribucion\n";
		cout << "2. Clientes\n";
		cout << "3. Colaboradores\n";
		cout << "4. Bodegas\n";
		cout << "5. Paquetes\n";
		cout << "6. Solicitudes de envio\n";
		cout << "7. Despachos\n";
		cout << "8. Reportes\n";
		cout << "9. Salir\n";
		cout << "Opcion: ";
		cin >> opcion;

		switch (opcion)
		{
		case 1:
		{
			int opcionCentro = 0;
			do
			{
				cout << "\n--- CENTROS DE DISTRIBUCION ---\n";
				cout << "1. Registrar centro\n2. Buscar centro\n3. Mostrar centros\n";
				cout << "4. Eliminar centro vacio\n5. Regresar\nOpcion: ";
				cin >> opcionCentro;

				if (opcionCentro == 1)
				{
					string codigo, nombre, provincia, direccion, telefono;
					cout << "Codigo: "; cin >> codigo;
					if (centros.buscar(codigo) != nullptr)
					{
						cout << "Ya existe ese centro.\n";
						break;
					}
					cin.ignore();
					cout << "Nombre: "; getline(cin, nombre);
					cout << "Provincia: "; getline(cin, provincia);
					cout << "Direccion descriptiva: "; getline(cin, direccion);
					cout << "Telefono: "; getline(cin, telefono);
					centros.insertarCentro(new CentroDistribucion(codigo, nombre, provincia, direccion, telefono));
					cout << "Centro registrado.\n";
				}
				else if (opcionCentro == 2)
				{
					string codigo;
					cout << "Codigo: "; cin >> codigo;
					CentroDistribucion* centro = centros.buscar(codigo);
					if (centro != nullptr) centro->mostrarCentro();
					else cout << "Centro no encontrado.\n";
				}
				else if (opcionCentro == 3)
					centros.mostrarCentros();
				else if (opcionCentro == 4)
				{
					string codigo;
					cout << "Codigo del centro: "; cin >> codigo;
					if (centros.eliminarCentro(codigo)) cout << "Centro eliminado.\n";
					else cout << "No se pudo eliminar; revise el codigo o si tiene datos.\n";
				}
			} while (opcionCentro != 5);
			break;
		}

		case 2:
		{
			string codigoCentro;
			cout << "Codigo del centro: "; cin >> codigoCentro;
			CentroDistribucion* centro = centros.buscar(codigoCentro);
			if (centro == nullptr)
			{
				cout << "Centro no encontrado.\n";
				break;
			}

			int opcionCliente = 0;
			do
			{
				cout << "\n--- CLIENTES ---\n1. Registrar\n2. Buscar\n3. Mostrar todos\n4. Regresar\nOpcion: ";
				cin >> opcionCliente;
				if (opcionCliente == 1)
				{
					string identificacion, nombre, telefono, correo;
					cout << "Identificacion: "; cin >> identificacion;
					if (centro->getListaClientes()->buscar(identificacion) != nullptr)
					{
						cout << "Ya existe ese cliente.\n";
						break;
					}
					cin.ignore();
					cout << "Nombre: "; getline(cin, nombre);
					cout << "Telefono: "; getline(cin, telefono);
					cout << "Correo: "; getline(cin, correo);
					int tipo;
					cout << "1. Persona  2. Empresa: "; cin >> tipo;
					if (tipo == 1)
						centro->getListaClientes()->insertar(new Cliente(identificacion, nombre, telefono, correo));
					else if (tipo == 2)
					{
						string actividad;
					float descuento;
					cin.ignore();
					cout << "Actividad economica: "; getline(cin, actividad);
					cout << "Descuento: "; cin >> descuento;
					centro->getListaClientes()->insertar(new Empresa(identificacion, nombre, telefono, correo, actividad, descuento));
					}
					else cout << "Tipo de cliente no valido.\n";
				}
				else if (opcionCliente == 2)
				{
					string identificacion;
					cout << "Identificacion: "; cin >> identificacion;
					Cliente* cliente = centro->getListaClientes()->buscar(identificacion);
					if (cliente != nullptr) cliente->mostrarInfo();
					else cout << "Cliente no encontrado.\n";
				}
				else if (opcionCliente == 3)
					centro->getListaClientes()->mostrarTodos();
			} while (opcionCliente != 4);
			break;
		}

		case 3:
		{
			string codigoCentro;
			cout << "Codigo del centro: "; cin >> codigoCentro;
			CentroDistribucion* centro = centros.buscar(codigoCentro);
			if (centro == nullptr)
			{
				cout << "Centro no encontrado.\n";
				break;
			}

			int opcionColaborador = 0;
			do
			{
				cout << "\n--- COLABORADORES ---\n1. Registrar\n2. Buscar\n3. Mostrar todos\n5. Regresar\nOpcion: ";
				cin >> opcionColaborador;
				if (opcionColaborador == 1)
				{
					string identificacion, nombre, fecha, puesto;
					cout << "Identificacion: "; cin >> identificacion;
					if (centro->getListaColaboradores()->buscar(identificacion) != nullptr)
					{
						cout << "Ya existe ese colaborador.\n";
						break;
					}
					cin.ignore();
					cout << "Nombre: "; getline(cin, nombre);
					cout << "Fecha de ingreso: "; getline(cin, fecha);
					cout << "Puesto: "; getline(cin, puesto);
					centro->getListaColaboradores()->insertarColaborador(new Colaborador(identificacion, nombre, fecha, puesto));
					cout << "Colaborador registrado.\n";
				}
				else if (opcionColaborador == 2)
				{
					string identificacion;
					cout << "Identificacion: "; cin >> identificacion;
					Colaborador* colaborador = centro->getListaColaboradores()->buscar(identificacion);
					if (colaborador != nullptr) colaborador->mostrarInfo();
					else cout << "Colaborador no encontrado.\n";
				}
				else if (opcionColaborador == 3)
					centro->getListaColaboradores()->mostrar();
			} while (opcionColaborador != 5);
			break;
		}

		case 4:
		{
			string codigoCentro;
			cout << "Codigo del centro: "; cin >> codigoCentro;
			CentroDistribucion* centro = centros.buscar(codigoCentro);
			if (centro == nullptr)
			{
				cout << "Centro no encontrado.\n";
				break;
			}

			int opcionBodega = 0;
			do
			{
				cout << "\n--- BODEGAS ---\n1. Registrar\n2. Buscar y ver ocupacion\n3. Mostrar\n4. Eliminar vacia\n5. Colocar paquete\n0. Regresar\nOpcion: ";
				cin >> opcionBodega;
				if (opcionBodega == 1)
				{
					string codigo, nombre;
					int tipo, filas, columnas;
					cout << "Codigo: "; cin >> codigo;
					if (centro->getListaBodegas()->buscar(codigo) != nullptr)
					{
						cout << "Ya existe esa bodega.\n";
						break;
					}
					cin.ignore();
					cout << "Nombre: "; getline(cin, nombre);
					cout << "Tipo (numero): "; cin >> tipo;
					cout << "Filas: "; cin >> filas;
					cout << "Columnas: "; cin >> columnas;
					if (filas > 0 && columnas > 0)
					{
						centro->getListaBodegas()->insertarBodega(new Bodega(codigo, nombre, tipo, filas, columnas));
						cout << "Bodega registrada.\n";
					}
					else cout << "Las filas y columnas deben ser mayores que cero.\n";
				}
				else if (opcionBodega == 2)
				{
					string codigo;
					cout << "Codigo: "; cin >> codigo;
					Bodega* bodega = centro->getListaBodegas()->buscar(codigo);
					if (bodega != nullptr)
					{
						bodega->mostrarBodega();
						cout << "Ocupacion: " << bodega->porcentajeOcupacion() << "%\n";
						cout << "Disponible: " << bodega->porcentajeDisponible() << "%\n";
					}
					else cout << "Bodega no encontrada.\n";
				}
				else if (opcionBodega == 3)
					centro->getListaBodegas()->mostrar();
				else if (opcionBodega == 4)
				{
					string codigo;
					cout << "Codigo: "; cin >> codigo;
					if (centro->getListaBodegas()->eliminarBodega(codigo)) cout << "Bodega eliminada.\n";
					else cout << "No se pudo eliminar la bodega.\n";
				}
				else if (opcionBodega == 5)
				{
					string codigoPaquete, codigoBodega;
					int fila, columna;
					cout << "Codigo del paquete: "; cin >> codigoPaquete;
					cout << "Codigo de la bodega: "; cin >> codigoBodega;
					Paquete* paquete = centro->getListaPaquetes()->buscar(codigoPaquete);
					Bodega* bodega = centro->getListaBodegas()->buscar(codigoBodega);
					if (paquete != nullptr && bodega != nullptr)
					{
						cout << "Fila (empieza en 1): "; cin >> fila;
						cout << "Columna (empieza en 1): "; cin >> columna;
						if (bodega->colocarPaquete(paquete, fila - 1, columna - 1)) cout << "Paquete colocado.\n";
						else cout << "Espacio ocupado o posicion incorrecta.\n";
					}
					else cout << "Paquete o bodega no encontrados.\n";
				}
			} while (opcionBodega != 0);
			break;
		}

		case 5:
		{
			string codigoCentro;
			cout << "Codigo del centro: "; cin >> codigoCentro;
			CentroDistribucion* centro = centros.buscar(codigoCentro);
			if (centro == nullptr)
			{
				cout << "Centro no encontrado.\n";
				break;
			}

			int opcionPaquete = 0;
			do
			{
				cout << "\n--- PAQUETES ---\n1. Registrar\n2. Buscar\n3. Mostrar\n4. Cambiar estado\n0. Regresar\nOpcion: ";
				cin >> opcionPaquete;
				if (opcionPaquete == 1)
				{
					string codigo, identificacion, descripcion, categoria;
					float peso;
					cout << "Codigo: "; cin >> codigo;
					if (centro->getListaPaquetes()->buscar(codigo) != nullptr)
					{
						cout << "Ya existe ese paquete.\n";
						break;
					}
					cout << "Identificacion del cliente: "; cin >> identificacion;
					Cliente* cliente = centro->getListaClientes()->buscar(identificacion);
					if (cliente == nullptr)
					{
						cout << "Cliente no encontrado.\n";
						break;
					}
					cin.ignore();
					cout << "Descripcion: "; getline(cin, descripcion);
					cout << "Peso: "; cin >> peso;
					cout << "Categoria (General, Fragil, Tecnologia, Documentos): "; cin >> categoria;
					centro->getListaPaquetes()->insertarPaquete(new Paquete(codigo, descripcion, peso, categoria, cliente, centro->getCodigo()));
					cout << "Paquete registrado.\n";
				}
				else if (opcionPaquete == 2)
				{
					string codigo;
					cout << "Codigo: "; cin >> codigo;
					Paquete* paquete = centro->getListaPaquetes()->buscar(codigo);
					if (paquete != nullptr) paquete->mostrarInfo();
					else cout << "Paquete no encontrado.\n";
				}
				else if (opcionPaquete == 3)
					centro->getListaPaquetes()->mostrar();
				else if (opcionPaquete == 4)
				{
					string codigo, estado;
					cout << "Codigo del paquete: "; cin >> codigo;
					Paquete* paquete = centro->getListaPaquetes()->buscar(codigo);
					if (paquete != nullptr)
					{
						cout << "Nuevo estado: "; cin >> estado;
						paquete->setEstado(estado);
					}
					else cout << "Paquete no encontrado.\n";
				}
			} while (opcionPaquete != 0);
			break;
		}

		case 6:
		{
			string codigoCentro;
			cout << "Codigo del centro: "; cin >> codigoCentro;
			CentroDistribucion* centro = centros.buscar(codigoCentro);
			if (centro == nullptr)
			{
				cout << "Centro no encontrado.\n";
				break;
			}

			int opcionSolicitud = 0;
			do
			{
				cout << "\n--- SOLICITUDES ---\n1. Registrar\n2. Buscar\n3. Mostrar\n4. Cambiar estado\n0. Regresar\nOpcion: ";
				cin >> opcionSolicitud;
				if (opcionSolicitud == 1)
				{
					string codigo, idCliente, codigoPaquete, idColaborador, destino, fecha;
					cout << "Codigo: "; cin >> codigo;
					if (centro->getListaSolicitudes()->buscar(codigo) != nullptr)
					{
						cout << "Ya existe esa solicitud.\n";
						break;
					}
					cout << "Identificacion del cliente: "; cin >> idCliente;
					cout << "Codigo del paquete: "; cin >> codigoPaquete;
					cout << "Identificacion del colaborador: "; cin >> idColaborador;
					Cliente* cliente = centro->getListaClientes()->buscar(idCliente);
					Paquete* paquete = centro->getListaPaquetes()->buscar(codigoPaquete);
					Colaborador* colaborador = centro->getListaColaboradores()->buscar(idColaborador);
					if (cliente == nullptr || paquete == nullptr || colaborador == nullptr)
					{
						cout << "Cliente, paquete o colaborador no encontrado.\n";
						break;
					}
					cin.ignore();
					cout << "Destino: "; getline(cin, destino);
					cout << "Fecha de solicitud: "; getline(cin, fecha);
					centro->getListaSolicitudes()->insertarSolicitud(new SolicitudEnvio(codigo, cliente, paquete, colaborador, centro->getCodigo(), destino, fecha));
				}
				else if (opcionSolicitud == 2)
				{
					string codigo;
					cout << "Codigo: "; cin >> codigo;
					NodoSolicitud* nodo = centro->getListaSolicitudes()->buscar(codigo);
					if (nodo != nullptr) nodo->getDato()->mostrarSolicitud();
					else cout << "Solicitud no encontrada.\n";
				}
				else if (opcionSolicitud == 3)
					centro->getListaSolicitudes()->mostrarSolicitudes();
				else if (opcionSolicitud == 4)
				{
					string codigo, estado, fecha;
					cout << "Codigo: "; cin >> codigo;
					NodoSolicitud* nodo = centro->getListaSolicitudes()->buscar(codigo);
					if (nodo != nullptr)
					{
						string anterior = nodo->getDato()->getEstado();
						cout << "Nuevo estado: "; cin >> estado;
						nodo->getDato()->setEstado(estado);
						cout << "Fecha del cambio: "; cin >> fecha;
						bitacora.insertarBitacora(new Bitacora(anterior, estado, fecha, nodo->getDato()->getResponsable()));
					}
					else cout << "Solicitud no encontrada.\n";
				}
			} while (opcionSolicitud != 0);
			break;
		}

		case 7:
		{
			string codigoCentro;
			cout << "Codigo del centro: "; cin >> codigoCentro;
			CentroDistribucion* centro = centros.buscar(codigoCentro);
			if (centro == nullptr)
			{
				cout << "Centro no encontrado.\n";
				break;
			}

			int opcionDespacho = 0;
			do
			{
				cout << "\n--- DESPACHOS ---\n1. Crear desde solicitud\n2. Buscar\n3. Mostrar\n4. Finalizar entrega\n0. Regresar\nOpcion: ";
				cin >> opcionDespacho;
				if (opcionDespacho == 1)
				{
					string codigo, codigoSolicitud, fecha, hora;
					cout << "Codigo del despacho: "; cin >> codigo;
					if (centro->getListaDespachos()->buscar(codigo) != nullptr)
					{
						cout << "Ya existe ese despacho.\n";
						break;
					}
					cout << "Codigo de solicitud: "; cin >> codigoSolicitud;
					NodoSolicitud* nodo = centro->getListaSolicitudes()->buscar(codigoSolicitud);
					if (nodo == nullptr)
					{
						cout << "Solicitud no encontrada.\n";
						break;
					}
					SolicitudEnvio* solicitud = nodo->getDato();
					cout << "Fecha: "; cin >> fecha;
					cout << "Hora: "; cin >> hora;
					centro->getListaDespachos()->insertarDespacho(new Despacho(codigo, solicitud, solicitud->getPaquete(), solicitud->getSoliCliente(), solicitud->getResponsable(), centro->getCodigo(), solicitud->getDestinoEntrega(), fecha, hora));
					solicitud->getPaquete()->setEstado("En tránsito");
					solicitud->setEstado("En despacho");
					bitacora.insertarBitacora(new Bitacora("Pendiente", "En despacho", fecha, solicitud->getResponsable()));
				}
				else if (opcionDespacho == 2)
				{
					string codigo;
					cout << "Codigo: "; cin >> codigo;
					NodoDespacho* nodo = centro->getListaDespachos()->buscar(codigo);
					if (nodo != nullptr) nodo->getDato()->mostrarDespacho();
					else cout << "Despacho no encontrado.\n";
				}
				else if (opcionDespacho == 3)
					centro->getListaDespachos()->mostrarDespachos();
				else if (opcionDespacho == 4)
				{
					string codigo, fecha;
					cout << "Codigo del despacho: "; cin >> codigo;
					NodoDespacho* nodo = centro->getListaDespachos()->buscar(codigo);
					if (nodo != nullptr)
					{
						Despacho* despacho = nodo->getDato();
						if (despacho->finalizarEntrega(despacho, despacho->getPaquete()))
						{
							cout << "Fecha de entrega: "; cin >> fecha;
							bitacora.insertarBitacora(new Bitacora("En proceso", "Finalizado", fecha, despacho->getResponsable()));
							despacho->getSolicitudAsociada()->setEstado("Entregada");
							cout << "Entrega finalizada.\n";
						}
						else cout << "El despacho no se puede finalizar en su estado actual.\n";
					}
					else cout << "Despacho no encontrado.\n";
				}
			} while (opcionDespacho != 0);
			break;
		}

		case 8:
		{
			cout << "\n--- CENTROS ---\n";
			centros.mostrarCentros();
			cout << "\n--- BITACORA ---\n";
			bitacora.mostrarBitacora();
			string codigoCentro;
			cout << "Codigo del centro para ver sus listas (0 para volver): "; cin >> codigoCentro;
			if (codigoCentro != "0")
			{
				CentroDistribucion* centro = centros.buscar(codigoCentro);
				if (centro != nullptr)
				{
					cout << "\nCLIENTES\n"; centro->getListaClientes()->mostrarTodos();
					cout << "COLABORADORES\n"; centro->getListaColaboradores()->mostrar();
					cout << "BODEGAS\n"; centro->getListaBodegas()->mostrar();
					cout << "PAQUETES\n"; centro->getListaPaquetes()->mostrar();
					cout << "SOLICITUDES\n"; centro->getListaSolicitudes()->mostrarSolicitudes();
					cout << "DESPACHOS\n"; centro->getListaDespachos()->mostrarDespachos();
				}
				else cout << "Centro no encontrado.\n";
			}
			break;
		}

		case 9:
			cout << "Saliendo del sistema.\n";
			break;

		default:
			cout << "Opcion no valida.\n";
		}
	} while (opcion != 9);

	return 0;
}
