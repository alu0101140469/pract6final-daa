/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file AlgoritmoVoraz.h
 * @brief Definición de la clase AlgoritmoVoraz para resolver el MDP mediante un enfoque constructivo voraz.
 */

#ifndef ALGORITMOVORAZ_H
#define ALGORITMOVORAZ_H

#include <vector>

#include "Algoritmo.h"

/**
 * @brief Algoritmo constructivo voraz para el Maximum Diversity Problem.
 *
 * Selecciona primero el elemento más alejado del centroide global y después
 * añade sucesivamente el elemento más alejado del centroide de la selección.
 */
class AlgoritmoVoraz : public Algoritmo {
 public:
    /**
     * @brief Construye el algoritmo voraz.
     * @param problema Instancia del problema.
     * @param m Tamaño del subconjunto buscado.
     */
    AlgoritmoVoraz(const Problema& problema, int m);

 protected:
    /**
     * @brief Ejecuta la construcción voraz.
     * @return Solución heurística obtenida.
     */
    Solucion resolver() override;

 private:
    /**
     * @brief Calcula el centroide de una selección.
     * @param indices Índices seleccionados en base 0.
     * @return Coordenadas del centroide.
     */
    std::vector<double> centroide(const std::vector<int>& indices) const;

    /**
     * @brief Obtiene el índice del candidato más alejado del centroide.
     * @param candidatos Candidatos todavía disponibles.
     * @param centro Coordenadas del centroide.
     * @return Índice del elemento elegido.
     */
    int masAlejadoDelCentro(const std::vector<int>& candidatos,
                            const std::vector<double>& centro) const;
};

#endif