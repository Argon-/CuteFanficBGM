#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QTextStream>
#include <QList>
#include <QHash>
#include <QPair>


class PlaylistStatus {
public:
    enum StatusEnum {
        OK, 
        Uninitialized, 
        EmptyFile, 
        EmptySongDirectory, 
        PartialSongDirectory,
        ParseFailure
    };
private:
    PlaylistStatus();
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
    PlaylistStatus::StatusEnum createPlaylistFromFile(QTextStream &in);
    PlaylistStatus::StatusEnum createSongMapFromFile(QTextStream &in);
    PlaylistStatus::StatusEnum setSongDirectory(const QString &s);
    PlaylistStatus::StatusEnum checkSongDirectory();

    PlaylistStatus::StatusEnum status();
    PlaylistStatus::StatusEnum nextChapter();
    PlaylistStatus::StatusEnum prevChapter();
    PlaylistStatus::StatusEnum nextSong(bool turnAround = true);
    PlaylistStatus::StatusEnum prevSong(bool turnAround = true);
    PlaylistStatus::StatusEnum reset();
    QString getCurrentChapter();
    QString getCurrentSong();
    QString getCurrentSongName();
    QString getLastParseError();
    QString getTitle();
    void printPlaylist();

private:
    inline QString getSongPath(const QString &s);

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
    PlaylistStatus::StatusEnum lastStatus;

};

#endif // PLAYLIST_H
