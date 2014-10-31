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
 
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtWidgets>
#include <QSlider>
#include <QMenu>
#include <QMenuBar>
#include <QCloseEvent>

#include "Playlist.h"
#include "LoopingPlayer.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, 
                        Playlist *playlist, 
                        LoopingPlayer *player);
    ~MainWindow();

private:
    const int max_volume;
    bool alwaysOnTop;
    
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QHBoxLayout *layout_title;
    QGridLayout *layout_main_ctrl;
    QHBoxLayout *layout_ch_ctrl;
    QHBoxLayout *layout_song_ctrl;
    QHBoxLayout *layout_song_title;
    QHBoxLayout *layout_volume_ctrl;

    QLabel *l_title;
    QLabel *l_ch_ctrl;
    QLabel *l_song_ctrl;
    QLabel *l_song_title;

    QPushButton *btn_playpause;
    QPushButton *btn_proceed;
    QPushButton *btn_reset;
    QPushButton *btn_ch_prev;
    QPushButton *btn_ch_next;
    QPushButton *btn_song_prev;
    QPushButton *btn_song_next;

    QSlider *slider_volume;

    QMenu *menu_controls;
    QAction *act_playpause;
    QAction *act_proceed;
    QAction *act_reset;
    QAction *act_ch_next;
    QAction *act_ch_prev;
    QAction *act_song_next;
    QAction *act_song_prev;

    QMenu *menu_settings;
    QAction *act_selectPlaylist;
    QAction *act_selectSonglist;
    QAction *act_selectSongDirectoy;
    QAction *act_always_on_top;

    QSettings *settings;
    Playlist *playlist;
    LoopingPlayer *player;

    void displayError(const QString &errorText, 
                      const QString &informativeText, 
                      const bool criticalWarning = true, 
                      const QString &buttonText = "Quit");
    QString promptForFile(const QString &prompt);

    bool setPlaylistFile(const QString &s, 
                         const bool criticalWarning = false, 
                         const QString &buttonText = "OK");
    bool setSonglistFile(const QString &s, 
                         const bool criticalWarning = false, 
                         const QString &buttonText = "OK");
    bool setSongDirectory(const QString &s, 
                          const bool criticalWarning = false, 
                          const QString &buttonText = "OK");
    void updateLabels();
    void closeEvent(QCloseEvent * event);

private slots:
    void init();
    void playpause_cb();
    void proceed_cb();
    void reset_cb();
    void ch_prev_cb();
    void ch_next_cb();
    void song_prev_cb();
    void song_next_cb();
    void slider_volume_cb(int value);
    void selectAndSetPlaylistFile_cb();
    void selectAndSetSonglistFile_cb();
    void selectAndSetSongDirectory_cb();
    void toggleAlwaysOnTop();

};

#endif // MAINWINDOW_H
