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
    if (fin.eof() or (line.empty() or (line.size()==0))) {
//        //pass
        f.id = 0;
        f.name = "";
        f.genre = -1;
        f.yearRelease = 0;
        return f;
    }
    else
    {
//        if (line.empty()){
//            throw std::runtime_error("Empty line");
//        }
        auto tokens = split_line(line, ';');

        auto idStr = tokens[0];
        if (idStr.empty()){
            throw std::runtime_error("Empty line in id");
        }
        int id = std::stoi(idStr);

        auto name = tokens[1];
        if (name.empty()){
            throw std::runtime_error("Empty line in name");
        }

        auto genreStr = tokens[2];
        if (genreStr.empty()){
            throw std::runtime_error("Empty line in genre");
        }
        int genre = std::stoi(genreStr);

        auto yearReleaseStr = tokens[3];
        if (yearReleaseStr.empty()){
            throw std::runtime_error("Empty line in release year");
        }
        int yearRelease = std::stoi(yearReleaseStr);

        f.id = id;
        f.name = name;
        f.genre = genre;
        f.yearRelease = yearRelease;
        return f;
    }
}

int CsvReader::getLineNum()
{
    return lineNum;
}

std::vector<flm> CsvReader::readAll()
{
    std::vector<flm> films;
    // try{

    lineNum = 1;

    while (!fin.eof())
    {

        flm f = read();
        if (f.genre==-1){ }
        else  films.push_back(f);

      lineNum++;
    }/*
    }
    catch (const std::exception& e) {
        << "Exception caught: " << e.what() << "\nin line: "<< lineNum <<"\nPlease, correct this error in your file." << std::endl;
        films.clear();
    }*/

    return films;
}
