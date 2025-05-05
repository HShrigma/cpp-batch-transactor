#include "csv_reader.h"

CSVReader::CSVReader(const std::string path, char delimiter, bool skipHeader)
{
    this->path = path;
    this->delimiter = delimiter;
    this->skipHeader = skipHeader;
}

std::vector<std::vector<std::string>> CSVReader::readAll()
{
    std::vector<std::vector<std::string>> parsed;
    std::fstream fin;
    try
    {
        fin.open(path);
        std::vector<std::string> row;
        std::string line, word, temp;

        bool isFirstLine{true};
        while (std::getline(fin, line))
        {
            if (isFirstLine && skipHeader)
            {
                isFirstLine = false;
                continue;
            }
            parsed.emplace_back(lineToRow(line));
        }
        return parsed;
    }
    catch (const std::exception &e)
    {
        std::cout << "[ERROR] CSVReader::readAll: Error trying to open file at path: " << std::endl
                  << path << std::endl;
        return parsed;
    }
}

std::vector<std::string> CSVReader::lineToRow(const std::string &line)
{
    std::vector<std::string> res;
    size_t start{0};
    size_t end{0};

    while ((end = line.find(',', start)) != std::string::npos)
    {
        res.emplace_back(line.substr(start, end - start));
        start = end + 1;
    }

    // ensure timestamp is not empty
    if (!res.empty() && res.back().empty())
        res.pop_back();
    return res;
}
