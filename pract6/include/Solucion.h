/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Solucion.h
 * @brief Definición de la clase Solucion para almacenar los resultados de los algoritmos de selección de elementos.
 */

#ifndef SOLUCION_H
#define SOLUCION_H

#include <cstddef>
#include <string>
#include <vector>

/**
 * @brief Almacena la solución de una instancia del problema.
 *
 * La clase guarda el subconjunto elegido, el valor objetivo y las métricas de
 * ejecución asociadas al algoritmo que la ha generado.
 */
class Solucion {
 public:
    /**
     * @brief Construye una solución vacía.
     */
    Solucion();

    /**
     * @brief Construye una solución con una selección y un valor dado.
     * @param seleccion Selección de índices en base 0.
     * @param valor Valor objetivo.
     */
    Solucion(std::vector<int> seleccion, double valor);

    /**
     * @brief Devuelve la selección almacenada.
     * @return Vector de índices seleccionados.
     */
    const std::vector<int>& seleccion() const;

    /**
     * @brief Devuelve el valor objetivo.
     * @return Valor de la solución.
     */
    double valor() const;

    /**
     * @brief Devuelve el tiempo de ejecución.
     * @return Tiempo en milisegundos.
     */
    double tiempoMilisegundos() const;

    /**
     * @brief Devuelve el número de nodos generados.
     * @return Número de nodos generados.
     */
    std::size_t nodosGenerados() const;

    /**
     * @brief Establece la selección.
     * @param seleccion Selección de índices en base 0.
     */
    void establecerSeleccion(std::vector<int> seleccion);

    /**
     * @brief Establece el valor objetivo.
     * @param valor Nuevo valor.
     */
    void establecerValor(double valor);

    /**
     * @brief Establece el tiempo de ejecución.
     * @param milisegundos Tiempo en milisegundos.
     */
    void establecerTiempoMilisegundos(double milisegundos);

    /**
     * @brief Establece el número de nodos generados.
     * @param nodos Número de nodos.
     */
    void establecerNodosGenerados(std::size_t nodos);

    /**
     * @brief Devuelve la selección en formato legible.
     * @return Cadena con los índices en base 1.
     */
    std::string seleccionComoTexto() const;

 private:
    std::vector<int> seleccion_;     // Selección de elementos.
    double valor_{0.0};              // Valor objetivo.
    double tiempoMs_{0.0};           // Tiempo de ejecución en milisegundos.
    std::size_t nodosGenerados_{0};  // Número de nodos generados.
};

#endif