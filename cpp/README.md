# Pipeline ETL en C++

Este proyecto implementa un pipeline de Extracción, Transformación y Carga (ETL) en C++ de forma modular. El pipeline realiza las siguientes tareas:

1. **Extracción:**
   - Se conecta a un servidor SFTP utilizando credenciales definidas en un archivo `.env`.
   - Se extrae un archivo CSV remoto usando libcurl.

2. **Transformación:**
   - Se lee el contenido del CSV (cadena de texto) y se convierte en una tabla (vector de vector de `std::string`).
   - Se limpia el encabezado (si es necesario) y se almacena la información en memoria.

3. **Análisis Interactivo:**
   - Se muestra un menú interactivo que permite al usuario elegir entre:
     1. Información básica (número de filas, columnas y nombres de columnas).
     2. Leer líneas específicas (el usuario indica cuántas líneas desea ver, mostrando el "head").
     3. Estadísticas descriptivas (describe) para cada columna numérica.
     4. Matriz de correlación (corr) entre las columnas numéricas.
   - El usuario puede seleccionar las opciones y visualizar el resultado en la terminal en un formato similar a un DataFrame.

4. **Guardar Estadísticas:**
   - Se guarda en un archivo TXT (en la carpeta `data/`) el análisis (describe y matriz de correlación).

5. **Conversión y Escritura Binaria:**
   - Se convierte la tabla (omitiendo el encabezado) en un arreglo de estructuras `Student` (cada estructura contiene: serial, GRE, TOEFL, University Rating, SOP, LOR, CGPA, Research y Chance of Admit).
   - Se guarda este arreglo de estructuras en un archivo binario dentro de la carpeta `data/`.

6. **Lectura y Visualización del Binario:**
   - Se lee el archivo binario y se muestran en la terminal los registros iniciales (head) y finales (tail) de los estudiantes.

7. **Medición de Tiempos y Pausas:**
   - Se mide el tiempo de ejecución de cada etapa utilizando la librería `<chrono>`.
   - Entre cada etapa se pausa la ejecución (esperando que el usuario presione Enter) para permitir la revisión de la salida.

## Estructura de Directorios

La estructura de la carpeta **cpp** es la siguiente:

