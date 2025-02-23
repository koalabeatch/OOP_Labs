#ifndef ABSTRACTREADER_H
#define ABSTRACTREADER_H

#include <iostream>
#include <fstream>
#include <iostream>
#include <vector>
#include <QString>

struct emp
{
    unsigned id;
    std::string name;
    int genre;
    unsigned year_release;
};
struct flm
{
    unsigned id;
    std::string name;
    int genre;
    unsigned yearRelease;
};

struct fig
{
    unsigned id;
    std::string name;
    std::string form;
    int color;
};
enum genres {Romantic = 0, Thriller = 1, Fantasy = 2, Action = 3 };


class AbstractReader
{
public:
    virtual bool is_open() = 0;
    virtual std::vector<flm>  readAll() = 0;
    virtual operator bool() = 0;
};

#endif // ABSTRACTREADER_H
