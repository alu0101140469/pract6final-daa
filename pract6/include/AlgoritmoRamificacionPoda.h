/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file AlgoritmoRamificacionPoda.h
 * @brief Definición de la clase AlgoritmoRamificacionPoda para resolver el MDP mediante ramificación y poda.
 */

#ifndef ALGORITMORAMIFICACIONPODA_H
#define ALGORITMORAMIFICACIONPODA_H

#include <memory>
#include <queue>

#include "Algoritmo.h"
#include "EstrategiaSeleccionNodo.h"

/**
 * @brief Algoritmo exacto de ramificación y poda para el MDP.
 *
 * Aplica una cota superior basada en la suma de las mejores contribuciones de
 * los elementos candidatos y usa una estrategia intercambiable para decidir el
 * orden de expansión de nodos.
 */
class AlgoritmoRamificacionPoda : public Algoritmo {
 public:
    /**
     * @brief Construye el algoritmo de ramificación y poda.
     * @param problema Instancia del problema.
     * @param m Tamaño del subconjunto buscado.
     * @param estrategia Estrategia de selección de nodos.
     */
    AlgoritmoRamificacionPoda(const Problema& problema, int m,
                              std::unique_ptr<EstrategiaSeleccionNodo> estrategia);

 protected:
    /**
     * @brief Ejecuta el algoritmo exacto.
     * @return Solución óptima encontrada.
     */
    Solucion resolver() override;

 private:
    std::unique_ptr<EstrategiaSeleccionNodo> estrategia_;  // Estrategia usada.
    std::size_t nodosGenerados_{0};                        // Nodos generados.

    /**
     * @brief Calcula la cota superior del nodo indicado.
     * @param nodo Nodo parcial.
     * @return Cota superior estimada.
     */
    double calcularCotaSuperior(const Nodo& nodo) const;

    /**
     * @brief Construye una solución voraz para fijar la cota inferior inicial.
     * @return Solución heurística inicial.
     */
    Solucion solucionInicialVoraz() const;
};

#endif