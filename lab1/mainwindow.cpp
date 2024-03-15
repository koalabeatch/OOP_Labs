#include <fstream>

#include "mainwindow.h"
#include "ui_mainwindow.h"

enum {Romantic = 0, Thriller = 1, Fantasy = 2, Action = 3 };

struct Film {
    unsigned id;
    std::string name;
    int genre;
    unsigned year_release;
};

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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    std::vector<Film> films;

    std::fstream fin("films.csv");
    if (fin.is_open()){
        while (!fin.eof()){
            std::string line;
            std::getline(fin, line);

            ui->textBrowser->append(QString::fromStdString(line));

            Film flm;

            auto tokens = split_line(line, ';');
            flm.id = std::stoi(tokens[0]);
            flm.name = tokens[1];
            flm.genre = std::stoi(tokens[2]);
            flm.year_release = std::stoi(tokens[3]);

            films.push_back(flm);
        }
        fin.close();
    }
    else{
        ui->textBrowser->append("Невозможно открыть файл");
    }
    std::sort(films.begin(),films.end(), [](const Film& lhs, const Film& rhs){
        return lhs.year_release < rhs.year_release;
    });

    for (const auto& f: films) {
        if ((f.year_release > 2010) and (f.genre == Romantic)) {
            ui->textBrowser->append(QString:: fromStdString(f.name) + ", " + QString::number(f.year_release));
        }
    }
    std::ofstream fout("films_sorted.csv");
    if (fout.is_open()){
        for (const auto& f: films) {
            fout << f.id << ";" << f.name << ";" << f.year_release << ";" << std::endl ;
        }
    }
    fin.close();
}

MainWindow::~MainWindow()
{
    delete ui;
}

