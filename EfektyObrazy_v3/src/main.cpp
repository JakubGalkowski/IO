#include "MainWindow.h"

#include <QApplication>
#include <filesystem>

#include "filters/FilterRegistry.h"
#include "filters/Filters.h"

#include "brushes/BrushRegistry.h"
#include "brushes/Brushes.h"

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    FilterRegistry::get().load();

    FilterRegistry::get().add({"Invert", new FilterInvert});
    FilterRegistry::get().add({"Swap B<>G", new FilterChannelMix(0,1)});
    FilterRegistry::get().add({"Swap R<>B", new FilterChannelMix(0,2)});
    FilterRegistry::get().add({"Swap R<>G", new FilterChannelMix(1,2)});

    BrushRegistry::get().add({"Red 50px", new BrushSimple});
    BrushRegistry::get().add({"Black 50px", new BrushEraser});

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
