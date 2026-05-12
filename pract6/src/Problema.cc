/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file Problema.cc
 * @brief Implementación de la clase Problema para representar una instancia del Maximum Diversity Problem.
 */

#include "Problema.h"

#include <cmath>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <utility>

#include "Utilidades.h"

/**
 * @brief Constructor por defecto de la clase Problema.
 */
Problema::Problema() = default;

/**
 * @brief Constructor de la clase Problema que carga la instancia desde un archivo.
 * @param rutaFichero Ruta del archivo que contiene la instancia.
 */
Problema::Problema(const std::string& rutaFichero) {
    if (!cargarDesdeFichero(rutaFichero)) {
        throw std::runtime_error("No se ha podido cargar la instancia: " +
                                 rutaFichero);
    }
}

/**
 * @brief Carga una instancia del problema desde un archivo de texto.
 * El formato esperado es n es el número de elementos, k es la dimensión de cada elemento, y
 * cada línea siguiente contiene las coordenadas de un elemento.
 *
 * @param rutaFichero Ruta del archivo a cargar.
 * @return true si la carga se ha realizado correctamente, false en caso contrario.
 */
bool Problema::cargarDesdeFichero(const std::string& rutaFichero) {
    std::ifstream archivo(rutaFichero);
    if (!archivo) {
        return false;
    }

    // Lee el número de elementos y la dimensión de cada elemento desde la primera línea del archivo.
    int numeroElementos = 0;
    int dimension = 0;
    archivo >> numeroElementos >> dimension;
    if (!archivo || numeroElementos <= 0 || dimension <= 0) {
        return false;
    }

    std::string linea;
    std::getline(archivo, linea);

    // Lee las coordenadas de los elementos, sustituyendo comas por puntos y convirtiendo a números.
    std::vector<std::vector<double>> nuevosElementos;
    nuevosElementos.reserve(static_cast<std::size_t>(numeroElementos));

    // Lee cada línea del archivo, procesa las coordenadas y las almacena en el vector de elementos.
    while (static_cast<int>(nuevosElementos.size()) < numeroElementos &&
           std::getline(archivo, linea)) {
        if (linea.empty()) {
            continue;
        }
        // Sustituye comas por puntos para asegurar la correcta interpretación de los números decimales.
        linea = utilidades::sustituirCaracter(linea, ',', '.');
        std::istringstream iss(linea);
        std::vector<double> coords;
        coords.reserve(static_cast<std::size_t>(dimension));

        std::string token;
        // Lee cada coordenada de la línea, convirtiéndola a double y almacenándola en el vector de coordenadas del elemento.
        while (iss >> token) {
            coords.push_back(utilidades::aDouble(token));
        }

        // Si el número de coordenadas leídas no coincide con la dimensión esperada, se considera que la carga ha fallado.
        if (static_cast<int>(coords.size()) != dimension) {
            return false;
        }
        nuevosElementos.push_back(std::move(coords));
    }

    // Si el número de elementos leídos no coincide con el número esperado, se considera que la carga ha fallado.
    if (static_cast<int>(nuevosElementos.size()) != numeroElementos) {
        return false;
    }

    // Se asignan los valores a los miembros de la clase.
    n_ = numeroElementos;
    k_ = dimension;
    elementos_ = std::move(nuevosElementos);
    precomputarDistancias();
    return true;
}

/**
 * @brief Devuelve el número de elementos en el problema.
 * @return Número de elementos.
 */
int Problema::numeroElementos() const { return n_; }

/**
 * @brief Devuelve la dimensión de cada elemento.
 * @return Dimensión de los elementos.
 */
int Problema::dimension() const { return k_; }

/**
 * @brief Devuelve el vector de coordenadas del elemento indicado por su índice.
 * @param indice Índice del elemento en base 0.
 * @return Vector de coordenadas del elemento.
 * @throws std::out_of_range si el índice está fuera del rango válido.
 */
const std::vector<double>& Problema::elemento(int indice) const {
    if (indice < 0 || indice >= n_) {
        throw std::out_of_range("Indice de elemento fuera de rango");
    }
    return elementos_.at(static_cast<std::size_t>(indice));
}

/**
 * @brief Devuelve la distancia euclídea entre dos elementos dados por sus índices.
 * @param i Índice del primer elemento en base 0.
 * @param j Índice del segundo elemento en base 0.
 * @return Distancia euclídea entre los dos elementos.
 * @throws std::out_of_range si alguno de los índices está fuera del rango válido.
 */
double Problema::distancia(int i, int j) const {
    if (i < 0 || j < 0 || i >= n_ || j >= n_) {
        throw std::out_of_range("Indice de distancia fuera de rango");
    }
    return distancias_.at(static_cast<std::size_t>(i))
                     .at(static_cast<std::size_t>(j));
}

/**
 * @brief Indica si la instancia del problema está cargada correctamente.
 * @return true si la instancia es válida, false en caso contrario.
 */
bool Problema::esValido() const {
    return n_ > 0 && k_ > 0 &&
           static_cast<int>(elementos_.size()) == n_ &&
           static_cast<int>(distancias_.size()) == n_;
}

/**
 * @brief Calcula la distancia euclídea entre dos vectores de coordenadas.
 * @param a Primer vector de coordenadas.
 * @param b Segundo vector de coordenadas.
 * @return Distancia euclídea entre los dos vectores.
 */
double Problema::distanciaEuclidea(const std::vector<double>& a,
                                   const std::vector<double>& b) {
    double suma = 0.0;
    for (std::size_t i = 0; i < a.size(); ++i) {
        const double dif = a[i] - b[i];
        suma += dif * dif;
    }
    return std::sqrt(suma);
}

/**
 * @brief Precomputa la matriz de distancias entre todos los pares de elementos para acelerar el acceso posterior.
 */
void Problema::precomputarDistancias() {
    distancias_.assign(static_cast<std::size_t>(n_),
                       std::vector<double>(static_cast<std::size_t>(n_), 0.0));

    // Calcula la distancia euclídea entre cada par de elementos y almacena el resultado en la matriz de distancias.
    for (int i = 0; i < n_; ++i) {
        for (int j = i + 1; j < n_; ++j) {
            const double d = distanciaEuclidea(elementos_[i], elementos_[j]);
            distancias_[static_cast<std::size_t>(i)][static_cast<std::size_t>(j)] = d;
            distancias_[static_cast<std::size_t>(j)][static_cast<std::size_t>(i)] = d;
        }
    }
}