#include <iostream>
#include <cstdlib>
#include <sys/stat.h>
#include <sys/types.h>
#include <chrono>
#include <limits>
#include "EnvLoader.h"
#include "SFTPClient.h"
#include "DataTransformer.h"
#include "AnalysisModule.h"
#include "ConversionModule.h"

using namespace std;
using namespace std::chrono;

// Función para esperar a que el usuario presione Enter
void waitForEnter(const string& prompt = "Presione Enter para continuar...") {
    cout << prompt;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
}

int main() {
    cout << "==== Proceso ETL Iniciado ====" << endl;
    
    // Paso 1: Conexión y extracción
    auto t1 = high_resolution_clock::now();
    loadEnv(".env");
    const char* url = getenv("SFTP_URL");
    const char* user = getenv("SFTP_USER");
    const char* password = getenv("SFTP_PASSWORD");
    if (!url || !user || !password) {
        cerr << "Variables de entorno no encontradas." << endl;
        return 1;
    }
    SFTPClient client(url, user, password);
    string csvData = client.extractData();
    if (csvData.empty()) {
        cerr << "Error: No se extrajeron datos." << endl;
        return 1;
    }
    auto t2 = high_resolution_clock::now();
    double extractionTime = duration_cast<duration<double>>(t2 - t1).count();
    cout << "Extracción completada en " << extractionTime << " segundos." << endl;
    waitForEnter();
    
    // Paso 2: Lectura del CSV y carga en memoria
    auto t3 = high_resolution_clock::now();
    vector<vector<string>> table = readCSV(csvData);
    auto t4 = high_resolution_clock::now();
    double csvReadTime = duration_cast<duration<double>>(t4 - t3).count();
    cout << "Lectura del CSV completada en " << csvReadTime << " segundos." << endl;
    waitForEnter();
    
    // Paso 3: Menú interactivo para análisis
    int option = -1;
    while (option != 0) {
        cout << "\nMenú de Análisis:" << endl;
        cout << "1. Información (info)" << endl;
        cout << "2. Leer líneas (indique cuántas líneas desea ver)" << endl;
        cout << "3. Descripción (describe)" << endl;
        cout << "4. Matriz de correlación (corr)" << endl;
        cout << "0. Salir del menú de análisis" << endl;
        cout << "Seleccione una opción: ";
        cin >> option;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        if (option == 1) {
            // Mostrar información básica
            printInfo(table);
        } else if (option == 2) {
            int nLines;
            cout << "Ingrese el número de líneas a mostrar: ";
            cin >> nLines;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            printHead(table, nLines);
        } else if (option == 3) {
            printDescribe(table);
        } else if (option == 4) {
            printCorrelation(table);
        } else if (option == 0) {
            cout << "Saliendo del menú de análisis..." << endl;
        } else {
            cout << "Opción inválida. Intente nuevamente." << endl;
        }
    }
    
    // Paso 4: Guardar estadísticas (describe y corr) en un archivo TXT
    auto t5 = high_resolution_clock::now();
    string analysisFile = "data/transformacion_resultados.txt";
    // Asegurar que exista la carpeta "data"
    struct stat st = {0};
    if (stat("data", &st) == -1) {
        mkdir("data", 0755);
    }
    saveAnalysisToTxt(table, analysisFile);
    auto t6 = high_resolution_clock::now();
    double analysisTime = duration_cast<duration<double>>(t6 - t5).count();
    cout << "Estadísticas guardadas en " << analysisFile << " en " << analysisTime << " segundos." << endl;
    waitForEnter();
    
    // Paso 5: Convertir a estructuras y guardar en binario
    auto t7 = high_resolution_clock::now();
    vector<Student> students = convertTableToStudents(table);
    auto t8 = high_resolution_clock::now();
    double conversionTime = duration_cast<duration<double>>(t8 - t7).count();
    cout << "Conversión a estructuras completada en " << conversionTime << " segundos." << endl;
    
    auto t9 = high_resolution_clock::now();
    string binFile = "data/Admission_Predict_new.bin";
    if (writeStudentsBinary(students, binFile))
        cout << "Archivo binario guardado: " << binFile << endl;
    else
        cerr << "Error al guardar el archivo binario." << endl;
    auto t10 = high_resolution_clock::now();
    double binWriteTime = duration_cast<duration<double>>(t10 - t9).count();
    cout << "Escritura del archivo binario completada en " << binWriteTime << " segundos." << endl;
    waitForEnter();
    
    // Paso 6: Leer el binario y mostrar head y tail
    auto t11 = high_resolution_clock::now();
    vector<Student> studentsRead;
    if (readStudentsBinary(binFile, studentsRead))
        printBinaryHeadTail(studentsRead);
    else
        cerr << "Error al leer el archivo binario." << endl;
    auto t12 = high_resolution_clock::now();
    double binReadTime = duration_cast<duration<double>>(t12 - t11).count();
    cout << "Lectura del archivo binario completada en " << binReadTime << " segundos." << endl;
    waitForEnter();
    
    cout << "==== Proceso ETL Finalizado ====" << endl;
    return 0;
}
