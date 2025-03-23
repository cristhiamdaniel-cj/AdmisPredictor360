#ifndef ANALYSISMODULE_H
#define ANALYSISMODULE_H

#include <string>
#include <vector>

// Imprime la información básica (info) del dataset.
void printInfo(const std::vector<std::vector<std::string>>& table);

// Imprime las primeras n filas (head) con formato tabular.
void printHead(const std::vector<std::vector<std::string>>& table, int n);

// Imprime las estadísticas descriptivas (describe) de cada columna numérica.
void printDescribe(const std::vector<std::vector<std::string>>& table);

// Imprime la matriz de correlación (corr) entre las columnas numéricas.
void printCorrelation(const std::vector<std::vector<std::string>>& table);

// Imprime todo el análisis: info, head, describe y correlación.
void analyzeAndPrint(const std::vector<std::vector<std::string>>& table);

// Guarda el análisis (resultado de analyzeAndPrint) en un archivo TXT.
void saveAnalysisToTxt(const std::vector<std::vector<std::string>>& table, const std::string& filename);

#endif // ANALYSISMODULE_H
