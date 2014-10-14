#include "MainWindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent, Playlist *playlist, LoopingPlayer *player) : 
    QMainWindow(parent),
    max_volume(100),
    centralWidget(new QWidget(parent)),
    layout(new QVBoxLayout(parent)),
    layout_title(new QHBoxLayout(parent)),
    layout_main_ctrl(new QGridLayout(parent)),
    layout_ch_ctrl(new QHBoxLayout(parent)),
    layout_song_ctrl(new QHBoxLayout(parent)),
    layout_volume_ctrl(new QHBoxLayout(parent)),
    l_title(new QLabel("title", this)),
    l_ch(new QLabel("chapter", this)),
    l_song(new QLabel("song", this)),
    btn_playpause(new QPushButton("Play", this)),
    btn_proceed(new QPushButton("&Proceed", this)),
    btn_reset(new QPushButton("Reset", this)),
    btn_ch_prev(new QPushButton("-", this)),
    btn_ch_next(new QPushButton("+", this)),
    btn_song_prev(new QPushButton("-", this)),
    btn_song_next(new QPushButton("+", this)),
    slider_volume(new QSlider(Qt::Horizontal, this)),
    file(new QMenu("&File", this)),
    act_selectOSTDirectoy(new QAction("&Select OST directoy", this)),
    act_proceed(new QAction("&Proceed", this)),
    playlist(playlist),
    player(player)
{
    slider_volume->setRange(0, max_volume);
    slider_volume->setTickInterval(1);
    //slider_volume->setTickPosition(QSlider::TicksAbove);
    slider_volume->setValue(max_volume / 2);

    layout_main_ctrl->setColumnStretch(0, 1);
    layout_main_ctrl->setColumnStretch(1, 0);
    layout_main_ctrl->setColumnStretch(2, 0);

    // set size policies
    l_title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    l_title->setAlignment(Qt::AlignLeft);
    l_ch->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    l_ch->setAlignment(Qt::AlignHCenter);
    l_song->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    l_song->setAlignment(Qt::AlignHCenter);
    btn_playpause->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    btn_proceed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    btn_reset->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    btn_ch_prev->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    btn_ch_next->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    btn_song_prev->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);
    btn_song_next->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Fixed);

    // nest widgets & layouts
    layout_title->addWidget(l_title);
    layout_main_ctrl->addWidget(btn_playpause, 0, 0, Qt::AlignLeft);
    layout_main_ctrl->addWidget(btn_proceed, 0, 1, Qt::AlignHCenter);
    layout_main_ctrl->addWidget(btn_reset, 0, 2, Qt::AlignRight);
    layout_ch_ctrl->addWidget(btn_ch_prev);
    layout_ch_ctrl->addWidget(l_ch);
    layout_ch_ctrl->addWidget(btn_ch_next);
    layout_song_ctrl->addWidget(btn_song_prev);
    layout_song_ctrl->addWidget(l_song);
    layout_song_ctrl->addWidget(btn_song_next);
    layout_volume_ctrl->addWidget(slider_volume);

    layout->addLayout(layout_title);
    layout->addLayout(layout_main_ctrl);
    layout->addLayout(layout_ch_ctrl);
    layout->addLayout(layout_song_ctrl);
    layout->addLayout(layout_volume_ctrl);
    centralWidget->setLayout(this->layout);
    this->setCentralWidget(this->centralWidget);

    // create menu bar
    file = menuBar()->addMenu("&File");
    file->addAction(act_proceed);
    file->addAction(act_selectOSTDirectoy);

    // connect slots
    connect(btn_playpause, SIGNAL(clicked()), this, SLOT(playpause_cb()));
    connect(btn_proceed, SIGNAL(clicked()), this, SLOT(proceed_cb()));
    connect(btn_reset, SIGNAL(clicked()), this, SLOT(reset_cb()));
    connect(btn_ch_prev, SIGNAL(clicked()), this, SLOT(ch_prev_cb()));
    connect(btn_ch_next, SIGNAL(clicked()), this, SLOT(ch_next_cb()));
    connect(btn_song_prev, SIGNAL(clicked()), this, SLOT(song_prev_cb()));
    connect(btn_song_next, SIGNAL(clicked()), this, SLOT(song_next_cb()));
    connect(slider_volume, SIGNAL(valueChanged(int)), this, SLOT(slider_volume_cb(int)));
    connect(act_selectOSTDirectoy, SIGNAL(triggered()), this, SLOT(selectOSTDirectoy_cb()));
    connect(act_proceed, SIGNAL(triggered()), this, SLOT(proceed_cb()));

    btn_proceed->setFocus();
}


void MainWindow::init() {
    // check for map files
    // pass qfiles to playlist
    playlist->init();
    // check for saved mp3 dir
    player->testSetAudioChain();
    player->setCurrentTrack(QString("test2.mp3"));
    // load settings, e.g. last pos and start playback
    //this->playpause_cb();
    btn_playpause->setText(player->isPlaying() ? "Pause" : "Play");
}


void MainWindow::playpause_cb()
{
    qDebug() << "playpause_cb";
    
    if (player->isPlaying()) {
        btn_playpause->setText("Play");
        player->pause();
    }
    else {
        btn_playpause->setText("Pause");
        player->setVolume((float) slider_volume->value() / max_volume);
        player->play();
    }
}


void MainWindow::proceed_cb()
{
    qDebug() << "proceed_cb";
}


void MainWindow::reset_cb()
{
    qDebug() << "reset_cb";
}


void MainWindow::ch_prev_cb()
{
    qDebug() << "ch_prev_cb";
}


void MainWindow::ch_next_cb()
{
    qDebug() << "ch_next_cb";
}


void MainWindow::song_prev_cb()
{
    qDebug() << "song_prev_cb";
}


void MainWindow::song_next_cb()
{
    qDebug() << "song_next_cb";
}


void MainWindow::slider_volume_cb(int value)
{
    qDebug() << "slider_volume_cb: " << value;
    player->setVolume((float) value/max_volume);
}


void MainWindow::selectOSTDirectoy_cb()
{
    qDebug() << "selectOSTDirectoy_cb";
    //playlist->setOSTdirectory(this->selectDirectoy(tr("Select OST directory")));
    qDebug() << this->selectDirectoy(tr("Select OST directory"));
}


QString MainWindow::selectDirectoy(const QString &caption)
{
    return QFileDialog::getExistingDirectory(this, 
            caption, 
            QDir::homePath(), 
            QFileDialog::ShowDirsOnly);
}


MainWindow::~MainWindow()
{
    
}
