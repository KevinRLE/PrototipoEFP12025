//Implementacion de archivos binarios Kevin Lopez 21/05/2025
#include <iostream>
#include <fstream>
#include "Usuario.h"
#include "Bitacora.h"
using namespace std;

usuarios usuarioRegistrado;

int main() {
        // Verificar si el archivo binario de usuarios existe
    ifstream archivoUsuarios("Usuarios.dat", ios::binary);
    if (!archivoUsuarios.is_open()) {
        cout << "\nNo se encontró el archivo de usuarios.\n";
        cout << "Debes registrar al menos un usuario para iniciar el sistema.\n\n";
        usuarioRegistrado.agregarUsuarios();
    }
    archivoUsuarios.close();


    bool accesoUsuarios = false;
    char intentarDeNuevo;

    do {
        accesoUsuarios = usuarioRegistrado.loginUsuarios();

        if (!accesoUsuarios) {
            cout << "\nAutenticación fallida. ¿Deseas intentar de nuevo? (S/N): ";
            cin >> intentarDeNuevo;
            intentarDeNuevo = toupper(intentarDeNuevo);
        }

    } while (!accesoUsuarios && intentarDeNuevo == 'S');

    if (!accesoUsuarios) {
        cout << "\nNo se pudo acceder al sistema. Cerrando...\n";
        return 0;
    }

    bitacora bit;
    string nombreUsuario = usuarioRegistrado.getNombre();

    int opcionGeneral;
    do {
        cout << "\n=========== MENÚ GENERAL ===========\n";
        cout << "Usuario: " << nombreUsuario << "\n";
        cout << "1. Catalogo\n";
        cout << "2. Informe\n";
        cout << "3. Seguridad\n";
        cout << "4. Salir de sesion\n";
        cout << "====================================\n";
        cout << "Seleccione una opción: ";
        cin >> opcionGeneral;


        switch (opcionGeneral) {
            case 1:
                usuarioRegistrado.menuUsuarios();
                bit.insertar(nombreUsuario, 1, "Catálogo", "Acceso al submenú de Catalogos");
                break;

            case 2: {
                int opcionProcesos;
                usuarioRegistrado.consultarUsuarios();
                bit.insertar(nombreUsuario, 2, "Informes", "Revisión de informes");
                break;
            }

            case 3:
                bit.menu();
                bit.insertar(nombreUsuario, 2003, "Informes", "Revisión de bitácora");
                break;

            case 4:
                cout << "\nCerrando sesión...\n";
                break;

            default:
                cout << "\nOpción inválida. Intenta de nuevo.\n";
                system("pause");
        }

    } while (opcionGeneral != 4);

    cout << "* Hasta la próxima *\n";
    return 0;
}
