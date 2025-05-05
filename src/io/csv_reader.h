#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <iostream>

class CSVReader
{
private:
    std::string path;
    char delimiter;
    bool skipHeader;
    std::vector<std::string> lineToRow(const std::string &line);

public:
    CSVReader(const std::string path, char delimiter = ',', bool skipHeader = true);

    std::vector<std::vector<std::string>> readAll();
};