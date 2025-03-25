#include "ConversionModule.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>

int toInt(const std::string& s) { return std::stoi(s); }
double toDouble(const std::string& s) { return std::stod(s); }

std::vector<Student> convertTableToStudents(const std::vector<std::vector<std::string>>& table) {
    std::vector<Student> students;
    // Empezamos desde 1 para omitir el header
    for (size_t i = 1; i < table.size(); i++) {
        std::vector<std::string> row = table[i];
        // Si la fila tiene menos de 9 columnas, se rellena con "0"
        while (row.size() < 9) {
            row.push_back("0");
        }
        Student s;
        try {
            s.serialNo = toInt(row[0]);
            s.greScore = toInt(row[1]);
            s.toeflScore = toInt(row[2]);
            s.universityRating = toInt(row[3]);
            s.sop = toDouble(row[4]);
            s.lor = toDouble(row[5]);
            s.cgpa = toDouble(row[6]);
            s.research = toInt(row[7]);
            s.chanceOfAdmit = toDouble(row[8]);
            students.push_back(s);
        } catch (...) {
            std::cerr << "Error en la conversión de la fila " << i << std::endl;
            continue;
        }
    }
    return students;
}

bool writeStudentsBinary(const std::vector<Student>& students, const std::string& filename) {
    std::ofstream out(filename, std::ios::binary);
    if (!out) {
        std::cerr << "Error al abrir " << filename << " para escritura." << std::endl;
        return false;
    }
    size_t count = students.size();
    out.write(reinterpret_cast<const char*>(&count), sizeof(count));
    for (const auto& s : students) {
        out.write(reinterpret_cast<const char*>(&s), sizeof(Student));
    }
    out.close();
    return true;
}

bool readStudentsBinary(const std::string& filename, std::vector<Student>& students) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "Error al abrir " << filename << " para lectura." << std::endl;
        return false;
    }
    size_t count;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    students.resize(count);
    for (size_t i = 0; i < count; i++) {
        in.read(reinterpret_cast<char*>(&students[i]), sizeof(Student));
    }
    in.close();
    return true;
}

void printBinaryHeadTail(const std::vector<Student>& students, size_t headCount, size_t tailCount) {
    std::cout << "--- Binary Data Head (" << headCount << " registros) ---" << std::endl;
    size_t n = students.size();
    for (size_t i = 0; i < n && i < headCount; i++) {
        std::cout << "Serial: " << students[i].serialNo 
                  << ", GRE: " << students[i].greScore
                  << ", TOEFL: " << students[i].toeflScore
                  << ", Rating: " << students[i].universityRating
                  << ", SOP: " << students[i].sop
                  << ", LOR: " << students[i].lor
                  << ", CGPA: " << students[i].cgpa
                  << ", Research: " << students[i].research
                  << ", Chance: " << students[i].chanceOfAdmit
                  << std::endl;
    }
    std::cout << std::endl;
    std::cout << "--- Binary Data Tail (" << tailCount << " registros) ---" << std::endl;
    size_t start = (n > tailCount ? n - tailCount : 0);
    for (size_t i = start; i < n; i++) {
        std::cout << "Serial: " << students[i].serialNo 
                  << ", GRE: " << students[i].greScore
                  << ", TOEFL: " << students[i].toeflScore
                  << ", Rating: " << students[i].universityRating
                  << ", SOP: " << students[i].sop
                  << ", LOR: " << students[i].lor
                  << ", CGPA: " << students[i].cgpa
                  << ", Research: " << students[i].research
                  << ", Chance: " << students[i].chanceOfAdmit
                  << std::endl;
    }
}

void printBinaryInfo_New(const std::string& filename) {
    std::ifstream in(filename, std::ios::binary);
    if (!in) {
        std::cerr << "No se pudo abrir " << filename << " para lectura." << std::endl;
        return;
    }
    size_t count = 0;
    in.read(reinterpret_cast<char*>(&count), sizeof(count));
    std::cout << "Número de registros (estudiantes) en el binario: " << count << std::endl;
    in.close();
}

void printStructSize() {
    std::cout << "Tamaño real de struct Student: " << sizeof(Student) << " bytes" << std::endl;
}