#include <JSONReader.h>


JSONReader::JSONReader(const std::string& filename)
{
    fin.open(filename);
}

JSONReader::~JSONReader()
{
    fin.close();
}

bool JSONReader::is_open()
{
    return fin.is_open();
}

// fig JSONReader::read()
// {
//     nlohmann::json json;
//     fin >> json;
//     nlohmann::json j = json[j_num];
//     fig film;
//     film.id = j["id"];
//     film.name = j["name"];
//     film.form = j["form"];
//     film.color = j["color"];
//     return film;
// }

std::vector<flm> JSONReader::readAll()
{
    std::vector<flm> films;

    nlohmann::json json;

    fin >> json;

    for(const auto & j: json["figs"])
    {
        flm film;

        film.id = j["id"];
        film.name = j["name"];
        film.genre = j["form"];
        film.yearRelease = j["color"];

        films.push_back(film);
    }

    return films;
}
