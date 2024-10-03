#include "Parqueadero.h"
#include "Carro.h"
#include "ArbolBinario.h"
#include <stdexcept>
#include <chrono>
#include <iostream>

// Constructor
Parqueadero::Parqueadero(const std::string& _id, const std::string& _nombre, int _capacidad, double _pagoXmin)
    : id(_id), nombre(_nombre), capacidad(_capacidad), pagoXmin(_pagoXmin) {}

// Función para agregar un carro al árbol binario
void Parqueadero::agregarCarro(Carro* carro) {
    arbolCarros.insertar(carro);
}

// Función para calcular las ganancias de todos los vehículos
double Parqueadero::calcularGanancias() {
    return arbolCarros.calcularGanancias(pagoXmin);
}

// Función para retirar un vehículo y devolver el valor a pagar
double Parqueadero::retirar(const std::string& placa) {
    Carro* carro = arbolCarros.buscar(placa);
    if (carro != nullptr) {
        // Obtener el tiempo actual y calcular el tiempo de parqueo
        auto tiempoActual = std::chrono::system_clock::now();
        auto tiempoEntrada = carro->getHoraEntrada();
        auto duracion = std::chrono::duration_cast<std::chrono::minutes>(tiempoActual - tiempoEntrada).count();

        double montoPagar = 0.0;

        // Calcular el monto a pagar según el tipo de vehículo
        if (carro->getTipo() == "Moto") {
            montoPagar = duracion * (pagoXmin / 2); // Pago reducido para motos
        } else if (carro->esServPublico()) {
            montoPagar = duracion * pagoXmin; // Pago completo para servicio público
        } else {
            montoPagar = duracion * pagoXmin; // Pago completo para carros particulares
        }

        // Eliminar el carro del árbol
        arbolCarros.eliminar(placa);
        return montoPagar;
    } else {
        // Si el carro no existe, retornamos 0
        return 0.0;
    }
}

// Función para mostrar el árbol en preorden
void Parqueadero::mostrarArbolPreOrden() {
    std::cout << "Mostrando el árbol de vehículos en preorden:" << std::endl;
    arbolCarros.preOrden();
}

// Función para mostrar el árbol en postorden
void Parqueadero::mostrarArbolPostOrden() {
    std::cout << "Mostrando el árbol de vehículos en postorden:" << std::endl;
    arbolCarros.postOrden();
}

// Función para verificar si el árbol está balanceado
bool Parqueadero::estaBalanceado() {
    return arbolCarros.estaBalanceado();
}
