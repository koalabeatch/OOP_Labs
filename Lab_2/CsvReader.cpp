#include <fstream>
#include "csvreader.h"

std::vector<std::string> split_line(const std::string &str, char delim) {

    std::vector<std::string> tokens;

    if (!str.empty()) {
        size_t start = 0, end;
        do {
            tokens.push_back(str.substr(start, (str.find(delim, start) - start)));
            end = str.find(delim, start);
            start = end + 1;
        } while (end != std::string::npos);
    }

    return tokens;
}

CsvReader::CsvReader(const std::string& filename)
{
    fin.open(filename);
}

CsvReader::~CsvReader()
{
    fin.close();
}

bool CsvReader::is_open()
{
    return fin.is_open();
}

flm CsvReader::read()
{
    std::string line;
    std::getline(fin, line);

    flm f;

    auto tokens = split_line(line, ';');
    f.id = std::stoi(tokens[0]);
    f.name = tokens[1];
    f.genre = std::stoi(tokens[2]);
    f.year_release = std::stoi(tokens[3]);

    return f;
}


std::vector<flm> CsvReader::readAll()
{
    std::vector<flm> films;

    while (!fin.eof()) {
        films.push_back(read());
    }

    return films;
}
