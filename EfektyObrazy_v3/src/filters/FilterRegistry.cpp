#include "FilterRegistry.h"
#include <filesystem>
#include <QDebug>
#include <fstream>
#include "Filters.h"

namespace fs = std::filesystem;

QStringList FilterRegistry::templateOptions({"default", "add", "max", "median", "min"});

FilterRegistry::FilterRegistry()
    : entries()
{

}

void FilterRegistry::load()
{
    const fs::path extensionsPath{"rozszerzenia"};

    if (fs::exists(extensionsPath) && fs::is_directory(extensionsPath))
    {
        for (auto const & entry : fs::directory_iterator(extensionsPath))
        {
            if(!fs::is_regular_file(entry)) continue;

            std::string path = entry.path().string();
            std::string name = entry.path().stem().string();

            // qDebug() << "Loading " << QString::fromStdString(path);

            std::ifstream file{entry.path().string()};

            if (file.is_open())
            {
                std::string line;
                std::getline(file, line);
//                file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                QString header = QString::fromStdString(line).toLower();
                QStringList headers = header.split(" ");

                if (headers[0] == "#template" && headers.size() == 2)
                {
                    std::vector<int> data = {};
                    while(!file.eof())
                    {
                        int tmp = 0;
                        file >> tmp;
                        data.push_back(tmp);
                    }

                    // for (int a : data) {
                    //     qDebug() << a;
                    // }

                    // "default", "add", "max", "median", "min"
                    switch (templateOptions.indexOf(headers[1]))
                    {
                        case 0:
                            {
                                int size = data[0];
                                // qDebug() << size;
                                Filter *f = new Filter(size, "Default");
                                for (int i = 0; i < size; ++i) {
                                    for (int j = 0; j < size; ++j) {
                                        int idx = size*i +j + 1;
                                        f->set(data[idx], i ,j);
                                    }
                                }
                                add({name, f});
                            }
                            break;
                        case 1:
                            {
                                add({name, new FilterAdd(data[0], data[1], data[2])});
                            }
                            break;
                        case 2:
                            {
                                int size = data[0];
                                add({name, new FilterMax(size)});
                            }

                            break;
                        case 3:
                            {
                                int size = data[0];
                                add({name, new FilterMedian(size)});
                            }

                            break;
                        case 4:
                            {
                                int size = data[0];
                                add({name, new FilterMin(size)});
                            }

                            break;
                        default:
                            break;
                    }
                }

                file.close();
            }
        }
    }
    else
    {
        fs::create_directory(extensionsPath);
    }
}

void FilterRegistry::add(Entry && e)
{
    entries.push_back(e);
}


