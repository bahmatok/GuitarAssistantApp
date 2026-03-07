QT += testlib core multimedia widgets
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += ../../src/ticker.cpp test_ticker.cpp
HEADERS += ../../src/ticker.h
INCLUDEPATH += ../../src