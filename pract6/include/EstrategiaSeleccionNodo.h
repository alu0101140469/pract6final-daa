/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file EstrategiaSeleccionNodo.h
 * @brief Definición de la clase EstrategiaSeleccionNodo para decidir el orden de expansión de nodos en el algoritmo de ramificación y poda.
 */

#ifndef ESTRATEGIASELECCIONNODO_H
#define ESTRATEGIASELECCIONNODO_H

#include <string>
#include <vector>

/**
 * @brief Nodo parcial del árbol de ramificación y poda.
 */
struct Nodo {
    std::vector<int> seleccion;  // Índices seleccionados en base 0.
    int siguienteIndice{0};      // Primer índice candidato disponible.
    double valorParcial{0.0};    // Valor acumulado de la parte fija.
    double cotaSuperior{0.0};    // Cota superior estimada.
};

/**
 * @brief Estrategia para decidir qué nodo se expande primero.
 */
class EstrategiaSeleccionNodo {
 public:
    /**
     * @brief Destructor virtual.
     */
    virtual ~EstrategiaSeleccionNodo() = default;

    /**
     * @brief Indica si el primer nodo debe preceder al segundo.
     * @param a Primer nodo.
     * @param b Segundo nodo.
     * @return true si a tiene prioridad sobre b.
     */
    virtual bool mejor(const Nodo& a, const Nodo& b) const = 0;

    /**
     * @brief Devuelve el nombre de la estrategia.
     * @return Nombre descriptivo.
     */
    virtual std::string nombre() const = 0;
};

/**
 * @brief Estrategia que prioriza la cota superior más pequeña.
 */
class EstrategiaMenorCotaSuperior final : public EstrategiaSeleccionNodo {
 public:
    bool mejor(const Nodo& a, const Nodo& b) const override;
    std::string nombre() const override;
};

/**
 * @brief Estrategia que prioriza la cota superior más grande.
 */
class EstrategiaMayorCotaSuperior final : public EstrategiaSeleccionNodo {
 public:
    bool mejor(const Nodo& a, const Nodo& b) const override;
    std::string nombre() const override;
};

#endif