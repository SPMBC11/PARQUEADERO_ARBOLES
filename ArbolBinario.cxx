#include "ArbolBinario.h"
#include <chrono>
#include <cmath>  // Para std::abs
#include <iostream>
using namespace std;

// Implementación del constructor
ArbolBinario::ArbolBinario() : raiz(nullptr) {}

// Implementación del método insertar
void ArbolBinario::insertar(Carro* carro) {
    raiz = insertarAVL(raiz, carro);
}

// Implementación del método eliminar
void ArbolBinario::eliminar(const std::string& placa) {
    raiz = eliminarRecu(raiz, placa);
}

// Implementación del método calcularGanancias
double ArbolBinario::calcularGanancias(double pagoPorMinuto) {
    return calcularGananciasRecursivo(raiz, pagoPorMinuto);
}

// Implementación del método buscar
Carro* ArbolBinario::buscar(const std::string& placa) {
    nodoTree* nodo = buscarRecurso(raiz, placa);
    if (nodo != nullptr) {
        return nodo->carro;
    } else {
        return nullptr;
    }
}

// Implementación del recorrido en preorden
void ArbolBinario::preOrden() {
    preOrdenRecu(raiz);
}

void ArbolBinario::preOrdenRecu(nodoTree* nodo) {
    if (nodo == nullptr) {
        return;
    }
    cout <<"Placa: "<< nodo->carro->getPlaca() <<" Marca: "<<nodo->carro->getMarca()<<" Tipo: "<<nodo->carro->getTipo()<< " "<<endl;
    preOrdenRecu(nodo->Izquierda);
    preOrdenRecu(nodo->Derecha);
    
}

// Implementación de insertarAVL con balanceo
nodoTree* ArbolBinario::insertarAVL(nodoTree* nodo, Carro* carro) {
    // Realizar la inserción normal del árbol binario
    if (nodo == nullptr) {
        return new nodoTree(carro);
    }
    if (carro->getPlaca() < nodo->carro->getPlaca()) {
        nodo->Izquierda = insertarAVL(nodo->Izquierda, carro);
    } else if (carro->getPlaca() > nodo->carro->getPlaca()) {
        nodo->Derecha = insertarAVL(nodo->Derecha, carro);
    } else {
        return nodo;  // No se permiten duplicados
    }

    // Actualizar altura del nodo actual
    nodo->altura = 1 + std::max(altura(nodo->Izquierda), altura(nodo->Derecha));

    // Obtener el factor de balance para verificar si está balanceado
    int balance = getFactorBalance(nodo);

    // Casos de rotaciones para balancear el árbol AVL

    // Caso 1 - Rotación derecha
    if (balance > 1 && carro->getPlaca() < nodo->Izquierda->carro->getPlaca()) {
        return rotacionDerecha(nodo);
    }

    // Caso 2 - Rotación izquierda
    if (balance < -1 && carro->getPlaca() > nodo->Derecha->carro->getPlaca()) {
        return rotacionIzquierda(nodo);
    }

    // Caso 3 - Rotación izquierda-derecha
    if (balance > 1 && carro->getPlaca() > nodo->Izquierda->carro->getPlaca()) {
        nodo->Izquierda = rotacionIzquierda(nodo->Izquierda);
        return rotacionDerecha(nodo);
    }

    // Caso 4 - Rotación derecha-izquierda
    if (balance < -1 && carro->getPlaca() < nodo->Derecha->carro->getPlaca()) {
        nodo->Derecha = rotacionDerecha(nodo->Derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

// Implementación de eliminarRecu con balanceo
nodoTree* ArbolBinario::eliminarRecu(nodoTree* nodo, const std::string& placa) {
    if (nodo == nullptr) {
        return nodo;
    }

    if (placa < nodo->carro->getPlaca()) {
        nodo->Izquierda = eliminarRecu(nodo->Izquierda, placa);
    } else if (placa > nodo->carro->getPlaca()) {
        nodo->Derecha = eliminarRecu(nodo->Derecha, placa);
    } else {
        // Nodo con el carro a eliminar encontrado
        if (nodo->Izquierda == nullptr) {
            nodoTree* temp = nodo->Derecha;
            delete nodo;
            return temp;
        } else if (nodo->Derecha == nullptr) {
            nodoTree* temp = nodo->Izquierda;
            delete nodo;
            return temp;
        }

        nodoTree* temp = nodo->Derecha;
        while (temp && temp->Izquierda != nullptr) {
            temp = temp->Izquierda;
        }

        nodo->carro = temp->carro;
        nodo->Derecha = eliminarRecu(nodo->Derecha, temp->carro->getPlaca());
    }

    if (nodo == nullptr) {
        return nodo;
    }

    // Actualizar la altura del nodo actual
    nodo->altura = 1 + std::max(altura(nodo->Izquierda), altura(nodo->Derecha));

    // Obtener el factor de balance del nodo actual
    int balance = getFactorBalance(nodo);

    // Caso 1 - Rotación derecha
    if (balance > 1 && getFactorBalance(nodo->Izquierda) >= 0) {
        return rotacionDerecha(nodo);
    }

    // Caso 2 - Rotación izquierda
    if (balance < -1 && getFactorBalance(nodo->Derecha) <= 0) {
        return rotacionIzquierda(nodo);
    }

    // Caso 3 - Rotación izquierda-derecha
    if (balance > 1 && getFactorBalance(nodo->Izquierda) < 0) {
        nodo->Izquierda = rotacionIzquierda(nodo->Izquierda);
        return rotacionDerecha(nodo);
    }

    // Caso 4 - Rotación derecha-izquierda
    if (balance < -1 && getFactorBalance(nodo->Derecha) > 0) {
        nodo->Derecha = rotacionDerecha(nodo->Derecha);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}
// Implementación para verificar si el árbol está balanceado
bool ArbolBinario::estaBalanceado() {
    return estaBalanceadoRecu(raiz);
}

bool ArbolBinario::estaBalanceadoRecu(nodoTree* nodo) {
    if (nodo == nullptr) {
        return true;
    }

    int balance = getFactorBalance(nodo);
    
    // Verificar si el nodo está balanceado y si los subárboles están balanceados
    return (std::abs(balance) <= 1) && estaBalanceadoRecu(nodo->Izquierda) && estaBalanceadoRecu(nodo->Derecha);
}


// Funciones auxiliares para balanceo

int ArbolBinario::getFactorBalance(nodoTree* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return altura(nodo->Izquierda) - altura(nodo->Derecha);
}

nodoTree* ArbolBinario::rotacionDerecha(nodoTree* y) {
    nodoTree* x = y->Izquierda;
    nodoTree* T2 = x->Derecha;

    // Rotación
    x->Derecha = y;
    y->Izquierda = T2;

    // Actualizar alturas
    y->altura = 1 + std::max(altura(y->Izquierda), altura(y->Derecha));
    x->altura = 1 + std::max(altura(x->Izquierda), altura(x->Derecha));

    return x;
}

nodoTree* ArbolBinario::rotacionIzquierda(nodoTree* x) {
    nodoTree* y = x->Derecha;
    nodoTree* T2 = y->Izquierda;

    // Rotación
    y->Izquierda = x;
    x->Derecha = T2;

    // Actualizar alturas
    x->altura = 1 + std::max(altura(x->Izquierda), altura(x->Derecha));
    y->altura = 1 + std::max(altura(y->Izquierda), altura(y->Derecha));

    return y;
}

// Implementación de calcularGananciasRecursivo
double ArbolBinario::calcularGananciasRecursivo(nodoTree* nodo, double pagoPorMinuto) {
    if (nodo == nullptr) return 0.0;

    double ganancias = 0.0;

    // Calcular el tiempo real que el carro ha estado en el parqueadero
    auto tiempoActual = std::chrono::system_clock::now();
    auto tiempoEntrada = nodo->carro->getHoraEntrada();
    auto duracion = std::chrono::duration_cast<std::chrono::minutes>(tiempoActual - tiempoEntrada).count();

    double montoPagar = 0.0;
   /*
    if (nodo->carro->getTipo() == "Moto") {
        montoPagar = duracion * (pagoPorMinuto / 2);  // Pago reducido para motos
    } else if (nodo->carro->esServPublico()) {
        montoPagar = duracion * pagoPorMinuto;  // Pago completo para servicio público
    } else {
        montoPagar = duracion * pagoPorMinuto;  // Pago completo para carros particulares
    }
   */

if (nodo->carro->esServPublico()== false){
    montoPagar= duracion* pagoPorMinuto;
}

    ganancias += montoPagar;
    ganancias += calcularGananciasRecursivo(nodo->Izquierda, pagoPorMinuto);
    ganancias += calcularGananciasRecursivo(nodo->Derecha, pagoPorMinuto);

    return ganancias;
}
// Implementación de buscarRecurso
nodoTree* ArbolBinario::buscarRecurso(nodoTree* nodo, const std::string& placa) {
    if (nodo == nullptr || nodo->carro->getPlaca() == placa) {
        return nodo;
    }

    if (placa < nodo->carro->getPlaca()) {
        return buscarRecurso(nodo->Izquierda, placa);
    } else {
        return buscarRecurso(nodo->Derecha, placa);
    }
}

// Implementación del recorrido en postorden
void ArbolBinario::postOrden() {
    if (raiz != nullptr) {
        cout << "RAIZ: " << raiz->carro->getPlaca() << " Marca: " << raiz->carro->getMarca() << " Tipo: " << raiz->carro->getTipo() << endl;
    } else {
        cout << "El árbol está vacío." << endl;
    }
    postOrdenRecu(raiz);  // Llamada al recorrido postorden
}

void ArbolBinario::postOrdenRecu(nodoTree* nodo) {
    if (nodo == nullptr) {
        return;
    }

    // Recorrer subárbol izquierdo
    postOrdenRecu(nodo->Izquierda);
    
    // Recorrer subárbol derecho
    postOrdenRecu(nodo->Derecha);
    
    // Mostrar datos del nodo actual (postorden)
    cout << "Placa: " << nodo->carro->getPlaca()
         << " Marca: " << nodo->carro->getMarca()
         << " Tipo: " << nodo->carro->getTipo() << endl;
}


// Función para obtener la altura de un nodo
int ArbolBinario::altura(nodoTree* nodo) {
    if (nodo == nullptr) {
        return 0;
    }
    return nodo->altura;
}
