/* This file is part of CuteFanficBGM.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
 
#include <QApplication>
#include <QCoreApplication>

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
