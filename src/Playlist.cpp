#include "Playlist.h"
#include <QDebug>


Playlist::Playlist()
{
    qDebug() << "Created Playlist";
}


PlaylistStatus::StatusEnum Playlist::createSongMapFromFile(const QTextStream &in)
{
    return PlaylistStatus::OK;
}


PlaylistStatus::StatusEnum Playlist::createPlaylistFromFile(const QTextStream &in)
{
    return PlaylistStatus::OK;
}


PlaylistStatus::StatusEnum Playlist::setOSTDirectory(const QString &s)
{
    return PlaylistStatus::OK;
}


Playlist::~Playlist()
{
    
}
