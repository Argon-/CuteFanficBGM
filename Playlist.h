#ifndef PLAYLIST_H
#define PLAYLIST_H

#include <QTextStream>


class Playlist
{

public:
    explicit Playlist();
    ~Playlist();
    void init();
    void setOSTDirectory(const QString &s);
    bool createSongMapFromFile(QTextStream &in);
    bool createPlaylistFromFile(QTextStream &in);

};

#endif // PLAYLIST_H
