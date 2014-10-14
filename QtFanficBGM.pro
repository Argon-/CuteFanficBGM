QT       += core gui phonon

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = QtFanficBGM
TEMPLATE = app


SOURCES += main.cpp\
        MainWindow.cpp \
        Playlist.cpp \
        LoopingPlayer.cpp

HEADERS  += MainWindow.h \
        Playlist.h \
        LoopingPlayer.h
