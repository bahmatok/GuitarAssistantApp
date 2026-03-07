QT += testlib core widgets multimedia
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
TEMPLATE = app

SOURCES += ../../src/mainwindow.cpp \
           ../../src/chordtransposer.cpp \
           ../../src/ticker.cpp \
           ../../src/timer.cpp \
           ../../src/tuner.cpp \
           test_mainwindow.cpp

HEADERS += ../../src/mainwindow.h \
           ../../src/chordtransposer.h \
           ../../src/ticker.h \
           ../../src/timer.h \
           ../../src/tuner.h

INCLUDEPATH += ../../src
FORMS += ../../src/mainwindow.ui