#ifndef CSVREADER_H
#define CSVREADER_H

#include <fstream>
#include <iostream>
#include <vector>
#include <QString>

struct emp{
    unsigned id;
    std::string name;
    int genre;
    unsigned year_release;
};
struct flm {
    unsigned id;
    std::string name;
    int genre;
    unsigned year_release;
};


std::vector<std::string> split_line(const std::string &str, char delim);

class CsvReader
{
public:
    CsvReader(const std::string& filename);
    ~CsvReader();

    bool is_open();
    void close();
    flm read();
    std::vector<flm> readAll();

private:
    std::ifstream fin;
};
#endif // CSVREADER_H
