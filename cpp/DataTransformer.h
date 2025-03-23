#ifndef DATATRANSFORMER_H
#define DATATRANSFORMER_H

#include <string>
#include <vector>
std::vector<std::vector<std::string>> readCSV(const std::string& csvData);
bool loadData(const std::vector<std::vector<std::string>>& table, const std::string& filename);

#endif // DATATRANSFORMER_H
