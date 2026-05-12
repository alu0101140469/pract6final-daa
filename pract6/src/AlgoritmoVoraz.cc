/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file AlgoritmoVoraz.cc
 * @brief Implementación de la clase AlgoritmoVoraz para resolver el MDP mediante un enfoque constructivo voraz.
 */ 

#include "AlgoritmoVoraz.h"

#include <algorithm>
#include <cmath>
#include <utility>

/**
 * @brief Constructor de la clase AlgoritmoVoraz.
 * @param problema Instancia del problema a resolver.
 * @param m Número de elementos a seleccionar.
 */
AlgoritmoVoraz::AlgoritmoVoraz(const Problema& problema, int m)
    : Algoritmo(problema, m, "Voraz") {}

/**
 * @brief Calcula el centroide de una selección.
 * @param indices Índices seleccionados en base 0.
 * @return Coordenadas del centroide.
 */
std::vector<double> AlgoritmoVoraz::centroide(const std::vector<int>& indices) const {
    const int dimension = problema().dimension();
    std::vector<double> centro(static_cast<std::size_t>(dimension), 0.0);

    // Si no hay índices seleccionados, el centroide es el vector de ceros.
    if (indices.empty()) {
        return centro;
    }

    // Suma las coordenadas de los elementos seleccionados para calcular el centroide.
    for (int indice : indices) {
        const auto& elemento = problema().elemento(indice);
        for (int d = 0; d < dimension; ++d) {
            centro[static_cast<std::size_t>(d)] += elemento[static_cast<std::size_t>(d)];
        }
    }

    // Divide por el número de elementos seleccionados para obtener el centroide.
    const double factor = 1.0 / static_cast<double>(indices.size());
    for (double& valor : centro) {
        valor *= factor;
    }
    return centro;
}

/**
 * @brief Obtiene el índice del candidato más alejado del centroide.
 * @param candidatos Candidatos todavía disponibles.
 * @param centro Coordenadas del centroide.
 * @return Índice del elemento elegido.
 */
int AlgoritmoVoraz::masAlejadoDelCentro(const std::vector<int>& candidatos,
                                        const std::vector<double>& centro) const {
    int mejorIndice = candidatos.front();
    double mejorDistancia = -1.0;

    // Para cada candidato, calcula su distancia al centroide y selecciona el que esté más alejado.
    for (int candidato : candidatos) {
        const auto& elemento = problema().elemento(candidato);
        double sumaCuadrados = 0.0;
        // Calcula la distancia euclídea entre el candidato y el centroide.
        for (int d = 0; d < problema().dimension(); ++d) {
            const double dif = elemento[static_cast<std::size_t>(d)] -
                               centro[static_cast<std::size_t>(d)];
            sumaCuadrados += dif * dif;
        }
        const double distancia = std::sqrt(sumaCuadrados);

        // Si la distancia es mejor que la mejor encontrada hasta ahora, o si es igual pero el 
        // índice del candidato es menor, se actualiza la mejor opción.
        if (distancia > mejorDistancia ||
            (std::abs(distancia - mejorDistancia) < 1e-12 && candidato < mejorIndice)) {
            mejorDistancia = distancia;
            mejorIndice = candidato;
        }
    }

    return mejorIndice;
}

/**
 * @brief Ejecuta la construcción voraz para obtener una solución heurística.
 * @return Solución heurística obtenida.
 */
Solucion AlgoritmoVoraz::resolver() {
    const int n = problema().numeroElementos();
    const int mObjetivo = m();

    // Crea una lista de candidatos con todos los índices disponibles.
    std::vector<int> candidatos(static_cast<std::size_t>(n));
    for (int i = 0; i < n; ++i) {
        candidatos[static_cast<std::size_t>(i)] = i;
    }

    // Selección voraz, primero el elemento más alejado del centroide global, 
    // luego el más alejado del centroide de la selección.
    std::vector<int> seleccion;
    seleccion.reserve(static_cast<std::size_t>(mObjetivo));

    // Calcula el centroide global considerando todos los elementos como candidatos.
    std::vector<double> centro = centroide(candidatos);
    // Mientras no se alcance el número de elementos objetivo, se selecciona el candidato más alejado del centroide.
    while (static_cast<int>(seleccion.size()) < mObjetivo) {
        const int elegido = masAlejadoDelCentro(candidatos, centro);
        seleccion.push_back(elegido);
        candidatos.erase(std::remove(candidatos.begin(), candidatos.end(), elegido),
                         candidatos.end());
        centro = centroide(seleccion);
    }

    double valor = 0.0;
    // Calcula el valor objetivo de la selección sumando las distancias entre los elementos seleccionados.
    for (std::size_t i = 0; i < seleccion.size(); ++i) {
        for (std::size_t j = i + 1; j < seleccion.size(); ++j) {
            valor += problema().distancia(seleccion[i], seleccion[j]);
        }
    }

    return Solucion(std::move(seleccion), valor);
}