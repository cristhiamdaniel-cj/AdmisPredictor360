#include "ConversionModule.h"
#include <vector>
#include <fstream>
#include <iostream>
#include <cstdlib>

int toInt(const std::string& s) { return std::stoi(s); }
double toDouble(const std::string& s) { return std::stod(s); }

std::vector<Student> convertTableToStudents(const std::vector<std::vector<std::string>>& table) {
    std::vector<Student> students;
    for (size_t i = 1; i < table.size(); i++) { // omitir header
        if (table[i].size() < 9) continue;
        Student s;
        try {
            s.serialNo = toInt(table[i][0]);
            s.greScore = toInt(table[i][1]);
            s.toeflScore = toInt(table[i][2]);
            s.universityRating = toInt(table[i][3]);
            s.sop = toDouble(table[i][4]);
            s.lor = toDouble(table[i][5]);
            s.cgpa = toDouble(table[i][6]);
            s.research = toInt(table[i][7]);
            s.chanceOfAdmit = toDouble(table[i][8]);
            students.push_back(s);
        } catch (...) {
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
