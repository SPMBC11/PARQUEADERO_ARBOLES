#include "Carro.h"

// Constructor
Carro::Carro(const std::string& _placa, const std::string& _color, const std::string& _tipo, 
             const std::string& _marca, bool _servPublico, 
             const std::chrono::system_clock::time_point& _horaEntrada)
    : placa(_placa), color(_color), tipo(_tipo), marca(_marca), servPublico(_servPublico), horaEntrada(_horaEntrada) {}

// Métodos de acceso (getters) y otros métodos

std::string Carro::getPlaca() const {
    return placa;
}

std::string Carro::getColor() const {
    return color;
}

std::string Carro::getTipo() const {
    return tipo;
}

std::string Carro::getMarca() const {
    return marca;
}

bool Carro::esServPublico() const {
    return servPublico;
}

std::chrono::system_clock::time_point Carro::getHoraEntrada() const {
    return horaEntrada;
}
