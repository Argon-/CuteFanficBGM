#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QTextStream>
#include <QList>
#include <QHash>
#include <QPair>



enum class PlaylistStatus {
    OK, 
    Uninitialized, 
    EmptyFile, 
    EmptySongDirectory, 
    PartialSongDirectory,
    ParseFailure,
    InvalidNumbersSet
};


class Playlist
{

public:
    explicit Playlist(const QString &playListSeparator = "::", 
                      const QString &playListSongSeparator = ",",
                      const QString &playListTerminator = ";", 
                      const QString &songMapSeparator = ":");
    ~Playlist();
    void init();
    PlaylistStatus createPlaylistFromFile(QTextStream &in);
    PlaylistStatus createSongMapFromFile(QTextStream &in);
    PlaylistStatus setSongDirectory(const QString &s);
    PlaylistStatus checkSongDirectory();

    PlaylistStatus status();
    PlaylistStatus nextChapter();
    PlaylistStatus prevChapter();
    PlaylistStatus nextSong(bool turnAround = true);
    PlaylistStatus prevSong(bool turnAround = true);
    PlaylistStatus reset();
    QString getCurrentChapter();
    QString getCurrentSong();

    QString getCurrentSongName();
    QString getCurrentSongPath();
    QString getLastParseError();
    QString getTitle();
    QString getPlaylistChecksum();
    QString getSongMapChecksum();
    int getCurrentChapterNumber();
    int getCurrentSongNumber();
    PlaylistStatus setCurrentChapterByNumber(const int i);
    PlaylistStatus setCurrentSongByNumber(const int i);
    bool loopCurrentSong();
    void printPlaylist();

private:
    QString getSongPath(const QString &s);

    const QString playListSeparator;
    const QString playListSongSeparator;
    const QString playListTerminator;
    const QString songMapSeparator;

    QList<QPair<QString, QList<int> > > playList;
    QHash<int, QString> songMap;

    QList<QPair<QString, QList<int> > >::const_iterator currentChapter;
    QList<int>::const_iterator currentSong;

    QString songDirectory;
    QString title;

    QString lastParseError;
    PlaylistStatus lastStatus;

    QString playlistChecksum;
    QString songMapChecksum;

};

#endif // PLAYLIST_H
