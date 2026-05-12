#!/usr/bin/env bash
set -euo pipefail # Asegura que el script se detenga ante errores

# Determina el directorio raíz del proyecto
ROOT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$ROOT_DIR"

# Compila el proyecto
make
mkdir -p results

# Define rutas de archivos de entrada y salida
INSTANCE_DIR="$ROOT_DIR/instances"
OUTPUT_GREEDY="$ROOT_DIR/results/greedy.csv"
OUTPUT_BB_MIN="$ROOT_DIR/results/bb_min.csv"
OUTPUT_BB_MAX="$ROOT_DIR/results/bb_max.csv"

# Inicializa los archivos de salida con encabezados
: > "$OUTPUT_GREEDY"
: > "$OUTPUT_BB_MIN"
: > "$OUTPUT_BB_MAX"

# Agrega encabezados a los archivos CSV
echo "algorithm,instance,n,K,m,z,S,CPU_ms,nodes" >> "$OUTPUT_GREEDY"
echo "algorithm,instance,n,K,m,z,S,CPU_ms,nodes" >> "$OUTPUT_BB_MIN"
echo "algorithm,instance,n,K,m,z,S,CPU_ms,nodes" >> "$OUTPUT_BB_MAX"

# Ejecuta los algoritmos para cada instancia y cada valor de m
for instance in "$INSTANCE_DIR"/*.txt; do
  for m in 2 3 4 5; do
    ./bin/mdp --instance "$instance" --m "$m" --algorithm greedy >> "$OUTPUT_GREEDY"
    ./bin/mdp --instance "$instance" --m "$m" --algorithm bb --strategy min >> "$OUTPUT_BB_MIN"
    ./bin/mdp --instance "$instance" --m "$m" --algorithm bb --strategy max >> "$OUTPUT_BB_MAX"
  done
done

# Muestra un mensaje indicando que los resultados han sido generados
echo "Resultados generados en results/"