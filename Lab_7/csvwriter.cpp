#include <fstream>
#include "csvwriter.h"



CsvWriter::CsvWriter(const std::string& filename)
{
    fout.open(filename);
}

CsvWriter::~CsvWriter()
{
    fout.close();
}

std::ofstream& operator<<(std::ofstream& os, flm film){
   os << film.id << ";" << film.name << ";" << film.genre << ";" << film.yearRelease << std::endl;
   return os;
}

void CsvWriter::write(flm film)
{
    if(!CsvWriter::isOpen()) { // Проверка, открылся ли файл на запись:
      std::cout << "Error! File is not open" << std::endl;}
    else {fout << film;}

    //backup
    //else if (flag==0) {fout  << film.id << ";" << film.name << ";" << film.form << ";" << film.color << std::endl;}
    //else {fout << film.id << ";" << film.name << ";" << film.form << ";" << film.color;}
}

void CsvWriter::writeAll(std::vector<flm> films)
{
    for (auto f: films){
        fout << f;
    }

    //backup
    //for (int i = 0; i < int(vec.size()); i++) {
    //  if (i != int(vec.size())-1){CsvWriter::write(vec[i]);}
    //  else {CsvWriter::write(vec[i],1);}
    //}

}

int CsvWriter::rusGenreToEnum(QString rusGenre)
{
    if      (rusGenre=="Романтика") {return Romantic;}
    else if (rusGenre=="Триллер")   {return Thriller;}
    else if (rusGenre=="Фантастика"){return Fantasy;}
    else                            {return Action;}
}
