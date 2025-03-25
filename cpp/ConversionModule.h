#ifndef CONVERSIONMODULE_H
#define CONVERSIONMODULE_H

#include <vector>
#include <string>
#pragma pack(push, 1)
struct Student {
    int serialNo;
    int greScore;
    int toeflScore;
    int universityRating;
    double sop;
    double lor;
    double cgpa;
    int research;
    double chanceOfAdmit;
};
#pragma pack(pop)

std::vector<Student> convertTableToStudents(const std::vector<std::vector<std::string>>& table);
bool writeStudentsBinary(const std::vector<Student>& students, const std::string& filename);
bool readStudentsBinary(const std::string& filename, std::vector<Student>& students);
void printBinaryHeadTail(const std::vector<Student>& students, size_t headCount = 5, size_t tailCount = 5);
void printStructSize();

#endif // CONVERSIONMODULE_H
