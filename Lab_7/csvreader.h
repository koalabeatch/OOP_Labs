#ifndef CSVREADER_H
#define CSVREADER_H


#include "AbstractReader.h"



std::vector<std::string> split_line(const std::string &str, char delim);

class CsvReader : public AbstractReader
{
public:
    CsvReader(const std::string& filename);
    ~CsvReader();

    bool is_open() override;
    void close();
    flm read();
    std::vector<flm> readAll() override;
    int getLineNum();
    operator bool() override{
        return is_open();
    }

private:
    std::ifstream fin;
    unsigned lineNum;
};
#endif // CSVREADER_H
