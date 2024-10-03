#ifndef CARRO_H
#define CARRO_H

#include <string>
#include <chrono>

class Carro {
private:
    std::string placa;
    std::string color;
    std::string tipo;
    std::string marca;
    bool servPublico;
    std::chrono::system_clock::time_point horaEntrada;

public:
    // Constructor
    Carro(const std::string& _placa, const std::string& _color, const std::string& _tipo, 
          const std::string& _marca, bool _servPublico, 
          const std::chrono::system_clock::time_point& _horaEntrada);

    // Métodos de acceso (getters) y otros métodos
    std::string getPlaca() const;
    std::string getColor() const;
    std::string getTipo() const;
    std::string getMarca() const;
    bool esServPublico() const;
    std::chrono::system_clock::time_point getHoraEntrada() const;
};

#endif // CARRO_H
