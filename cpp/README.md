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

```
cpp/
├── AnalysisModule.h         # Declaración de funciones de análisis (info, head, describe, corr y guardar en TXT)
├── AnalysisModule.cpp       # Implementación del módulo de análisis
├── ConversionModule.h       # Declaración de funciones para conversión a estructuras y manejo de archivos binarios
├── ConversionModule.cpp     # Implementación de conversión a estructuras, escritura y lectura del binario
├── DataTransformer.h        # Declaración de funciones para leer el CSV y cargarlo en memoria
├── DataTransformer.cpp      # Implementación de la lectura del CSV y transformación a tabla
├── EnvLoader.h              # Declaración de la función para cargar variables de entorno desde un archivo .env
├── EnvLoader.cpp            # Implementación de la carga del archivo .env
├── SFTPClient.h             # Declaración de la clase SFTPClient (conexión SFTP y extracción del CSV)
├── SFTPClient.cpp           # Implementación de SFTPClient usando libcurl
└── pipeline.cpp             # Main que orquesta todo el pipeline, mide tiempos y muestra el menú interactivo
```

## Requisitos

- **Compilador C++** que soporte C++11 (por ejemplo, g++).
- **libcurl** instalado en el sistema (para la extracción SFTP).
- Un archivo **.env** en la raíz del proyecto con las siguientes variables (ejemplo):

  ```
  SFTP_URL=sftp://8.tcp.ngrok.io:13819/home/desarrollo/Admission_Predict.csv
  SFTP_USER=desarrollo
  SFTP_PASSWORD=your_actual_password
  ```

- Las carpetas **data/** (para archivos generados) se crearán automáticamente si no existen.

## Flujo de Trabajo

1. **Extracción:**
   - Se carga el archivo `.env` y se leen las variables de entorno.
   - Se conecta al servidor SFTP y se descarga el CSV.
   - Se mide el tiempo de extracción.

2. **Transformación:**
   - Se convierte el CSV a una tabla en memoria.
   - Se mide el tiempo de lectura y transformación.

3. **Menú Interactivo de Análisis:**
   - Se muestra un menú que permite ver:
     - Información básica (info)
     - Líneas específicas (head, según la cantidad solicitada)
     - Estadísticas descriptivas (describe)
     - Matriz de correlación (corr)
   - El usuario selecciona opciones y visualiza los resultados en la terminal.
   - Se espera que el usuario presione Enter para continuar.

4. **Guardar Análisis:**
   - Se guardan las estadísticas (describe y corr) en un archivo TXT dentro de `data/`.

5. **Conversión y Escritura Binaria:**
   - Se convierte la tabla en un arreglo de estructuras `Student`.
   - Se escribe el arreglo en un archivo binario en `data/`.
   - Se miden los tiempos de conversión y escritura.

6. **Lectura del Binario:**
   - Se lee el archivo binario y se muestra el head y tail de los registros.
   - Se mide el tiempo de lectura.

7. **Finalización:**
   - Se muestra un mensaje de finalización del pipeline y se finaliza el programa.

## Compilación y Ejecución

Desde la raíz del proyecto, compila el pipeline ejecutando:

```bash
g++ -std=c++11 -o pipeline cpp/EnvLoader.cpp cpp/SFTPClient.cpp cpp/DataTransformer.cpp cpp/AnalysisModule.cpp cpp/ConversionModule.cpp cpp/pipeline.cpp -lcurl
```

Luego, ejecuta:

```bash
./pipeline
```

Sigue las instrucciones en pantalla, utilizando el menú interactivo para revisar cada sección, y presiona Enter entre etapas para continuar.

---