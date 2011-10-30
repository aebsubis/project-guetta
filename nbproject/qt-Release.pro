# This file is generated automatically. Do not edit.
# Use project properties -> Build -> Qt -> Expert -> Custom Definitions.
TEMPLATE = app
DESTDIR = dist/Release/GNU-Linux-x86
TARGET = QtApplication_1
VERSION = 1.0.0
CONFIG -= debug_and_release app_bundle lib_bundle
CONFIG += release 
QT = core gui opengl
SOURCES += main.cpp StandardCamera.cpp GLWidget.cpp GuettaFeatures.cpp Tetrahedron.cpp Guetta.cpp Viewer.cpp newForm.cpp GuettaViewer.cpp
HEADERS += GuettaKeyPoint.h GuettaFeatures.h StandardCamera.h GLWidget.h Viewer.h GuettaViewer.h newForm.h Guetta.h Tetrahedron.h
FORMS += GuettaViewer.ui newForm.ui Guetta.ui
RESOURCES +=
TRANSLATIONS +=
OBJECTS_DIR = build/Release/GNU-Linux-x86
MOC_DIR = 
RCC_DIR = 
UI_DIR = 
QMAKE_CC = gcc
QMAKE_CXX = g++
DEFINES += 
INCLUDEPATH += 
LIBS += 
