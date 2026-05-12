/**
 * @author Daniel Palenzuela Álvarez alu0101140469
 * @file main.cc
 * @brief Programa principal para ejecutar los algoritmos de selección de elementos.
 * Ejecutar: ./run_all.sh
 */

#include <iostream>
#include <memory>
#include <stdexcept>
#include <string>
#include <filesystem>

#include "AlgoritmoRamificacionPoda.h"
#include "AlgoritmoVoraz.h"
#include "Utilidades.h"

namespace {

/**
 * @brief Muestra el uso correcto del programa.
 * @param nombrePrograma Nombre del ejecutable.
 */
void mostrarUso(const char* nombrePrograma) {
    std::cerr << "Ejecución:\n"
              << "  " << nombrePrograma
              << " --instance <fichero> --m <entero> --algorithm <greedy|bb> [--strategy <min|max>]\n";
}

/**
 * @brief Obtiene el valor de un argumento específico de la línea de comandos.
 * @param argc Número de argumentos.
 * @param argv Vector de argumentos.
 * @param clave Clave del argumento a buscar, por ejemplo "--instance".
 * @return Valor asociado a la clave, o una cadena vacía si no se encuentra.
 */
std::string obtenerArgumento(int argc, char* argv[], const std::string& clave) {
    for (int i = 1; i + 1 < argc; ++i) {
        if (std::string(argv[i]) == clave) {
            return argv[i + 1];
        }
    }
    return {};
}

/**
 * @brief Verifica si un argumento específico está presente en la línea de comandos.
 * @param argc Número de argumentos.
 * @param argv Vector de argumentos.
 * @param clave Clave del argumento a buscar, por ejemplo "--instance".
 * @return true si el argumento está presente, false en caso contrario.
 */
bool tieneArgumento(int argc, char* argv[], const std::string& clave) {
    for (int i = 1; i < argc; ++i) {
        if (std::string(argv[i]) == clave) {
            return true;
        }
    }
    return false;
}

}

/**
 * @brief Función principal del programa.
 *
 * El programa espera recibir los siguientes argumentos
 * --instance <fichero>: Ruta al fichero de entrada con la instancia del problema.
 * --m <entero>: Número de elementos a seleccionar.
 * --algorithm <greedy|bb>: Algoritmo a ejecutar (voraz o ramificación y poda).
 * [--strategy <min|max>]: Estrategia de selección de nodos para ramificación y poda (solo si se selecciona bb).
 *
 * El programa carga la instancia, ejecuta el algoritmo seleccionado y muestra los resultados en formato CSV.
 */
int main(int argc, char* argv[]) {
    try {
        // Verifica que se han proporcionado los argumentos necesarios.
        if (!tieneArgumento(argc, argv, "--instance") ||
            !tieneArgumento(argc, argv, "--m") ||
            !tieneArgumento(argc, argv, "--algorithm")) {
            mostrarUso(argv[0]);
            return 1;
        }

        // Obtiene los valores de los argumentos proporcionados.
        const std::string ruta = obtenerArgumento(argc, argv, "--instance");
        const std::string mTexto = obtenerArgumento(argc, argv, "--m");
        const std::string algoritmo = obtenerArgumento(argc, argv, "--algorithm");
        const std::string estrategia = obtenerArgumento(argc, argv, "--strategy");

        // Verifica que los argumentos no estén vacíos.
        if (ruta.empty() || mTexto.empty() || algoritmo.empty()) {
            mostrarUso(argv[0]);
            return 1;
        }

        // Convierte el valor de m a entero y carga la instancia del problema.
        const int m = std::stoi(mTexto);
        Problema problema(ruta);

        // Verifica que la instancia se ha cargado correctamente.
        std::unique_ptr<Algoritmo> alg;

        // Crea el algoritmo seleccionado según los argumentos proporcionados.
        if (algoritmo == "greedy") { // Algoritmo voraz.
            alg = std::make_unique<AlgoritmoVoraz>(problema, m);
        } else if (algoritmo == "bb") { // Algoritmo de ramificación y poda.
            if (estrategia.empty()) {
                throw std::runtime_error("La ramificación y poda requiere --strategy min|max");
            }
            if (estrategia == "min") { // Estrategia de menor cota superior.
                alg = std::make_unique<AlgoritmoRamificacionPoda>(
                    problema, m, std::make_unique<EstrategiaMenorCotaSuperior>());
            } else if (estrategia == "max") { // Estrategia de mayor cota superior.
                alg = std::make_unique<AlgoritmoRamificacionPoda>(
                    problema, m, std::make_unique<EstrategiaMayorCotaSuperior>());
            } else { // Estrategia no reconocida.
                throw std::runtime_error("Estrategia no reconocida: use min o max");
            }
        } else { // Algoritmo no reconocido.
            throw std::runtime_error("Algoritmo no reconocido: use greedy o bb");
        }

        // Ejecuta el algoritmo y obtiene la solución.
        const Solucion solucion = alg->ejecutar();

        // Extrae el nombre de la instancia a partir de la ruta del archivo para mostrarlo en los resultados.
        const std::string nombreInstancia = std::filesystem::path(ruta).filename().string();

        // Muestra los resultados en formato CSV con las métricas relevantes.
        std::cout << "algorithm=" << alg->nombre()
                  << ",instance=" << nombreInstancia
                  << ",n=" << problema.numeroElementos()
                  << ",K=" << problema.dimension()
                  << ",m=" << m
                  << ",z=" << utilidades::formatearDouble(solucion.valor(), 6)
                  << ",S=" << solucion.seleccionComoTexto()
                  << ",CPU_ms=" << utilidades::formatearDouble(solucion.tiempoMilisegundos(), 3)
                  << ",nodes=" << solucion.nodosGenerados()
                  << '\n';
        return 0;
    } catch (const std::exception& ex) {
        // Si ocurre cualquier error durante la ejecución, se muestra un mensaje de error descriptivo.
        std::cerr << "Error: " << ex.what() << '\n';
        return 2;
    }
}