QT += testlib
QT += widgets testlib
QT -= gui
QT += testlib widgets

INCLUDEPATH += ../chisl
DEPENDPATH += ../chisl

INCLUDEPATH += ../build-chisl-*/debug


CONFIG += qt console warn_on depend_includepath testcase
CONFIG -= app_bundle

TEMPLATE = app

SOURCES +=  tst_testicui.cpp

HEADERS += \
    tst_testicui.h

INCLUDEPATH += ../chisla

