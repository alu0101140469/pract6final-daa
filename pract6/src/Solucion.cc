/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Solucion.cc
 * @brief Implementación de la clase Solucion para almacenar los resultados de los algoritmos de selección de elementos.
 */

#include "Solucion.h"

#include <utility>

#include "Utilidades.h"

/**
 * @brief Constructor por defecto de la clase Solucion.
 */
Solucion::Solucion() = default;

/**
 * @brief Constructor de la clase Solucion que inicializa la selección y el valor objetivo.
 * @param seleccion Selección de índices en base 0.
 * @param valor Valor objetivo asociado a la selección.
 */
Solucion::Solucion(std::vector<int> seleccion, double valor)
    : seleccion_(std::move(seleccion)), valor_(valor) {}

/**
 * @brief Devuelve la selección almacenada.
 * @return Vector de índices seleccionados.
 */
const std::vector<int>& Solucion::seleccion() const { return seleccion_; }

/**
 * @brief Devuelve el valor objetivo.
 * @return Valor de la solución.
 */
double Solucion::valor() const { return valor_; }

/**
 * @brief Devuelve el tiempo de ejecución.
 * @return Tiempo en milisegundos.
 */
double Solucion::tiempoMilisegundos() const { return tiempoMs_; }

/**
 * @brief Devuelve el número de nodos generados.
 * @return Número de nodos generados.
 */
std::size_t Solucion::nodosGenerados() const { return nodosGenerados_; }

/**
 * @brief Establece la selección.
 * @param seleccion Selección de índices en base 0.
 */
void Solucion::establecerSeleccion(std::vector<int> seleccion) {
    seleccion_ = std::move(seleccion);
}

/**
 * @brief Establece el valor objetivo.
 * @param valor Valor objetivo.
 */
void Solucion::establecerValor(double valor) { valor_ = valor; }

/**
 * @brief Establece el tiempo de ejecución.
 * @param milisegundos Tiempo en milisegundos.
 */
void Solucion::establecerTiempoMilisegundos(double milisegundos) { tiempoMs_ = milisegundos; }

/**
 * @brief Establece el número de nodos generados.
 * @param nodos Número de nodos generados.
 */
void Solucion::establecerNodosGenerados(std::size_t nodos) { nodosGenerados_ = nodos; }

/**
 * @brief Devuelve la selección como una cadena de texto formateada.
 * @return Cadena con la selección, por ejemplo "{0, 2, 5}".
 */
std::string Solucion::seleccionComoTexto() const {
    return utilidades::indicesATexto(seleccion_);
}