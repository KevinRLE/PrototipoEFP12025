//Implementacion de archivos binarios Kevin Lopez 21/05/2025
#include <iostream>
#include <fstream>
#include "Usuario.h"
#include "Inventario.h"
#include "Bitacora.h"
#include "Menu.h"
using namespace std;

usuarios usuarioRegistrado;
Menu menu;

int main() {
        // Verificar si el archivo binario de usuarios existe
    ifstream archivoUsuarios("Usuarios.dat", ios::binary);
    if (!archivoUsuarios.is_open()) {
        cout << "\nNo se encontr� el archivo de usuarios.\n";
        cout << "Debes registrar al menos un usuario para iniciar el sistema.\n\n";
        usuarioRegistrado.agregarUsuarios();
    }
    archivoUsuarios.close();


    bool accesoUsuarios = false;
    char intentarDeNuevo;

    do {
        accesoUsuarios = usuarioRegistrado.loginUsuarios();

        if (!accesoUsuarios) {
            cout << "\nAutenticaci�n fallida. �Deseas intentar de nuevo? (S/N): ";
            cin >> intentarDeNuevo;
            intentarDeNuevo = toupper(intentarDeNuevo);
        }

    } while (!accesoUsuarios && intentarDeNuevo == 'S');

    if (!accesoUsuarios) {
        cout << "\nNo se pudo acceder al sistema. Cerrando...\n";
        return 0;
    }

    Inventario inventario;
    Facturacion factura;
    bitacora bit;
    string nombreUsuario = usuarioRegistrado.getNombre();

    int opcionGeneral;
    do {
        system("cls");
        cout << "\n=========== MEN� GENERAL ===========\n";
        cout << "Usuario: " << nombreUsuario << "\n";
        cout << "1. Catalogo\n";
        cout << "2. Procesos\n";
        cout << "3. Informes\n";
        cout << "4. Salir de sesion\n";
        cout << "====================================\n";
        cout << "Seleccione una opci�n: ";
        cin >> opcionGeneral;

        switch (opcionGeneral) {
            case 1:
                menu.mostrarOpciones(inventario, factura, nombreUsuario);
                bit.insertar(nombreUsuario, 1999, "Cat�logo", "Acceso al submen� de inventario");
                break;

            case 2: {
                int opcionProcesos;
                do {
                    system("cls");
                    cout << "\n=========== MEN� DE PROCESOS ===========\n";
                    cout << "1. Facturacion\n";
                    cout << "2. Gestion de usuarios\n";
                    cout << "3. Volver al men� general\n";
                    cout << "========================================\n";
                    cout << "Seleccione una opci�n: ";
                    cin >> opcionProcesos;

                    switch (opcionProcesos) {
                        case 1:
                            factura.generarFactura(inventario);
                            bit.insertar(nombreUsuario, 2101, "Procesos", "Acceso a facturaci�n");
                            break;
                        case 2:
                            usuarioRegistrado.menuUsuarios();
                            bit.insertar(nombreUsuario, 2102, "Procesos", "Acceso a gesti�n de usuarios");
                            break;
                        case 3:
                            cout << "Volviendo al men� general...\n";
                            break;
                        default:
                            cout << "Opci�n inv�lida. Intente nuevamente.\n";
                            system("pause");
                    }
                } while (opcionProcesos != 3);
                break;
            }

            case 3:
                bit.menu();
                bit.insertar(nombreUsuario, 2003, "Informes", "Revisi�n de bit�cora");
                break;

            case 4:
                cout << "\nCerrando sesi�n...\n";
                break;

            default:
                cout << "\nOpci�n inv�lida. Intenta de nuevo.\n";
                system("pause");
        }

    } while (opcionGeneral != 4);

    cout << "* Hasta la pr�xima *\n";
    return 0;
}
