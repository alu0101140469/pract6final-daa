/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Problema.h
 * @brief Definición de la clase Problema para representar una instancia del Maximum Diversity Problem.
 */

#ifndef PROBLEMA_H
#define PROBLEMA_H

#include <string>
#include <vector>

/**
 * @brief Representa una instancia del Maximum Diversity Problem.
 *
 * La clase carga un fichero de texto con las coordenadas de los elementos y
 * precomputa la matriz de distancias euclídeas para acelerar los algoritmos.
 */
class Problema {
 public:
    /**
     * @brief Construye una instancia vacía.
     */
    Problema();

    /**
     * @brief Construye una instancia cargándola desde fichero.
     * @param rutaFichero Ruta del fichero de entrada.
     */
    explicit Problema(const std::string& rutaFichero);

    /**
     * @brief Carga una instancia desde fichero.
     * @param rutaFichero Ruta del fichero de entrada.
     * @return true si la lectura es correcta.
     */
    bool cargarDesdeFichero(const std::string& rutaFichero);

    /**
     * @brief Devuelve el número de elementos de la instancia.
     * @return Número de elementos.
     */
    int numeroElementos() const;

    /**
     * @brief Devuelve la dimensión de los elementos.
     * @return Dimensión de cada vector.
     */
    int dimension() const;

    /**
     * @brief Devuelve el elemento indicado.
     * @param indice Índice en base 0.
     * @return Vector de coordenadas del elemento.
     */
    const std::vector<double>& elemento(int indice) const;

    /**
     * @brief Devuelve la distancia euclídea entre dos elementos.
     * @param i Índice del primer elemento.
     * @param j Índice del segundo elemento.
     * @return Distancia entre ambos elementos.
     */
    double distancia(int i, int j) const;

    /**
     * @brief Indica si la instancia está cargada correctamente.
     * @return true si la instancia es válida.
     */
    bool esValido() const;

 private:
    int n_{};  // Número de elementos.
    int k_{};  // Dimensión de cada elemento.
    std::vector<std::vector<double>> elementos_;  // Coordenadas de los elementos.
    std::vector<std::vector<double>> distancias_;  // Matriz de distancias.

    /**
     * @brief Calcula la distancia euclídea entre dos vectores.
     * @param a Primer vector.
     * @param b Segundo vector.
     * @return Distancia euclídea.
     */
    static double distanciaEuclidea(const std::vector<double>& a,
                                    const std::vector<double>& b);

    /**
     * @brief Precomputa la matriz de distancias de la instancia.
     */
    void precomputarDistancias();
};

#endif