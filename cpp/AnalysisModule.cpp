#include "AnalysisModule.h"
#include <iostream>
#include <iomanip>
#include <sstream>
#include <fstream>
#include <cmath>
#include <algorithm>

using namespace std;

bool isNumeric(const string& str) {
    char* endptr = nullptr;
    strtod(str.c_str(), &endptr);
    return endptr != str.c_str() && *endptr == '\0';
}

void printInfo(const vector<vector<string>>& table) {
    if (table.empty()) return;

    int rows = table.size();
    int cols = table[0].size();
    cout << "--- INFO ---" << endl;
    cout << "Número de filas (incluyendo header): " << rows << endl;
    cout << "Número de columnas: " << cols << endl;
    cout << "Nombres de columnas:" << endl;

    for (const auto& col : table[0])
        cout << "  " << col << endl;

    cout << "\nResumen por columna:\n";
    cout << setw(20) << "Columna" << setw(15) << "Nulls" << setw(15) << "Tipo" << endl;

    for (int j = 0; j < cols; ++j) {
        int nulls = 0, numerics = 0;
        for (int i = 1; i < rows; ++i) {
            if (table[i][j].empty()) nulls++;
            else if (isNumeric(table[i][j])) numerics++;
        }
        string tipo = (numerics == (rows - 1 - nulls)) ? "Numérico" : "String";
        cout << setw(20) << table[0][j] << setw(15) << nulls << setw(15) << tipo << endl;
    }
}

void printHead(const std::vector<std::vector<std::string>>& table, int nLines) {
    std::cout << "--- HEAD (" << nLines << " filas) ---" << std::endl;
    int count = 0;
    for (const auto& row : table) {
        for (size_t i = 0; i < row.size(); ++i) {
            std::cout << row[i];
            if (i != row.size() - 1) std::cout << ", ";
        }
        std::cout << std::endl;
        if (++count >= nLines) break;
    }
}


void printDescribe(const vector<vector<string>>& table) {
    cout << "--- DESCRIBE ---" << endl;
    int cols = table[0].size();
    int rows = table.size();
    for (int j = 0; j < cols; ++j) {
        vector<double> nums;
        for (int i = 1; i < rows; ++i) {
            if (isNumeric(table[i][j])) nums.push_back(stod(table[i][j]));
        }
        if (!nums.empty()) {
            double sum = 0;
            for (auto v : nums) sum += v;
            double mean = sum / nums.size();
            double sq_sum = 0;
            for (auto v : nums) sq_sum += (v - mean) * (v - mean);
            double stddev = sqrt(sq_sum / nums.size());
            auto [min_it, max_it] = minmax_element(nums.begin(), nums.end());
            cout << " " << table[0][j] << ": Mean=" << mean 
                 << ", Std=" << stddev 
                 << ", Min=" << *min_it 
                 << ", Max=" << *max_it << endl;
        }
    }
}

void printCorrelation(const vector<vector<string>>& table) {
    cout << "--- CORRELATION MATRIX ---" << endl;

    if (table.empty()) return;

    int cols = table[0].size();
    int rows = table.size();

    // Extraer solo las columnas numéricas
    vector<string> headers = table[0];
    vector<vector<double>> numericData;

    // Identificar columnas numéricas
    vector<int> numericCols;
    for (int j = 0; j < cols; ++j) {
        bool isNumericCol = true;
        for (int i = 1; i < rows; ++i) {
            if (!isNumeric(table[i][j])) {
                isNumericCol = false;
                break;
            }
        }
        if (isNumericCol) numericCols.push_back(j);
    }

    int n = numericCols.size();
    numericData.resize(n, vector<double>(rows - 1));

    for (int k = 0; k < n; ++k) {
        int col = numericCols[k];
        for (int i = 1; i < rows; ++i) {
            numericData[k][i - 1] = stod(table[i][col]);
        }
    }

    // Función lambda para calcular la correlación de Pearson
    auto pearson = [](const vector<double>& x, const vector<double>& y) {
        double sumX = 0, sumY = 0, sumXY = 0;
        double sumX2 = 0, sumY2 = 0;
        int n = x.size();
        for (int i = 0; i < n; ++i) {
            sumX += x[i];
            sumY += y[i];
            sumXY += x[i] * y[i];
            sumX2 += x[i] * x[i];
            sumY2 += y[i] * y[i];
        }
        double numerator = n * sumXY - sumX * sumY;
        double denominator = sqrt((n * sumX2 - sumX * sumX) * (n * sumY2 - sumY * sumY));
        return (denominator == 0) ? 0.0 : numerator / denominator;
    };

    // Imprimir encabezados
    cout << fixed << setprecision(4);
    cout << setw(15) << "";
    for (int i = 0; i < n; ++i)
        cout << setw(15) << headers[numericCols[i]];
    cout << endl;

    for (int i = 0; i < n; ++i) {
        cout << setw(15) << headers[numericCols[i]];
        for (int j = 0; j < n; ++j) {
            double corr = pearson(numericData[i], numericData[j]);
            cout << setw(15) << corr;
        }
        cout << endl;
    }
}


void saveAnalysisToTxt(const vector<vector<string>>& table, const string& filename) {
    ofstream out(filename);
    if (!out) {
        cerr << "No se pudo crear archivo de salida: " << filename << endl;
        return;
    }

    streambuf* coutbuf = cout.rdbuf(); // backup cout buffer
    cout.rdbuf(out.rdbuf());           // redirige cout al archivo

    printInfo(table);
    cout << endl;
    printDescribe(table);
    cout << endl;
    printCorrelation(table);

    cout.rdbuf(coutbuf); // restaurar cout
    out.close();
}
