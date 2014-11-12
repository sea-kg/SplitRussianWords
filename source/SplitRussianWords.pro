QT       += core
QT       += xml
QT       -= gui

TARGET = SplitRussianWords
DESTDIR = bin
OBJECTS_DIR = tmp/

CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += 	src/main.cpp \
			src/seakgExplodeWords.cpp \

HEADERS += 	src/seakgExplodeWords.h \
			
			
