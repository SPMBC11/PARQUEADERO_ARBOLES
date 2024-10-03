#ifndef ARBOLBINARIO_H
#define ARBOLBINARIO_H

#include "NodoTree.h"  // Ahora incluimos la clase nodoTree desde su archivo
#include <string>
#include <algorithm>  // Para std::max

// Definición de la clase ArbolBinario
class ArbolBinario {
private:
    nodoTree* raiz;

    // Funciones auxiliares
    nodoTree* insertarAVL(nodoTree* nodo, Carro* carro);  // Inserción con balanceo AVL
    nodoTree* eliminarRecu(nodoTree* nodo, const std::string& placa);  // Eliminación con balanceo AVL
    nodoTree* buscarRecurso(nodoTree* nodo, const std::string& placa);
    double calcularGananciasRecursivo(nodoTree* nodo, double pagoPorMinuto);
    void postOrdenRecu(nodoTree* nodo);
    void preOrdenRecu(nodoTree* nodo);  // Recorrido en preorden
    bool estaBalanceadoRecu(nodoTree* nodo);
    int altura(nodoTree* nodo);  // Función auxiliar para calcular la altura

    // Funciones de balanceo AVL
    int getFactorBalance(nodoTree* nodo);  // Función para obtener el factor de balance
    nodoTree* rotacionDerecha(nodoTree* y);  // Rotación a la derecha
    nodoTree* rotacionIzquierda(nodoTree* x);  // Rotación a la izquierda

public:
    ArbolBinario();
    void insertar(Carro* carro);  // Inserción pública
    void eliminar(const std::string& placa);  // Eliminación pública
    Carro* buscar(const std::string& placa);
    double calcularGanancias(double pagoPorMinuto);

    // Recorridos
    void postOrden();  // Recorrido en postorden
    void preOrden();   // Recorrido en preorden

    bool estaBalanceado();  // Función para verificar si el árbol está balanceado
};

#endif  // ARBOLBINARIO_H
