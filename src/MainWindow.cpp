#include "MainWindow.h"
#include <QDebug>


MainWindow::MainWindow(QWidget *parent, Playlist *playlist, LoopingPlayer *player) : 
    QMainWindow(parent),
    max_volume(100),
    alwaysOnTop(false),
    centralWidget(new QWidget(parent)),
    layout(new QVBoxLayout(parent)),
    layout_title(new QHBoxLayout(parent)),
    layout_main_ctrl(new QGridLayout(parent)),
    layout_ch_ctrl(new QHBoxLayout(parent)),
    layout_song_ctrl(new QHBoxLayout(parent)),
    layout_volume_ctrl(new QHBoxLayout(parent)),
    l_title(new QLabel(tr("title"), this)),
    l_ch(new QLabel(tr("chapter"), this)),
    l_song(new QLabel(tr("song"), this)),
    btn_playpause(new QPushButton(tr("Play"), this)),
    btn_proceed(new QPushButton(tr("&Proceed"), this)),
    btn_reset(new QPushButton(tr("Reset"), this)),
    btn_ch_prev(new QPushButton(tr("-"), this)),
    btn_ch_next(new QPushButton(tr("+"), this)),
    btn_song_prev(new QPushButton(tr("-"), this)),
    btn_song_next(new QPushButton(tr("+"), this)),
    slider_volume(new QSlider(Qt::Horizontal, this)),
    menu_controls(new QMenu(tr("Controls"), this)),
    act_playpause(new QAction(tr("Play"), this)),
    act_proceed(new QAction(tr("Proceed"), this)),
    act_reset(new QAction(tr("Reset"), this)),
    act_ch_next(new QAction(tr("Next chapter"), this)),
    act_ch_prev(new QAction(tr("Previous chapter"), this)),
    act_song_next(new QAction(tr("Next song"), this)),
    act_song_prev(new QAction(tr("Previous song"), this)),
    menu_settings(new QMenu(tr("Settings"), this)),
    act_selectPlaylist(new QAction(tr("&Select playlist"), this)),
    act_selectSonglist(new QAction(tr("&Select songlist"), this)),
    act_selectSongDirectoy(new QAction(tr("&Select song directoy"), this)),
    act_always_on_top(new QAction(tr("&Always On Top"), this)),
    settings(new QSettings(this)),
    playlist(playlist),
    player(player)
{
    slider_volume->setRange(0, max_volume);
    slider_volume->setValue(max_volume / 2);
    slider_volume->setTickInterval(1);
    //slider_volume->setTickPosition(QSlider::TicksAbove);

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
    menuBar()->addMenu(menu_controls);
    menu_controls->addAction(act_playpause);
    menu_controls->addAction(act_proceed);
    menu_controls->addAction(act_reset);
    menu_controls->addSeparator();
    menu_controls->addAction(act_ch_next);
    menu_controls->addAction(act_ch_prev);
    menu_controls->addAction(act_song_next);
    menu_controls->addAction(act_song_prev);

    menuBar()->addMenu(menu_settings);
    menu_settings->addAction(act_selectPlaylist);
    menu_settings->addAction(act_selectSonglist);
    menu_settings->addAction(act_selectSongDirectoy);
    menu_settings->addSeparator();
    menu_settings->addAction(act_always_on_top);

    act_playpause->setShortcut(QKeySequence(tr("Ctrl+P")));
    act_proceed->setShortcut(QKeySequence(tr("P")));
    act_reset->setShortcut(QKeySequence(tr("R")));
    act_ch_next->setShortcut(QKeySequence(tr("Ctrl++")));
    act_ch_prev->setShortcut(QKeySequence(tr("Ctrl+-")));
    act_song_next->setShortcut(QKeySequence(tr("Shift++")));
    act_song_prev->setShortcut(QKeySequence(tr("Shift++")));

    act_selectPlaylist->setShortcut(QKeySequence(tr("Shift+P")));
    act_selectSonglist->setShortcut(QKeySequence(tr("Shift+S")));
    act_selectSongDirectoy->setShortcut(QKeySequence(tr("Shift+D")));
    act_always_on_top->setShortcut(QKeySequence(tr("Shift+A")));

    // connect slots
    connect(btn_playpause, SIGNAL(clicked()), this, SLOT(playpause_cb()));
    connect(btn_proceed,   SIGNAL(clicked()), this, SLOT(proceed_cb()));
    connect(btn_reset,     SIGNAL(clicked()), this, SLOT(reset_cb()));
    connect(btn_ch_prev,   SIGNAL(clicked()), this, SLOT(ch_prev_cb()));
    connect(btn_ch_next,   SIGNAL(clicked()), this, SLOT(ch_next_cb()));
    connect(btn_song_prev, SIGNAL(clicked()), this, SLOT(song_prev_cb()));
    connect(btn_song_next, SIGNAL(clicked()), this, SLOT(song_next_cb()));
    connect(slider_volume, SIGNAL(valueChanged(int)), this, SLOT(slider_volume_cb(int)));

    connect(act_playpause, SIGNAL(triggered()), this, SLOT(playpause_cb()));
    connect(act_proceed,   SIGNAL(triggered()), this, SLOT(proceed_cb()));
    connect(act_reset,     SIGNAL(triggered()), this, SLOT(reset_cb()));
    connect(act_ch_next,   SIGNAL(triggered()), this, SLOT(ch_next_cb()));
    connect(act_ch_prev,   SIGNAL(triggered()), this, SLOT(ch_prev_cb()));
    connect(act_song_next, SIGNAL(triggered()), this, SLOT(song_next_cb()));
    connect(act_song_prev, SIGNAL(triggered()), this, SLOT(song_prev_cb()));

    connect(act_selectPlaylist,    SIGNAL(triggered()), this, SLOT(selectAndSetPlaylistFile_cb()));
    connect(act_selectSonglist,    SIGNAL(triggered()), this, SLOT(selectAndSetSonglistFile_cb()));
    connect(act_selectSongDirectoy,SIGNAL(triggered()), this, SLOT(selectAndSetSongDirectory_cb()));
    connect(act_always_on_top,     SIGNAL(triggered()), this, SLOT(toggleAlwaysOnTop()));

    btn_proceed->setFocus();
    QTimer::singleShot(0, this, SLOT(init()));
}


void MainWindow::init() {
    QString path;

    // retrieve song dir
    path = settings->value("location/songs", "/").toString();
    if (!QFile::exists(path)) {
        path = QFileDialog::getExistingDirectory(this, tr("Select song directory"), QDir::homePath(), QFileDialog::ShowDirsOnly);
    }
    if (!this->setSongDirectory(path, true, tr("Quit"))) {
        this->close();
        return;
    }
    settings->setValue("location/songs", path);
    qDebug() << "song dir: " << path;

    
    // retrieve songlist
    path = settings->value("location/songlist", "Songlist.txt").toString();
    if (!QFile::exists(path)) {
        path = this->promptForFile(tr("Please select a songlist"));
    }
    if (!this->setSonglistFile(path, true, tr("Quit"))) {
        this->close();
        return;
    }
    settings->setValue("location/songlist", path);
    qDebug() << "songlist: " << path;


    // check if every song actually exists
    if (playlist->checkSongDirectory() != PlaylistStatus::OK) {
        this->displayError(tr("File(s) not found."), 
                           tr("One or more songs were not found. See log for details."), 
                           true, tr("Quit"));
        this->close();
        return;
    }


    // retrieve playlist
    path = settings->value("location/playlist", "Sisterhood.txt").toString();
    if (!QFile::exists(path)) {
        path = this->promptForFile(tr("Please select a playlist"));
    }
    if (!this->setPlaylistFile(path, true, tr("Quit"))) {
        this->close();
        return;
    }
    settings->setValue("location/playlist", path);
    qDebug() << "playlist: " << path;






    // load settings, e.g. last pos and start playback, volume, file locations




    player->testSetAudioChain();
    player->setCurrentTrack(QString("resources/test2.mp3"));
    // load settings, e.g. last pos and start playback, volume, file locations
    //this->playpause_cb();
    btn_playpause->setText(player->isPlaying() ? tr("Pause") : tr("Play"));
    act_playpause->setText(player->isPlaying() ? tr("Pause") : tr("Play"));
    this->l_title->setText(playlist->getTitle());
}


void MainWindow::playpause_cb()
{
    qDebug() << "playpause_cb";
    
    if (player->isPlaying()) {
        btn_playpause->setText(tr("Play"));
        act_playpause->setText(tr("Play"));
        player->pause();
    }
    else {
        btn_playpause->setText(tr("Pause"));
        act_playpause->setText(tr("Pause"));
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


void MainWindow::selectAndSetSonglistFile_cb()
{
    QString s = this->promptForFile(tr("Please select a songlist"));
    if (!this->setSonglistFile(s)) {
        return;
    }

    QTextStream(stdout) << "New SonglistFile: " << s << endl;
    settings->setValue("location/songlist", s);
}


bool MainWindow::setSonglistFile(const QString &s, const bool criticalWarning, const QString &buttonText)
{
    if (!QFile::exists(s)) {
        this->displayError(tr("File not found."), 
                           "\"" + s + tr("\" is not a valid file."), 
                           criticalWarning, buttonText);
        return false;
    }
    
    QFile f(s);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->displayError(tr("File not accessible."), 
                           tr("Unable to read file \"") + s + "\"", 
                           criticalWarning, buttonText);
        return false;
    }

    QTextStream in(&f);
    PlaylistStatus::StatusEnum r = playlist->createSongMapFromFile(in);
    if (r != PlaylistStatus::OK) {
        if (r == PlaylistStatus::ParseFailure) {
            this->displayError(tr("Invalid file."), 
                               playlist->getLastParseError(), 
                               criticalWarning, buttonText);
        }
        else {
            this->displayError(tr("Invalid file."), 
                               tr("Content of file \"") + s + tr("\" is not correctly formatted."), 
                               criticalWarning, buttonText);
        }
        return false;
    }
    return true;
}


void MainWindow::selectAndSetPlaylistFile_cb()
{
    QString s = this->promptForFile(tr("Please select a playlist"));
    if (!this->setPlaylistFile(s)) {
        return;
    }

    QTextStream(stdout) << "New PlaylistFile: " << s << endl;
    settings->setValue("location/playlist", s);
}


bool MainWindow::setPlaylistFile(const QString &s, const bool criticalWarning, const QString &buttonText)
{
    if (!QFile::exists(s)) {
        this->displayError(tr("File not found."), 
                           "\"" + s + tr("\" is not a valid file."), 
                           criticalWarning, buttonText);
        return false;
    }
    
    QFile f(s);
    if (!f.open(QIODevice::ReadOnly | QIODevice::Text)) {
        this->displayError(tr("File not accessible."), 
                           tr("Unable to read file \"") + s + "\"", 
                           criticalWarning, buttonText);
        return false;
    }

    QTextStream in(&f);
    PlaylistStatus::StatusEnum r = playlist->createPlaylistFromFile(in);
    if (r != PlaylistStatus::OK) {
        if (r == PlaylistStatus::ParseFailure) {
            this->displayError(tr("Invalid file."), 
                               playlist->getLastParseError(), 
                               criticalWarning, buttonText);
        }
        else {
            this->displayError(tr("Invalid file."), 
                               tr("Content of file \"") + s + tr("\" is not correctly formatted."), 
                               criticalWarning, buttonText);
        }
        return false;
    }
    return true;
}


void MainWindow::selectAndSetSongDirectory_cb()
{
    QString s = QFileDialog::getExistingDirectory(this, 
                    tr("Select song directory"), 
                    QDir::homePath(), QFileDialog::ShowDirsOnly);
    if (!this->setSongDirectory(s)) {
        return;
    }

    QTextStream(stdout) << "New SongDirectory: " << s << endl;
    settings->setValue("location/songs", s);
}


bool MainWindow::setSongDirectory(const QString &s, const bool criticalWarning, const QString &buttonText)
{
    if (s.isNull() || s.isEmpty() || !QDir(s).exists()) {
        this->displayError(tr("Invalid directory."), 
                           "\"" + s + tr("\" is not a valid directory."), 
                           criticalWarning, buttonText);
        return false;
    }

    if (playlist->setSongDirectory(s) != PlaylistStatus::OK) {
        this->displayError(tr("Invalid directory."), 
                           "\"" + s + tr("\" is not a valid directory."), 
                           criticalWarning, buttonText);
        return false;
    }
    return true;
}


void MainWindow::displayError(const QString &errorText, const QString &informativeText, const bool criticalWarning, const QString &buttonText)
{
    QTextStream(stderr) << errorText << " => " << informativeText << endl;
    QMessageBox msg;
    msg.setIcon(criticalWarning ? QMessageBox::Critical : QMessageBox::Warning);
    msg.setText(errorText);
    msg.setInformativeText(informativeText);
    msg.addButton(buttonText, QMessageBox::AcceptRole);
    msg.exec();
}


QString MainWindow::promptForFile(const QString &prompt)
{
    return QFileDialog::getOpenFileName(0, 
            prompt,
            //"Please select a songlist (" + s + ")", 
            //QDir::homePath()
            "");
}


void MainWindow::toggleAlwaysOnTop()
{
    this->alwaysOnTop = !this->alwaysOnTop;
    if (alwaysOnTop) {
        this->setWindowFlags(this->windowFlags() | Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint);
        this->show();
    }
    else {
        this->setWindowFlags(this->windowFlags() ^ (Qt::CustomizeWindowHint | Qt::WindowStaysOnTopHint));
        this->show();
    }
}


MainWindow::~MainWindow()
{
    
}
