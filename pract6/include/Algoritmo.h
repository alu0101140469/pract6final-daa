/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Algoritmo.h
 * @brief Definición de la clase base Algoritmo para resolver problemas de selección de elementos.
 */

#ifndef ALGORITMO_H
#define ALGORITMO_H

#include <string>

#include "Problema.h"
#include "Solucion.h"

/**
 * @brief Clase base abstracta para algoritmos de resolución.
 *
 * Implementa el patrón Template Method mediante ejecutar(), que mide el tiempo
 * y delega la lógica concreta en resolver().
 */
class Algoritmo {
 public:
    /**
     * @brief Construye un algoritmo asociado a una instancia y a un valor m.
     * @param problema Instancia del problema.
     * @param m Tamaño del subconjunto buscado.
     * @param nombre Nombre descriptivo del algoritmo.
     */
    Algoritmo(const Problema& problema, int m, std::string nombre);

    /**
     * @brief Destructor virtual.
     */
    virtual ~Algoritmo() = default;

    /**
     * @brief Ejecuta el algoritmo y devuelve la solución obtenida.
     * @return Solución calculada.
     */
    Solucion ejecutar();

    /**
     * @brief Devuelve el nombre del algoritmo.
     * @return Nombre legible.
     */
    const std::string& nombre() const;

 protected:
    /**
     * @brief Implementación concreta del algoritmo.
     * @return Solución calculada.
     */
    virtual Solucion resolver() = 0;

    /**
     * @brief Devuelve la instancia del problema.
     * @return Referencia constante al problema.
     */
    const Problema& problema() const;

    /**
     * @brief Devuelve el valor m.
     * @return Tamaño del subconjunto buscado.
     */
    int m() const;

 private:
    const Problema& problema_;  // Instancia del problema.
    int m_;                     // Tamaño del subconjunto buscado.
    std::string nombre_;        // Nombre del algoritmo.
};

#endif