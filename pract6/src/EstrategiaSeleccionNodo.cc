/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file EstrategiaSeleccionNodo.cc
 * @brief Implementación de la clase EstrategiaSeleccionNodo para decidir el orden de expansión de nodos en el algoritmo de ramificación y poda.
 */

#include "EstrategiaSeleccionNodo.h"

/**
 * @brief Compara dos nodos para determinar cuál es mejor según la estrategia de selección.
 * @param a Primer nodo.
 * @param b Segundo nodo.
 * @return true si el primer nodo es mejor que el segundo, false en caso contrario.
 */
bool EstrategiaMenorCotaSuperior::mejor(const Nodo& a, const Nodo& b) const {
    if (a.cotaSuperior == b.cotaSuperior) {
        return a.seleccion.size() > b.seleccion.size();
    }
    return a.cotaSuperior < b.cotaSuperior;
}

/**
 * @brief Devuelve el nombre de la estrategia de menor cota superior.
 * @return Nombre descriptivo de la estrategia.
 */
std::string EstrategiaMenorCotaSuperior::nombre() const {
    return "BB_min_cota_superior";
}

/**
 * @brief Compara dos nodos para determinar cuál es mejor según la estrategia de selección.
 * @param a Primer nodo.
 * @param b Segundo nodo.
 * @return true si el primer nodo es mejor que el segundo, false en caso contrario.
 */
bool EstrategiaMayorCotaSuperior::mejor(const Nodo& a, const Nodo& b) const {
    if (a.cotaSuperior == b.cotaSuperior) {
        return a.seleccion.size() > b.seleccion.size();
    }
    return a.cotaSuperior > b.cotaSuperior;
}

/**
 * @brief Devuelve el nombre de la estrategia de mayor cota superior.
 * @return Nombre descriptivo de la estrategia.
 */
std::string EstrategiaMayorCotaSuperior::nombre() const {
    return "BB_max_cota_superior";
}