#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QTextStream>


class PlaylistStatus {
public:
    enum StatusEnum {
        OK, Error, NoSongMapSet, NoPlaylistSet, SongMapParseFailure, PlaylistParseFailure
    };
private:
    PlaylistStatus();
};


class Playlist
{

public:
    explicit Playlist();
    ~Playlist();
    void init();
    PlaylistStatus::StatusEnum setOSTDirectory(const QString &s);
    PlaylistStatus::StatusEnum createSongMapFromFile(const QTextStream &in);
    PlaylistStatus::StatusEnum createPlaylistFromFile(const QTextStream &in);

};

#endif // PLAYLIST_H
