QT += testlib core
QT -= gui
CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle
TEMPLATE = app
SOURCES += ../../src/timer.cpp test_timer.cpp
HEADERS += ../../src/timer.h
INCLUDEPATH += ../../src