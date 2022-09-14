#ifndef FILTERREGISTRY_H
#define FILTERREGISTRY_H

#include <vector>
#include <string>
#include <QStringList>
#include "Filter.h"

class FilterRegistry
{
public:
    struct Entry {
           std::string name;
           Filter * filter;
    };

    static FilterRegistry & get()
    {
        static FilterRegistry fr;
        return fr;
    }

    static QStringList templateOptions;

    void load();
    void add(FilterRegistry::Entry && e);

    std::vector<FilterRegistry::Entry> entries;

private:
    FilterRegistry();
};

#endif // FILTERREGISTRY_H
