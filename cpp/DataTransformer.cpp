#include "DataTransformer.h"
#include <sstream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

std::vector<std::vector<std::string>> readCSV(const std::string& csvData) {
    std::vector<std::vector<std::string>> table;
    std::istringstream iss(csvData);
    std::string line;
    while (std::getline(iss, line)) {
        std::vector<std::string> row;
        std::istringstream lineStream(line);
        std::string cell;
        while (std::getline(lineStream, cell, ',')) {
            row.push_back(cell);
        }
        table.push_back(row);
    }
    return table;
}

bool loadData(const std::vector<std::vector<std::string>>& table, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "No se pudo abrir " << filename << " para escritura." << std::endl;
        return false;
    }
    size_t numRows = table.size();
    out.write(reinterpret_cast<const char*>(&numRows), sizeof(numRows));
    for (const auto& row : table) {
        size_t numCols = row.size();
        out.write(reinterpret_cast<const char*>(&numCols), sizeof(numCols));
        for (const auto& cell : row) {
            size_t len = cell.size();
            out.write(reinterpret_cast<const char*>(&len), sizeof(len));
            out.write(cell.c_str(), len);
        }
    }
    out.close();
    return true;
}
