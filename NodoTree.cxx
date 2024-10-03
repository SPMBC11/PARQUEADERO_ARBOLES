#include "nodoTree.h"
#include <algorithm> // std::max
#include <cmath>     // std::abs

// Función para calcular la altura de un nodo
int nodoTree::calcularAltura() {
    // La altura ya está almacenada en el nodo, así que solo retornamos su valor
    return this ? altura : 0;
}

// Función para verificar si el nodo (y su subárbol) está balanceado
bool nodoTree::estaBalanceado() {
    if (this == nullptr) {
        return true;  // Un árbol vacío está balanceado
    }

    int alturaIzquierda = (Izquierda == nullptr) ? 0 : Izquierda->calcularAltura();
    int alturaDerecha = (Derecha == nullptr) ? 0 : Derecha->calcularAltura();

    // Verificar si la diferencia entre las alturas es mayor que 1
    if (std::abs(alturaIzquierda - alturaDerecha) > 1) {
        return false;
    }

    // Verificar si ambos subárboles están balanceados
    return (Izquierda == nullptr || Izquierda->estaBalanceado()) &&
           (Derecha == nullptr || Derecha->estaBalanceado());
}
