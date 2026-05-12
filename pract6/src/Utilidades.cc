/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Utilidades.cc
 * @brief Implementación de las funciones auxiliares para el manejo de datos.
 */

#include "Utilidades.h"

#include <algorithm>
#include <stdexcept>

namespace utilidades {

/**
 * @brief Sustituye todas las apariciones de un carácter por otro en una cadena.
 * @param texto Cadena original.
 * @param buscado Carácter a buscar.
 * @param sustituido Carácter que reemplaza al buscado.
 * @return Nueva cadena con las sustituciones realizadas.
 */
std::string sustituirCaracter(std::string texto, char buscado, char sustituido) {
    std::replace(texto.begin(), texto.end(), buscado, sustituido);
    return texto;
}

/**
 * @brief Convierte una cadena a un número de punto flotante.
 * @param texto Cadena a convertir.
 * @return Valor numérico representado por la cadena.
 */
double aDouble(const std::string& texto) {
    try {
        return std::stod(texto);
    } catch (const std::exception& ex) {
        throw std::runtime_error("No se ha podido convertir a double: " + texto +
                                 " (" + ex.what() + ")");
    }
}

/**
 * @brief Formatea un número de punto flotante con una precisión dada.
 * @param valor Número a formatear.
 * @param precision Número de dígitos decimales.
 * @return Cadena con el número formateado.
 */
std::string formatearDouble(double valor, int precision) {
    std::ostringstream oss;
    oss << std::fixed << std::setprecision(precision) << valor;
    return oss.str();
}

/**
 * @brief Convierte un vector de enteros a una cadena de texto con formato.
 * @param indices Vector de índices a convertir.
 * @return Cadena con los índices formateados, por ejemplo "{0, 2, 5}".
 */
std::string indicesATexto(const std::vector<int>& indices) {
    std::ostringstream oss;
    oss << "{";
    for (std::size_t i = 0; i < indices.size(); ++i) {
        if (i > 0) {
            oss << ", ";
        }
        oss << (indices[i] + 1);
    }
    oss << "}";
    return oss.str();
}

}