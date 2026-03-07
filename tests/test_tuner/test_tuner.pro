QT += testlib core multimedia
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += ../../src/tuner.cpp test_tuner.cpp
HEADERS += ../../src/tuner.h 
INCLUDEPATH += ../../src