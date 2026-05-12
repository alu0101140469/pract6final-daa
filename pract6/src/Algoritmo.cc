/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Algoritmo.cc
 * @brief Implementación de la clase base Algoritmo para resolver problemas de selección de elementos.
 */

#include "Algoritmo.h"

#include <chrono>
#include <stdexcept>
#include <utility>

/**
 * @brief Constructor de la clase Algoritmo.
 * @param problema Instancia del problema a resolver.
 * @param m Número de elementos a seleccionar.
 * @param nombre Nombre del algoritmo.
 */
Algoritmo::Algoritmo(const Problema& problema, int m, std::string nombre)
    : problema_(problema), m_(m), nombre_(std::move(nombre)) {
    // Validación básica de la instancia y del valor de m.
    if (!problema_.esValido()) {
        throw std::runtime_error("La instancia del problema no es válida");
    }
    if (m_ <= 0 || m_ > problema_.numeroElementos()) {
        throw std::runtime_error("El valor de m no es válido");
    }
}

/**
 * @brief Ejecuta el algoritmo y mide su tiempo de ejecución.
 * @return Solución obtenida por el algoritmo.
 */
Solucion Algoritmo::ejecutar() {
    // Mide el tiempo de ejecución del método resolver() y almacena el resultado en la solución.
    const auto inicio = std::chrono::steady_clock::now();
    Solucion solucion = resolver();
    const auto fin = std::chrono::steady_clock::now();
    const auto duracion =
        std::chrono::duration_cast<std::chrono::duration<double, std::milli>>(fin - inicio);
    solucion.establecerTiempoMilisegundos(duracion.count());
    return solucion;
}

// Implementación de los métodos de acceso.
const std::string& Algoritmo::nombre() const { return nombre_; }
const Problema& Algoritmo::problema() const { return problema_; }
int Algoritmo::m() const { return m_; }