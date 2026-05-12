/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file AlgoritmoRamificacionPoda.cc
 * @brief Implementación de la clase AlgoritmoRamificacionPoda para resolver el MDP mediante ramificación y poda.
 * El algoritmo explora un árbol de soluciones parciales, aplicando una cota superior para podar ramas que no pueden superar la mejor solución encontrada. 
 * Se puede configurar la estrategia de selección de nodos para priorizar la expansión de aquellos con mayor o menor cota superior.
 */

#include "AlgoritmoRamificacionPoda.h"

#include <algorithm>
#include <stdexcept>
#include <utility>

#include "AlgoritmoVoraz.h"

namespace {

/**
 * @brief Estructura para comparar nodos según la estrategia de selección.
 */
struct ComparadorNodo {
    // Constructor que recibe la estrategia de selección de nodos.
    explicit ComparadorNodo(const EstrategiaSeleccionNodo* estrategia)
        : estrategia_(estrategia) {}

    // Sobrecarga del operador de comparación para la prioridad en la cola.
    bool operator()(const Nodo& a, const Nodo& b) const {
        return estrategia_->mejor(b, a);
    }

    // Puntero a la estrategia de selección de nodos.
    const EstrategiaSeleccionNodo* estrategia_;
};

}

/**
 * @brief Constructor de la clase AlgoritmoRamificacionPoda.
 * @param problema Instancia del problema a resolver.
 * @param m Número de elementos a seleccionar.
 * @param estrategia Estrategia de selección de nodos.
 */
AlgoritmoRamificacionPoda::AlgoritmoRamificacionPoda(
        const Problema& problema, int m,
        std::unique_ptr<EstrategiaSeleccionNodo> estrategia)
    : Algoritmo(problema, m, "Ramificacion_y_Poda"),
      estrategia_(std::move(estrategia)) {
    // Validación de la estrategia de selección de nodos.
    if (!estrategia_) {
        throw std::runtime_error("La estrategia de nodos no puede ser nula");
    }
}

/**
 * @brief Obtiene la solución inicial utilizando el algoritmo voraz.
 * @return Solución inicial encontrada.
 */
Solucion AlgoritmoRamificacionPoda::solucionInicialVoraz() const {
    AlgoritmoVoraz voraz(problema(), m());
    return voraz.ejecutar();
}

/**
 * @brief Calcula la cota superior del nodo indicado.
 * @param nodo Nodo parcial del árbol de búsqueda.
 * @return Cota superior estimada para el nodo.
 */
double AlgoritmoRamificacionPoda::calcularCotaSuperior(const Nodo& nodo) const {
    // La cota superior se calcula sumando el valor parcial del nodo con las mejores contribuciones de los candidatos restantes.
    const int n = problema().numeroElementos();
    const int restantes = m() - static_cast<int>(nodo.seleccion.size());
    // Si no quedan candidatos, la cota es el valor parcial actual.
    if (restantes <= 0) {
        return nodo.valorParcial;
    }

    // Calcula las contribuciones de los candidatos restantes y ordena para obtener las mejores.
    std::vector<double> valores;
    valores.reserve(static_cast<std::size_t>(n - nodo.siguienteIndice));

    // Para cada candidato, calcula su contribución al valor objetivo sumando las distancias a los elementos 
    // ya seleccionados y las mejores distancias a los candidatos no seleccionados.
    for (int v = nodo.siguienteIndice; v < n; ++v) {
        double zSel = 0.0;
        for (int s : nodo.seleccion) {
            zSel += problema().distancia(s, v);
        }

        // Calcula las distancias a los candidatos no seleccionados para estimar la contribución máxima posible.
        std::vector<double> distanciasCandidatas;
        distanciasCandidatas.reserve(static_cast<std::size_t>(n - nodo.siguienteIndice - 1));
        for (int u = nodo.siguienteIndice; u < n; ++u) {
            if (u == v) {
                continue;
            }
            distanciasCandidatas.push_back(problema().distancia(v, u));
        }

        // Ordena las distancias de mayor a menor para sumar las mejores contribuciones posibles.
        std::sort(distanciasCandidatas.begin(), distanciasCandidatas.end(),
                  std::greater<double>());

        double zUnsel = 0.0;
        // Suma las mejores contribuciones de los candidatos no seleccionados, limitando al número de elementos restantes.
        for (int i = 0; i < restantes - 1 &&
                        i < static_cast<int>(distanciasCandidatas.size()); ++i) {
            zUnsel += distanciasCandidatas[static_cast<std::size_t>(i)];
        }
        zUnsel *= 0.5;
        valores.push_back(zSel + zUnsel);
    }

    // Ordena las contribuciones de los candidatos restantes para sumar las mejores posibles.
    std::sort(valores.begin(), valores.end(), std::greater<double>());

    // La cota superior es la suma del valor parcial del nodo con las mejores contribuciones de los candidatos restantes.
    double cota = nodo.valorParcial;
    for (int i = 0; i < restantes && i < static_cast<int>(valores.size()); ++i) {
        cota += valores[static_cast<std::size_t>(i)];
    }
    return cota;
}

/**
 * @brief Ejecuta el algoritmo de ramificación y poda para encontrar la solución óptima.
 * @return Solución óptima encontrada.
 */
Solucion AlgoritmoRamificacionPoda::resolver() {
    const int n = problema().numeroElementos();
    const int mObjetivo = m();

    // Obtiene una solución inicial utilizando el algoritmo voraz para establecer una cota inferior.
    Solucion mejor = solucionInicialVoraz();
    // Si la solución inicial no es válida (por ejemplo, si m es mayor que el número de elementos), 
    // se establece una solución vacía con valor 0.
    if (mejor.seleccion().size() != static_cast<std::size_t>(mObjetivo)) {
        mejor.establecerSeleccion({});
        mejor.establecerValor(0.0);
    }

    // Cola de prioridad para los nodos abiertos, ordenada según la estrategia de selección de nodos.
    std::priority_queue<Nodo, std::vector<Nodo>, ComparadorNodo> abiertos(
        ComparadorNodo(estrategia_.get()));

    // Nodo raíz del árbol de búsqueda, con selección vacía y cota superior calculada.
    Nodo raiz;
    raiz.siguienteIndice = 0;
    raiz.valorParcial = 0.0;
    raiz.cotaSuperior = calcularCotaSuperior(raiz);
    abiertos.push(raiz);
    nodosGenerados_ = 1;

    // Bucle principal de exploración del árbol de búsqueda.
    while (!abiertos.empty()) {
        Nodo actual = abiertos.top();
        abiertos.pop();

        // Si la cota superior del nodo actual no supera el valor de la mejor solución encontrada, se poda la rama.
        if (actual.cotaSuperior <= mejor.valor()) {
            continue;
        }

        // Si se ha alcanzado el número de elementos objetivo, se actualiza la mejor solución si es necesario.
        const int restantes = mObjetivo - static_cast<int>(actual.seleccion.size());
        if (restantes == 0) {
            if (actual.valorParcial > mejor.valor()) {
                mejor.establecerSeleccion(actual.seleccion);
                mejor.establecerValor(actual.valorParcial);
            }
            continue;
        }

        // Genera los nodos hijos expandiendo el siguiente índice candidato y calcula su valor parcial y cota superior.
        const int ultimoPosible = n - restantes;
        for (int candidato = actual.siguienteIndice; candidato <= ultimoPosible; ++candidato) {
            Nodo hijo = actual;
            hijo.seleccion.push_back(candidato);
            hijo.siguienteIndice = candidato + 1;

            // Calcula el valor parcial del hijo sumando las distancias a los elementos ya seleccionados.
            for (int s : actual.seleccion) {
                hijo.valorParcial += problema().distancia(s, candidato);
            }

            // Si el hijo ya tiene el número de elementos objetivo, se actualiza la mejor solución si es necesario.
            if (static_cast<int>(hijo.seleccion.size()) == mObjetivo) {
                if (hijo.valorParcial > mejor.valor()) {
                    mejor.establecerSeleccion(hijo.seleccion);
                    mejor.establecerValor(hijo.valorParcial);
                }
                ++nodosGenerados_;
                continue;
            }

            // Calcula la cota superior del hijo y lo añade a la cola de abiertos si puede superar la mejor solución encontrada.
            hijo.cotaSuperior = calcularCotaSuperior(hijo);
            ++nodosGenerados_;

            // Solo se añade el hijo a la cola de abiertos si su cota superior es mejor que el valor de la mejor solución 
            // encontrada, para evitar explorar ramas que no pueden mejorar el resultado.
            if (hijo.cotaSuperior > mejor.valor()) {
                abiertos.push(std::move(hijo));
            }
        }
    }

    // Al finalizar la exploración, se establece el número de nodos generados en la solución.
    mejor.establecerNodosGenerados(nodosGenerados_);
    return mejor;
}