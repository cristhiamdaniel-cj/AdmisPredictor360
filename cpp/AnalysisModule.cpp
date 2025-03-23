#include "AnalysisModule.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>

// Estructura para almacenar estadísticas
struct Stats {
    size_t count;
    double mean;
    double stdDev;
    double min;
    double q25;
    double median;
    double q75;
    double max;
};

// Función auxiliar para calcular estadísticas de un vector de datos
static Stats computeStats(const std::vector<double>& data) {
    Stats s;
    s.count = data.size();
    if (s.count == 0) return s;
    double sum = 0.0;
    s.min = data[0];
    s.max = data[0];
    for (double v : data) {
        sum += v;
        if (v < s.min) s.min = v;
        if (v > s.max) s.max = v;
    }
    s.mean = sum / s.count;
    double variance = 0.0;
    for (double v : data) {
        variance += (v - s.mean) * (v - s.mean);
    }
    s.stdDev = (s.count > 1) ? std::sqrt(variance / (s.count - 1)) : 0.0;
    std::vector<double> sorted = data;
    std::sort(sorted.begin(), sorted.end());
    auto getPercentile = [&](double p) -> double {
        double pos = p * (s.count - 1);
        size_t idx = static_cast<size_t>(pos);
        double frac = pos - idx;
        if (idx + 1 < sorted.size())
            return sorted[idx] * (1 - frac) + sorted[idx+1] * frac;
        else
            return sorted[idx];
    };
    s.q25 = getPercentile(0.25);
    s.median = getPercentile(0.5);
    s.q75 = getPercentile(0.75);
    return s;
}

// Función auxiliar para calcular la correlación de Pearson entre dos vectores
static double correlation(const std::vector<double>& x, const std::vector<double>& y) {
    if (x.size() != y.size() || x.empty()) return 0.0;
    double meanX = 0.0, meanY = 0.0;
    size_t n = x.size();
    for (size_t i = 0; i < n; i++) {
        meanX += x[i];
        meanY += y[i];
    }
    meanX /= n;
    meanY /= n;
    double numerator = 0.0, denomX = 0.0, denomY = 0.0;
    for (size_t i = 0; i < n; i++) {
        double dx = x[i] - meanX;
        double dy = y[i] - meanY;
        numerator += dx * dy;
        denomX += dx * dx;
        denomY += dy * dy;
    }
    double denominator = std::sqrt(denomX * denomY);
    return (denomX && denomY) ? numerator / denominator : 0.0;
}

// Imprime la información básica del dataset
void printInfo(const std::vector<std::vector<std::string>>& table) {
    if (table.empty()) return;
    std::cout << "--- INFO ---" << std::endl;
    std::cout << "Filas: " << table.size() << std::endl;
    std::cout << "Columnas: " << table[0].size() << std::endl;
    std::cout << "Nombres de columnas:" << std::endl;
    for (const auto &col : table[0]) {
        if (!col.empty())
            std::cout << std::setw(15) << col << std::endl;
    }
    std::cout << std::endl;
}

// Imprime las primeras n filas con formato de DataFrame
void printHead(const std::vector<std::vector<std::string>>& table, int n) {
    std::cout << "--- HEAD (" << n << " filas) ---" << std::endl;
    for (size_t i = 0; i < table.size() && i < static_cast<size_t>(n); i++){
        for (size_t j = 0; j < table[i].size(); j++){
            std::cout << std::setw(15) << table[i][j];
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Imprime estadísticas descriptivas de cada columna numérica
void printDescribe(const std::vector<std::vector<std::string>>& table) {
    std::cout << "--- DESCRIBE ---" << std::endl;
    int cols = table[0].size();
    for (int j = 0; j < cols; j++){
        std::vector<double> colData;
        for (size_t i = 1; i < table.size(); i++){
            try {
                double val = std::stod(table[i][j]);
                colData.push_back(val);
            } catch (...) {
                // Ignorar celdas no numéricas
            }
        }
        if (!colData.empty()){
            Stats s = computeStats(colData);
            std::cout << std::setw(15) << table[0][j] << ": ";
            std::cout << "Mean=" << s.mean << ", Std=" << s.stdDev;
            std::cout << ", Min=" << s.min << ", Max=" << s.max << std::endl;
        } else {
            std::cout << std::setw(15) << table[0][j] << ": No numérico" << std::endl;
        }
    }
    std::cout << std::endl;
}

// Imprime la matriz de correlación entre columnas numéricas
void printCorrelation(const std::vector<std::vector<std::string>>& table) {
    std::cout << "--- CORRELATION MATRIX ---" << std::endl;
    int cols = table[0].size();
    std::vector<std::vector<double>> numericCols(cols);
    for (int j = 0; j < cols; j++){
        for (size_t i = 1; i < table.size(); i++){
            try {
                double val = std::stod(table[i][j]);
                numericCols[j].push_back(val);
            } catch (...) {
                // Ignorar celdas no numéricas
            }
        }
    }
    std::cout << std::setw(15) << "";
    for (int j = 0; j < cols; j++){
        std::cout << std::setw(15) << table[0][j];
    }
    std::cout << std::endl;
    for (int i = 0; i < cols; i++){
        std::cout << std::setw(15) << table[0][i];
        for (int j = 0; j < cols; j++){
            if (numericCols[i].empty() || numericCols[j].empty())
                std::cout << std::setw(15) << "NA";
            else {
                double corr = correlation(numericCols[i], numericCols[j]);
                std::cout << std::setw(15) << corr;
            }
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

// Función que agrupa todo el análisis e imprime en la terminal
void analyzeAndPrint(const std::vector<std::vector<std::string>>& table) {
    printInfo(table);
    printHead(table, 6);  // Header + 5 filas de datos
    printDescribe(table);
    printCorrelation(table);
}

// Guarda el análisis (resultado de analyzeAndPrint) en un archivo TXT.
void saveAnalysisToTxt(const std::vector<std::vector<std::string>>& table, const std::string& filename) {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "No se pudo crear " << filename << std::endl;
        return;
    }
    std::ostringstream oss;
    // Redirigir la salida temporalmente
    std::streambuf* coutbuf = std::cout.rdbuf();
    std::cout.rdbuf(oss.rdbuf());
    analyzeAndPrint(table);
    std::cout.rdbuf(coutbuf);
    out << oss.str();
    out.close();
}
