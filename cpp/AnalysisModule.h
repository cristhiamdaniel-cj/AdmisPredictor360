#ifndef ANALYSISMODULE_H
#define ANALYSISMODULE_H

#include <vector>
#include <string>

void printInfo(const std::vector<std::vector<std::string>>& table);
void printHead(const std::vector<std::vector<std::string>>& table, int lines = 5);
void printDescribe(const std::vector<std::vector<std::string>>& table);
void printCorrelation(const std::vector<std::vector<std::string>>& table);
void saveAnalysisToTxt(const std::vector<std::vector<std::string>>& table, const std::string& filename);

#endif // ANALYSISMODULE_H
