#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <iomanip>  // Para get_time
#include "Carro.h"
#include "Parqueadero.h"

using namespace std;

// Función para cargar vehículos desde un archivo CSV
void cargarVehiculosDesdeCSV(Parqueadero& parqueadero, const string& archivoCSV) {
    ifstream archivo(archivoCSV);
    string linea;

    if (!archivo.is_open()) {
        cerr << "Error abriendo el archivo: " << archivoCSV << endl;
        return;
    }

    while (getline(archivo, linea)) {
        stringstream ss(linea);
        string placa, color, tipo, marca, esServicioPublicoStr, horaEntradaStr;
        bool esServicioPublico;
        chrono::system_clock::time_point horaEntrada;

        // Leer y separar los campos del CSV
        getline(ss, placa, ',');
        getline(ss, color, ',');
        getline(ss, tipo, ',');
        getline(ss, marca, ',');
        getline(ss, esServicioPublicoStr, ',');
        getline(ss, horaEntradaStr, ',');

        esServicioPublico = (esServicioPublicoStr == "1");

        // Convertir la hora de entrada a un objeto time_point
        tm t = {};
        stringstream ssHora(horaEntradaStr);
        ssHora >> get_time(&t, "%Y-%m-%d %H:%M");
        time_t timeEntrada = mktime(&t);
        horaEntrada = chrono::system_clock::from_time_t(timeEntrada);

        // Crear un nuevo objeto Carro y agregarlo al parqueadero
        Carro* carro = new Carro(placa, color, tipo, marca, esServicioPublico, horaEntrada);
        parqueadero.agregarCarro(carro);
    }

    archivo.close();
}

// Función para retirar un vehículo y mostrar el monto a pagar
void retirarVehiculo(Parqueadero& parqueadero) {
    string placa;
    cout << "Ingrese la placa del vehículo que desea retirar: ";
    cin >> placa;

    double monto = parqueadero.retirar(placa);
    if (monto > 0) {
        cout << "El vehículo con placa " << placa << " debe pagar: $" << monto << endl;
    } else {
        cout << "No se encontró un vehículo con la placa " << placa << " en el parqueadero." << endl;
    }
}

// Función para mostrar el árbol en preorden
void mostrarArbolPreOrden(Parqueadero& parqueadero) {
    cout << "Mostrando el árbol en preorden: " << endl;
    parqueadero.mostrarArbolPreOrden();
}

// Función para mostrar el árbol en postorden
void mostrarArbolPostOrden(Parqueadero& parqueadero) {
    cout << "Mostrando el árbol en postorden: " << endl;
    parqueadero.mostrarArbolPostOrden();
}

// Función para verificar si el árbol está balanceado
void verificarBalance(Parqueadero& parqueadero) {
    if (parqueadero.estaBalanceado()) {
        cout << "El árbol está balanceado." << endl;
    } else {
        cout << "El árbol NO está balanceado." << endl;
    }
}

int main() {
    int opcion, parqueaderoOpcion;

    // Crear dos parqueaderos
    Parqueadero parqueadero1("P001", "Parqueadero Central", 100, 0.05);
    Parqueadero parqueadero2("P002", "Parqueadero Norte", 80, 0.07);

    // Cargar vehículos desde archivo CSV al inicio para ambos parqueaderos
    cargarVehiculosDesdeCSV(parqueadero1, "parqueadero_central.csv");
    cargarVehiculosDesdeCSV(parqueadero2, "parqueadero_norte.csv");

    do {
        cout << "---SELECCIONE EL PARQUEADERO---" << endl;
        cout << "1. Parqueadero Central" << endl;
        cout << "2. Parqueadero Norte" << endl;
        cout << "3. Salir" << endl;
        cin >> parqueaderoOpcion;

        if (parqueaderoOpcion == 1 || parqueaderoOpcion == 2) {
            Parqueadero& parqueadero = (parqueaderoOpcion == 1) ? parqueadero1 : parqueadero2;

            do {
                cout << "---MENU PARQUEADERO---" << endl;
                cout << "1. Ver ganancias del parqueadero" << endl;
                cout << "2. Retirar vehículo" << endl;
                cout << "3. Mostrar árbol en preorden" << endl;
                cout << "4. Mostrar árbol en postorden" << endl;
                cout << "5. Verificar si el árbol está balanceado" << endl;
                cout << "6. Volver al menú principal" << endl;
                cin >> opcion;

                switch (opcion) {
                    case 1: {
                        cout << "Ganancias del parqueadero: " << parqueadero.calcularGanancias() << " dólares" << endl;
                        break;
                    }
                    case 2: {
                        retirarVehiculo(parqueadero);
                        break;
                    }
                    case 3: {
                        mostrarArbolPreOrden(parqueadero);
                        break;
                    }
                    case 4: {
                        mostrarArbolPostOrden(parqueadero);
                        break;
                    }
                    case 5: {
                        verificarBalance(parqueadero);
                        break;
                    }
                    case 6: {
                        cout << "Volviendo al menú principal..." << endl;
                        break;
                    }
                    default: {
                        cout << "OPCION INVALIDA" << endl;
                        break;
                    }
                }
            } while (opcion != 6);
        } else if (parqueaderoOpcion == 3) {
            cout << "SALIENDO..." << endl;
        } else {
            cout << "OPCION INVALIDA" << endl;
        }

    } while (parqueaderoOpcion != 3);

    return 0;
}
