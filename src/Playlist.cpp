#include "Playlist.h"
#include <QDebug>



Playlist::Playlist()
{
    qDebug() << "Created Playlist";
}


bool Playlist::createSongMapFromFile(QTextStream &in)
{
    return true;
}


bool Playlist::createPlaylistFromFile(QTextStream &in)
{
    return true;
}


void Playlist::setOSTDirectory(const QString &s)
{
}


Playlist::~Playlist()
{
    
}
