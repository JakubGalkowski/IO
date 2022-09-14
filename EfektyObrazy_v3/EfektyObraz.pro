QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

# You can make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

unix {
    CONFIG += link_pkgconfig
    PKGCONFIG += opencv4
}
INCLUDEPATH += C:\Users\Thinkpad\Downloads\Moodle\IO-projek\opencv\build\include


LIBS += C:\Users\Thinkpad\Downloads\Moodle\IO-projek\opencv\build-opencv\bin\libopencv_core460.dll
LIBS += C:\Users\Thinkpad\Downloads\Moodle\IO-projek\opencv\build-opencv\bin\libopencv_highgui460.dll
LIBS += C:\Users\Thinkpad\Downloads\Moodle\IO-projek\opencv\build-opencv\bin\libopencv_imgcodecs460.dll
LIBS += C:\Users\Thinkpad\Downloads\Moodle\IO-projek\opencv\build-opencv\bin\libopencv_imgproc460.dll
LIBS += C:\Users\Thinkpad\Downloads\Moodle\IO-projek\opencv\build-opencv\bin\libopencv_features2d460.dll
LIBS += C:\Users\Thinkpad\Downloads\Moodle\IO-projek\opencv\build-opencv\bin\libopencv_calib3d460.dll



SOURCES += \
    src/History.cpp \
    src/MainWindow.cpp \
    src/PaintArea.cpp \
    src/brushes/Brush.cpp \
    src/brushes/BrushEraser.cpp \
    src/brushes/BrushRegistry.cpp \
    src/brushes/BrushSimple.cpp \
    src/filters/Filter.cpp \
    src/filters/FilterRegistry.cpp \
    src/main.cpp

HEADERS += \
    src/Action.h \
    src/History.h \
    src/MainWindow.h \
    src/PaintArea.h \
    src/brushes/Brush.h \
    src/brushes/BrushEraser.h \
    src/brushes/BrushRegistry.h \
    src/brushes/BrushSimple.h \
    src/brushes/Brushes.h \
    src/filters/Filter.h \
    src/filters/FilterAdd.h \
    src/filters/FilterChannelMix.h \
    src/filters/FilterInvert.h \
    src/filters/FilterMax.h \
    src/filters/FilterMedian.h \
    src/filters/FilterMin.h \
    src/filters/FilterRegistry.h \
    src/filters/Filters.h

FORMS += \
    src/MainWindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES += \
    bin/rozszerzenia/czerwony.txt \
    bin/rozszerzenia/highpass.txt \
    bin/rozszerzenia/max.txt \
    bin/rozszerzenia/mediana.txt \
    bin/rozszerzenia/min.txt \
    bin/rozszerzenia/rozmycie.txt
