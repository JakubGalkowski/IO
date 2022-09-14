#ifndef BRUSHREGISTRY_H
#define BRUSHREGISTRY_H

#include <vector>
#include <string>
#include <QStringList>
#include "Brush.h"

class BrushRegistry
{
public:
    struct Entry {
           std::string name;
           Brush * brush;
    };

    static BrushRegistry & get()
    {
        static BrushRegistry fr;
        return fr;
    }

public:
    void setCurrent(int id);
    void add(BrushRegistry::Entry && e);
    std::vector<BrushRegistry::Entry> entries;

    Entry * current = nullptr;

private:
    BrushRegistry();
};

#endif // BRUSHREGISTRY_H
