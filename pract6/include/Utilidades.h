/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Utilidades.h
 * @brief Definición de funciones auxiliares para manipulación de cadenas y conversiones.
 */

#ifndef UTILIDADES_H
#define UTILIDADES_H

#include <iomanip>
#include <sstream>
#include <string>
#include <vector>

/**
 * @brief Espacio de nombres para funciones auxiliares.
 */
namespace utilidades {

    /**
     * @brief Sustituye todas las apariciones de un carácter por otro en una cadena.
     * @param texto Cadena original.
     * @param buscado Carácter a buscar.
     * @param sustituido Carácter que reemplaza al buscado.
     * @return Nueva cadena con las sustituciones realizadas.
     */
    std::string sustituirCaracter(std::string texto, char buscado, char sustituido);
    /**
     * @brief Convierte una cadena a un número de punto flotante.
     * @param texto Cadena a convertir.
     * @return Valor numérico representado por la cadena.
     */
    double aDouble(const std::string& texto);
    /**
     * @brief Formatea un número de punto flotante con una precisión dada.
     * @param valor Número a formatear.
     * @param precision Número de dígitos decimales.
     * @return Cadena con el número formateado.
     */
    std::string formatearDouble(double valor, int precision = 4);
    /**
     * @brief Convierte un vector de enteros a una cadena de texto con formato.
     * @param indices Vector de índices a convertir.
     * @return Cadena con los índices formateados, por ejemplo "{0, 2, 5}".
     */
    std::string indicesATexto(const std::vector<int>& indices);

}

#endif