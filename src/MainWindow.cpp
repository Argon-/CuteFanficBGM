#include "MainWindow.h"
#include <QTextStream>


MainWindow::MainWindow(QWidget *parent, 
                       Playlist *playlist, 
                       LoopingPlayer *player) : 
    QMainWindow(parent),
    max_volume(100),
    alwaysOnTop(false),
    centralWidget(new QWidget(parent)),
    layout(new QVBoxLayout(parent)),
    layout_title(new QHBoxLayout(parent)),
    layout_main_ctrl(new QGridLayout(parent)),
    layout_ch_ctrl(new QHBoxLayout(parent)),
    layout_song_ctrl(new QHBoxLayout(parent)),
    layout_song_title(new QHBoxLayout(parent)),
    layout_volume_ctrl(new QHBoxLayout(parent)),
    l_title(new QLabel(tr("title"), this)),
    l_ch_ctrl(new QLabel(tr("chapter"), this)),
    l_song_ctrl(new QLabel(tr("song"), this)),
    l_song_title(new QLabel(tr(""), this)),
    btn_playpause(new QPushButton(tr("Pause"), this)),
    btn_proceed(new QPushButton(tr("&Proceed"), this)),
    btn_reset(new QPushButton(tr("Reset"), this)),
    btn_ch_prev(new QPushButton(" - ", this)),
    btn_ch_next(new QPushButton(" + ", this)),
    btn_song_prev(new QPushButton(tr(" - "), this)),
    btn_song_next(new QPushButton(tr(" + "), this)),
    slider_volume(new QSlider(Qt::Horizontal, this)),
    menu_controls(new QMenu(tr("Controls"), this)),
    act_playpause(new QAction(tr("Pause"), this)),
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
    l_title->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    l_title->setAlignment(Qt::AlignLeft);
    l_ch_ctrl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    l_ch_ctrl->setAlignment(Qt::AlignVCenter);
    l_ch_ctrl->setAlignment(Qt::AlignHCenter);
    l_song_ctrl->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    l_song_ctrl->setAlignment(Qt::AlignVCenter);
    l_song_ctrl->setAlignment(Qt::AlignHCenter);
    l_song_title->setAlignment(Qt::AlignVCenter);
    l_song_title->setAlignment(Qt::AlignHCenter);
    btn_playpause->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    btn_proceed->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    btn_reset->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    btn_ch_prev->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    btn_ch_next->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    btn_song_prev->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
    btn_song_next->setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);

    // nest widgets & layouts
    layout_title->addWidget(l_title);
    layout_main_ctrl->addWidget(btn_playpause, 0, 0, Qt::AlignLeft);
    layout_main_ctrl->addWidget(btn_proceed, 0, 1, Qt::AlignHCenter);
    layout_main_ctrl->addWidget(btn_reset, 0, 2, Qt::AlignRight);
    layout_ch_ctrl->addWidget(btn_ch_prev);
    layout_ch_ctrl->addWidget(l_ch_ctrl);
    layout_ch_ctrl->addWidget(btn_ch_next);
    layout_song_ctrl->addWidget(btn_song_prev);
    layout_song_ctrl->addWidget(l_song_ctrl);
    layout_song_ctrl->addWidget(btn_song_next);
    layout_song_title->addWidget(l_song_title);
    layout_volume_ctrl->addWidget(slider_volume);

    layout->addLayout(layout_title);
    layout->addLayout(layout_main_ctrl);
    layout->addLayout(layout_ch_ctrl);
    layout->addLayout(layout_song_ctrl);
    layout->addLayout(layout_song_title);
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

    act_playpause->setShortcut(QKeySequence(tr("Ctrl+A")));
    act_proceed->setShortcut(QKeySequence(tr("Ctrl+S")));
    act_reset->setShortcut(QKeySequence(tr("Ctrl+D")));
    act_ch_next->setShortcut(QKeySequence(tr("Ctrl++")));
    act_ch_prev->setShortcut(QKeySequence(tr("Ctrl+-")));
    //act_song_next->setShortcut(QKeySequence(tr("Shift++")));
    //act_song_prev->setShortcut(QKeySequence(tr("Shift+-")));

    //act_selectPlaylist->setShortcut(QKeySequence(tr("Shift+L")));
    //act_selectSonglist->setShortcut(QKeySequence(tr("Shift+S")));
    //act_selectSongDirectoy->setShortcut(QKeySequence(tr("Shift+D")));
    //act_always_on_top->setShortcut(QKeySequence(tr("Shift+A")));

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

    // retrieve song dir
    QString spath = settings->value("location/songs", "/").toString();
    if (!QFile::exists(spath)) {
        spath = QFileDialog::getExistingDirectory(this, 
                        tr("Please select a song directory"), 
                        /*QDir::homePath()*/ "", QFileDialog::ShowDirsOnly);
    }
    if (!this->setSongDirectory(spath, true, tr("Quit"))) {
        this->close();
        return;
    }
    settings->setValue("location/songs", spath);
    QTextStream(stdout) << "song dir: " << spath << endl;
    
    // retrieve songlist
    QString slpath = settings->value("location/songlist", "Songlist.txt").toString();
    if (!QFile::exists(slpath)) {
        slpath = this->promptForFile(tr("Please select a songlist"));
    }
    if (!this->setSonglistFile(slpath, true, tr("Quit"))) {
        this->close();
        return;
    }
    settings->setValue("location/songlist", slpath);
    QTextStream(stdout) << "songlist: " << slpath << " (" 
                        << playlist->getSongMapChecksum() << ")" << endl;

    // check if every song actually exists
    if (playlist->checkSongDirectory() != PlaylistStatus::OK) {
        this->displayError(tr("File(s) not found."), 
                           tr("One or more songs were not found. See log for details. \
                              Please try a different song directory or validate our songlist."), 
                           true, tr("Quit"));
        this->close();
        return;
    }

    // retrieve playlist
    QString ppath = settings->value("location/playlist", "Sisterhood.txt").toString();
    if (!QFile::exists(ppath)) {
        ppath = this->promptForFile(tr("Please select a playlist"));
    }
    if (!this->setPlaylistFile(ppath, true, tr("Quit"))) {
        this->close();
        return;
    }
    settings->setValue("location/playlist", ppath);
    QTextStream(stdout) << "playlist: " << ppath  << " (" 
                        << playlist->getPlaylistChecksum() << ")" << endl;


    // load and apply settings

    // always on top
    this->alwaysOnTop = settings->value("state/window/always_on_top", 
                                        false).toBool();
    if (this->alwaysOnTop) {
        this->setWindowFlags(this->windowFlags() | 
                             Qt::CustomizeWindowHint | 
                             Qt::WindowStaysOnTopHint);
        this->show();
    }

    // playback volume
    int vol = settings->value("state/player/volume", this->max_volume/2).toInt();
    slider_volume->setValue(vol);
    player->setVolume(vol);

    // current chapter
    bool loadedListDoesNotMatchChecksum = false;
    QString pcs = settings->value("location/playlist_checksum", "").toString();
    if (!pcs.isEmpty() && pcs == playlist->getPlaylistChecksum())
    {
        bool ok;
        int n = settings->value("state/playlist/current_chapter_num", "").toInt(&ok);
        PlaylistStatus s1 = playlist->setCurrentChapterByNumber(n);

        // current song
        QString scs = settings->value("location/songlist_checksum", "").toString();
        if (ok && s1 == PlaylistStatus::OK && !scs.isEmpty() && scs == playlist->getSongMapChecksum())
        {
            bool ok;
            int m = settings->value("state/playlist/current_song_num", "").toInt(&ok);
            PlaylistStatus s2 = playlist->setCurrentSongByNumber(m);

            // playback state
            if (ok && s2 == PlaylistStatus::OK) {
                QTextStream(stdout) << "successfully restored progress" << endl;
                if (settings->value("state/player/playing", false).toBool()) {
                    player->play();
                }
            }
            else {
                loadedListDoesNotMatchChecksum = true;
            }
        }
        else {
            loadedListDoesNotMatchChecksum = true;
        }
    }
    else {
        loadedListDoesNotMatchChecksum = true;
    }

    // when loaded lists (i.e., old path was still fine) have changed content,
    // the checksums won't match (as expected) so we need new "base values"
    if (loadedListDoesNotMatchChecksum) {
        QTextStream(stdout) << "playlist/songlist changed, setting new base values" << endl;
        settings->setValue("location/playlist_checksum", playlist->getPlaylistChecksum());
        settings->setValue("location/songlist_checksum", playlist->getSongMapChecksum());
        settings->setValue("state/playlist/current_chapter_num", playlist->getCurrentChapterNumber());
        settings->setValue("state/playlist/current_song_num", playlist->getCurrentSongNumber());
        settings->setValue("state/player/playing", false);
    }
    
    this->updateLabels();
    btn_playpause->setText(player->isPlaying() ? tr("Pause") : tr("Play"));
    act_playpause->setText(player->isPlaying() ? tr("Pause") : tr("Play"));
}


void MainWindow::playpause_cb()
{    
    if (player->isPlaying()) {
        btn_playpause->setText(tr("Play"));
        act_playpause->setText(tr("Play"));
        player->pause();
    }
    else {
        btn_playpause->setText(tr("Pause"));
        act_playpause->setText(tr("Pause"));
        player->setVolume(slider_volume->value());
        player->play();
    }
    settings->setValue("state/player/playing", player->isPlaying());
}


void MainWindow::proceed_cb()
{
    playlist->nextSong(false);
    settings->setValue("state/playlist/current_chapter_num", playlist->getCurrentChapterNumber());
    settings->setValue("state/playlist/current_song_num", playlist->getCurrentSongNumber());
    this->updateLabels();
}


void MainWindow::reset_cb()
{
    // chapter/song
    playlist->reset();
    settings->setValue("state/playlist/current_chapter_num", playlist->getCurrentChapterNumber());
    settings->setValue("state/playlist/current_song_num", playlist->getCurrentSongNumber());
    this->updateLabels();
    // volume
    slider_volume->setValue(this->max_volume/2);
    player->setVolume(this->max_volume/2);
    settings->setValue("state/player/volume", this->max_volume/2);
    // playback
    if (player->isPlaying()) {
        btn_playpause->setText(tr("Play"));
        act_playpause->setText(tr("Play"));
        player->pause();
    }
    settings->setValue("state/player/playing", false);
}


void MainWindow::ch_prev_cb()
{
    playlist->prevChapter();
    settings->setValue("state/playlist/current_chapter_num", playlist->getCurrentChapterNumber());
    settings->setValue("state/playlist/current_song_num", playlist->getCurrentSongNumber());
    this->updateLabels();
}


void MainWindow::ch_next_cb()
{
    playlist->nextChapter();
    settings->setValue("state/playlist/current_chapter_num", playlist->getCurrentChapterNumber());
    settings->setValue("state/playlist/current_song_num", playlist->getCurrentSongNumber());
    this->updateLabels();
}


void MainWindow::song_prev_cb()
{
    playlist->prevSong();
    settings->setValue("state/playlist/current_chapter_num", playlist->getCurrentChapterNumber());
    settings->setValue("state/playlist/current_song_num", playlist->getCurrentSongNumber());
    this->updateLabels();
}


void MainWindow::song_next_cb()
{
    playlist->nextSong();
    settings->setValue("state/playlist/current_chapter_num", playlist->getCurrentChapterNumber());
    settings->setValue("state/playlist/current_song_num", playlist->getCurrentSongNumber());
    this->updateLabels();
}


void MainWindow::slider_volume_cb(int value)
{
    player->setVolume(value);
    settings->setValue("state/player/volume", value);
}


void MainWindow::updateLabels()
{
    player->setTrack(playlist->getCurrentSongPath(), playlist->loopCurrentSong());
    this->l_title->setText(playlist->getTitle());
    this->l_ch_ctrl->setText(playlist->getCurrentChapter());
    this->l_song_ctrl->setText(tr("Song: ") + playlist->getCurrentSong());
    this->l_song_title->setText(playlist->getCurrentSongName());
}


void MainWindow::selectAndSetSonglistFile_cb()
{
    QString s = this->promptForFile(tr("Please select a songlist"));
    if (!this->setSonglistFile(s)) {
        return;
    }

    QTextStream(stdout) << "new songlist file: " << s << endl;
    settings->setValue("location/songlist", s);
    settings->setValue("location/songlist_checksum", playlist->getSongMapChecksum());
    this->updateLabels();
}


bool MainWindow::setSonglistFile(const QString &s, 
                                 const bool criticalWarning, 
                                 const QString &buttonText)
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
    PlaylistStatus r = playlist->createSongMapFromFile(in);
    if (r != PlaylistStatus::OK) {
        if (r == PlaylistStatus::ParseFailure) {
            this->displayError(tr("Invalid file."), 
                               playlist->getLastParseError(), 
                               criticalWarning, buttonText);
        }
        else {
            this->displayError(tr("Invalid file."), 
                               tr("Content of file \"") + s + 
                               tr("\" is not correctly formatted."), 
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

    QTextStream(stdout) << "new playlist file: " << s << endl;
    settings->setValue("location/playlist", s);
    settings->setValue("location/playlist_checksum", playlist->getPlaylistChecksum());
    this->updateLabels();
}


bool MainWindow::setPlaylistFile(const QString &s, 
                                 const bool criticalWarning, 
                                 const QString &buttonText)
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
    PlaylistStatus r = playlist->createPlaylistFromFile(in);
    if (r != PlaylistStatus::OK) {
        if (r == PlaylistStatus::ParseFailure) {
            this->displayError(tr("Invalid file."), 
                               playlist->getLastParseError(), 
                               criticalWarning, buttonText);
        }
        else {
            this->displayError(tr("Invalid file."), 
                               tr("Content of file \"") + s + 
                               tr("\" is not correctly formatted."), 
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
                    /*QDir::homePath()*/ "", QFileDialog::ShowDirsOnly);
    if (!this->setSongDirectory(s)) {
        return;
    }

    QTextStream(stdout) << "new song directory: " << s << endl;
    settings->setValue("location/songs", s);
    this->updateLabels();
}


bool MainWindow::setSongDirectory(const QString &s, 
                                  const bool criticalWarning, 
                                  const QString &buttonText)
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


void MainWindow::displayError(const QString &errorText, 
                              const QString &informativeText, 
                              const bool criticalWarning, 
                              const QString &buttonText)
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
            /*QDir::homePath()*/ "");
}


void MainWindow::toggleAlwaysOnTop()
{
    this->alwaysOnTop = !this->alwaysOnTop;
    settings->setValue("state/window/always_on_top", this->alwaysOnTop);
    if (this->alwaysOnTop) {
        this->setWindowFlags(this->windowFlags() | 
                             Qt::CustomizeWindowHint | 
                             Qt::WindowStaysOnTopHint);
        this->show();
    }
    else {
        // assumption: this is never called without both flags set, otherwhise
        // they are added and not removed
        this->setWindowFlags(this->windowFlags() ^ 
                             (Qt::CustomizeWindowHint | 
                              Qt::WindowStaysOnTopHint));
        this->show();
    }
}


MainWindow::~MainWindow()
{
    
}
