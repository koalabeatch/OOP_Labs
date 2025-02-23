#ifndef CSVWRITER_H
#define CSVWRITER_H

#include "csvreader.h"

class CsvWriter
{
public:

  CsvWriter(const std::string& filename);
  ~CsvWriter();
  bool isOpen() const { return fout.is_open(); }
  void write(flm figure);
  void writeAll(std::vector<flm> vec);
  int rusColortoEnum(QString text);
  int rusGenreToEnum(QString rusGenre);

//  friend std::ofstream& operator<<(std::ofstream& os, flm film){
//     os << film.id << ";" << film.name << ";" << film.genre << ";" << film.yearRelease << std::endl;
//     return os;
//  }

private:
  std::ofstream fout; // Обьект потокового вывода
  enum genres {Romantic = 0, Thriller = 1, Fantasy = 2, Action = 3 };
};


#endif // CSVWRITER_H
