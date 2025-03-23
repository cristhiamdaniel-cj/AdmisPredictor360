#!/bin/bash
# Script para organizar el proyecto siguiendo buenas prácticas

# Verifica que estamos en el directorio raíz del proyecto (ajusta según convenga)
echo "Organizando el proyecto..."

# Crear la estructura de directorios
mkdir -p src/main/java/com/miempresa/prediccion
mkdir -p src/main/resources/images
mkdir -p src/test/java/com/miempresa/prediccion
mkdir -p cpp
mkdir -p python

# Mover archivos Java a src/main/java/com/miempresa/prediccion/
if [ -f DesktopApp.java ]; then
    mv DesktopApp.java src/main/java/com/miempresa/prediccion/
    echo "Movido DesktopApp.java"
fi

if [ -f ModelParams.java ]; then
    mv ModelParams.java src/main/java/com/miempresa/prediccion/
    echo "Movido ModelParams.java"
fi

# Mover el archivo pom.xml a la raíz (ya debería estar en la raíz, pero por si acaso)
if [ -f pom.xml ]; then
    echo "pom.xml ya se encuentra en la raíz."
fi

# Mover archivos de recursos a src/main/resources/
if [ -f model.json ]; then
    mv model.json src/main/resources/
    echo "Movido model.json a src/main/resources/"
fi

if [ -f Admission_Predict.bin ]; then
    mv Admission_Predict.bin src/main/resources/
    echo "Movido Admission_Predict.bin a src/main/resources/"
fi

# Mover la carpeta images a src/main/resources/
if [ -d images ]; then
    mv images src/main/resources/
    echo "Movida la carpeta images a src/main/resources/"
fi

# Mover archivos Python a la carpeta python/
if [ -f modelo.py ]; then
    mv modelo.py python/
    echo "Movido modelo.py a python/"
fi

if [ -f generate_happy.py ]; then
    mv generate_happy.py python/
    echo "Movido generate_happy.py a python/"
fi

# Mover archivos C++ a la carpeta cpp/
if [ -f extraccion.cpp ]; then
    mv extraccion.cpp cpp/
    echo "Movido extraccion.cpp a cpp/"
fi

if [ -f pipeline_data.cpp ]; then
    mv pipeline_data.cpp cpp/
    echo "Movido pipeline_data.cpp a cpp/"
fi

if [ -f lectura_bin.cpp ]; then
    mv lectura_bin.cpp cpp/
    echo "Movido lectura_bin.cpp a cpp/"
fi

echo "Estructura del proyecto organizada exitosamente."
