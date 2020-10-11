TEMPLATE = app
CONFIG += c++17
CONFIG -= app_bundle
CONFIG -= qt


QMAKE_CXXFLAGS +=   -pedantic-errors\
                    -std=c++17

SOURCES += main.cpp \
    Tools/tools.cpp \
    Ceasar/ceasar.cpp \
    Vigenere/vigenere.cpp

HEADERS += \
    Tools/tools.hpp \
    Ceasar/ceasar.hpp \
    Vigenere/vigenere.hpp
