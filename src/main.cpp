#include <QApplication>
#include <QCoreApplication>
#include <QDebug>

#include "MainWindow.h"
#include "Playlist.h"
#include "LoopingPlayer.h"



int main(int argc, char *argv[])
{
    QApplication::setOrganizationName("CuteFanficBGMProductions");
    QApplication::setOrganizationDomain("CuteFanficBGMProductions.net");
    QApplication::setApplicationName("CuteFanficBGM");
    QApplication a(argc, argv);

    Playlist *playlist = new Playlist();
    LoopingPlayer *player = new LoopingPlayer();

    MainWindow w (0, playlist, player);
    w.show();

    const int r = a.exec();
    delete playlist;
    delete player;
    return r;
}
