#ifndef Parqueadero_H
#define Parqueadero_H

#include "ArbolBinario.h"
#include "Carro.h"
#include <string>

class Parqueadero {
private:
    std::string id;
    std::string nombre;
    int capacidad;
    double pagoXmin;
    ArbolBinario arbolCarros;

public:
    Parqueadero(const std::string& _id, const std::string& _nombre, int _capacidad, double _pagoXmin);

    // Función para agregar un carro al árbol binario
    void agregarCarro(Carro* carro);

    // Función para calcular las ganancias de los vehículos
    double calcularGanancias();

    // Función para retirar un vehículo y devolver el valor a pagar
    double retirar(const std::string& placa);

    // Función para mostrar el árbol en preorden
    void mostrarArbolPreOrden();

    // Función para mostrar el árbol en postorden
    void mostrarArbolPostOrden();

    // Función para verificar si el árbol está balanceado
    bool estaBalanceado();

    // Getters para obtener información del parqueadero
    std::string getId() const;
    std::string getNombre() const;
    int getCapacidad() const;
    double getPagoPorMinuto() const;
};

#endif
