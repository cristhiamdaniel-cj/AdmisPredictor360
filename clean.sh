#!/bin/bash
# Script para eliminar archivos innecesarios en el directorio raíz del proyecto

echo "Limpiando archivos y directorios que no se usan..."

# Eliminar ejecutables y otros archivos temporales
rm -f a.out extraccion lectura transformacion_resultados.txt

# Eliminar archivos compilados Java (.class) en el directorio raíz y subdirectorios
find . -maxdepth 2 -type f -name "*.class" -exec rm -f {} \;

echo "Limpieza completada."
