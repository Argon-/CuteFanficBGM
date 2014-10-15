#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <QSlider>
#include <QMenu>
#include <QMenuBar>

#include "Playlist.h"
#include "LoopingPlayer.h"



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent, Playlist *playlist, LoopingPlayer *player);
    ~MainWindow();
    void init();

private:
    const int max_volume;
    
    QWidget *centralWidget;
    QVBoxLayout *layout;
    QHBoxLayout *layout_title;
    QGridLayout *layout_main_ctrl;
    QHBoxLayout *layout_ch_ctrl;
    QHBoxLayout *layout_song_ctrl;
    QHBoxLayout *layout_volume_ctrl;

    QLabel *l_title;
    QLabel *l_ch;
    QLabel *l_song;

    QPushButton *btn_playpause;
    QPushButton *btn_proceed;
    QPushButton *btn_reset;
    QPushButton *btn_ch_prev;
    QPushButton *btn_ch_next;
    QPushButton *btn_song_prev;
    QPushButton *btn_song_next;

    QSlider *slider_volume;

    QMenu *file;
    QAction *act_selectOSTDirectoy;
    QAction *act_proceed;

    QSettings *settings;
    Playlist *playlist;
    LoopingPlayer *player;

    void setAlwaysOnTop(const bool alwaysOnTop);

private slots:
    void playpause_cb();
    void proceed_cb();
    void reset_cb();
    void ch_prev_cb();
    void ch_next_cb();
    void song_prev_cb();
    void song_next_cb();
    void slider_volume_cb(int value);
    void selectOSTDirectoy_cb();

};

#endif // MAINWINDOW_H
