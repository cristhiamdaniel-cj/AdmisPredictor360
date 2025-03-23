#include "EnvLoader.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

void loadEnv(const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "No se pudo abrir " << filename << std::endl;
        return;
    }
    std::string line;
    while (std::getline(file, line)) {
        if (line.empty() || line[0]=='#') continue;
        std::istringstream iss(line);
        std::string key, value;
        if (std::getline(iss, key, '=') && std::getline(iss, value)) {
            setenv(key.c_str(), value.c_str(), 1);
        }
    }
}
