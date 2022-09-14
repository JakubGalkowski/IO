#include "BrushRegistry.h"

BrushRegistry::BrushRegistry()
    : entries()
{}

void BrushRegistry::add(Entry && e)
{
    entries.push_back(e);
}


void BrushRegistry::setCurrent(int id)
{
    current = &entries[id];
}

