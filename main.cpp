#include <QApplication>
#include <QCoreApplication>
#include <QDebug>

#include "MainWindow.h"
#include "Playlist.h"
#include "LoopingPlayer.h"


int main(int argc, char *argv[])
{
    QCoreApplication::setOrganizationName("CuteFanficBGMProductions");
    QCoreApplication::setOrganizationDomain("CuteFanficBGMProductions.net");
    QCoreApplication::setApplicationName("CuteFanficBGM");

    Playlist *playlist = new Playlist();
    LoopingPlayer *player = new LoopingPlayer();

    QApplication a(argc, argv);
    MainWindow w (0, playlist, player);
    w.init();
    w.show();

    return a.exec();
}
