#ifndef NODOTREE_H
#define NODOTREE_H

#include "Carro.h"

class nodoTree {
public:
    Carro* carro;
    nodoTree* Izquierda;
    nodoTree* Derecha;
    int altura;  // Atributo para almacenar la altura del nodo

    // Constructor con inicialización
    nodoTree(Carro* _Carro) : carro(_Carro), Izquierda(nullptr), Derecha(nullptr), altura(1) {}

    // Función para calcular la altura del nodo (ya no del árbol completo)
    int calcularAltura();

    // Función para verificar si el nodo (y su subárbol) está balanceado
    bool estaBalanceado();
};

#endif // NODOTREE_H
