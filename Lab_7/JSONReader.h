#ifndef JSONREADER_H
#define JSONREADER_H

#include "AbstractReader.h"
#include "json.hpp"

class JSONReader : public AbstractReader
{
public:
    JSONReader(const std::string& filename);
    ~JSONReader();
    bool is_open() override;
    std::vector<flm> readAll() override;
    operator bool() override{
        return is_open();
    }
private:
    std::ifstream fin;
};

#endif // JSONREADER_H
