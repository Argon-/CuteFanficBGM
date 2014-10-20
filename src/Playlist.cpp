#include "Playlist.h"
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QDir>
#include <QDebug>


Playlist::Playlist(const QString &playListSeparator, 
                   const QString &playListSongSeparator, 
                   const QString &playListTerminator,
                   const QString &songMapSeparator) : 
    playListSeparator(playListSeparator),
    playListSongSeparator(playListSongSeparator),
    playListTerminator(playListTerminator),
    songMapSeparator(songMapSeparator),
    songDirectory(QString("")),
    title(QString("")),
    lastParseError(QString(""))
{
}


PlaylistStatus::StatusEnum Playlist::nextChapter() {
    if (this->playList.isEmpty()) {
        this->lastStatus = PlaylistStatus::Uninitialized;
        return this->lastStatus;
    }

    if (this->playList.size() > 1) {
        ++this->currentChapter;
        if (this->currentChapter == this->playList.constEnd())
            this->currentChapter = this->playList.constBegin();
    }
    this->currentSong = this->currentChapter->second.constBegin();
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


PlaylistStatus::StatusEnum Playlist::prevChapter() {
    if (this->playList.isEmpty()) {
        this->lastStatus = PlaylistStatus::Uninitialized;
        return this->lastStatus;
    }

    if (this->playList.size() > 1) {
        if (this->currentChapter == this->playList.constBegin())
            this->currentChapter = this->playList.constEnd();
        --this->currentChapter;
    }
    this->currentSong = this->currentChapter->second.constBegin();
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


PlaylistStatus::StatusEnum Playlist::nextSong() {
    if (this->currentChapter->second.isEmpty()) {
        this->lastStatus = PlaylistStatus::Uninitialized;
        return this->lastStatus;
    }

    if (this->currentChapter->second.size() > 1) {
        ++this->currentSong;
        if (this->currentSong == this->currentChapter->second.constEnd())
            this->currentSong = this->currentChapter->second.constBegin();
    }
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


PlaylistStatus::StatusEnum Playlist::prevSong() {
    if (this->currentChapter->second.isEmpty()) {
        this->lastStatus = PlaylistStatus::Uninitialized;
        return this->lastStatus;
    }

    if (this->currentChapter->second.size() > 1) {
        if (this->currentSong == this->currentChapter->second.constBegin())
            this->currentSong = this->currentChapter->second.constEnd();
        --this->currentSong;
    }
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


void Playlist::printPlaylist()
{
    QList<QPair<QString, QList<int> > >::const_iterator i;
        for (i = playList.constBegin(); i != playList.constEnd(); ++i) {
            qDebug() << "Currently at:" << i->first;
            QList<int>::const_iterator e;
            for (e = i->second.constBegin(); e != i->second.constEnd(); ++e) {
                qDebug() << "   " << *e << " (" << this->songMap.value(*e, "???") << ")";
            }
        }
}


QString Playlist::getCurrentChapter() {
    return currentChapter->first;
}


QString Playlist::getCurrentSong() {
    this->lastStatus = PlaylistStatus::OK;
    qDebug() << "Playlist::getCurrentSong:" << *this->currentSong;
    return QString::number(*this->currentSong);
}


QString Playlist::getCurrentSongName() {
    this->lastStatus = PlaylistStatus::OK;
    return this->songMap.value(*currentSong, "???");
}


PlaylistStatus::StatusEnum Playlist::createPlaylistFromFile(QTextStream &in)
{
    // empty file?
    if (in.atEnd()) {
        this->lastStatus = PlaylistStatus::EmptyFile;
        return this->lastStatus;
    }
    this->title = in.readLine();

    QList<QPair<QString, QList<int> > > newList;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty())
            continue;

        // is there even a separator?
        // not really required, main purpose is to give better error messages
        if (!line.contains(playListSeparator)) {
            this->lastParseError = QObject::tr("no separator \"") + playListSeparator + 
                                    QObject::tr("\" found in line: \"") + line + "\"";
            this->lastStatus = PlaylistStatus::ParseFailure;
            return this->lastStatus;
        }

        // remove line terminator
        if (playListTerminator == line.at(line.length() - 1))
            line.remove(line.length() - 1, 1);
        else
            QTextStream(stdout) << "warning: line is not properly terminated: " << line << endl;

        QStringList split = line.split(playListSeparator, QString::SkipEmptyParts);

        // an existing separator does not guarantee two splits (QString::SkipEmptyParts)
        if (split.size() < 2) {
            this->lastParseError = QObject::tr("invalid syntax in line: \"") + line + "\"";
            this->lastStatus = PlaylistStatus::ParseFailure;
            return this->lastStatus;
        }

        QString chapter = split.takeFirst();

        // create list of song ids
        // this might actually be empty, that's fine
        QStringList songIDList = split.join(playListSeparator).split(playListSongSeparator, QString::SkipEmptyParts);
        QList<int> songs;

        QStringList::const_iterator i;
        for (i = songIDList.constBegin(); i != songIDList.constEnd(); ++i) {
            bool ok;
            int n = i->toInt(&ok);
            if (!ok) {
                this->lastParseError = QObject::tr("song ID \"") + *i + QObject::tr("\" is not a valid number, in line: \"") + line + "\"";
                this->lastStatus = PlaylistStatus::ParseFailure;
                return this->lastStatus;
            }
            songs.append(n);
        }
        // wrap it all into a pair and append the data
        newList.append(QPair<QString, QList<int> >(chapter, songs));
    }

    this->playList = newList;
    this->currentChapter = this->playList.constBegin();
    this->currentSong = currentChapter->second.constBegin();
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


PlaylistStatus::StatusEnum Playlist::createSongMapFromFile(QTextStream &in)
{
    // empty file?
    if (in.atEnd()) {
        this->lastStatus = PlaylistStatus::EmptyFile;
        return this->lastStatus;
    }

    QHash<int, QString> newMap;

    while (!in.atEnd()) {
        QString line = in.readLine();
        if (line.isEmpty())
            continue;

        // is there even a separator?
        if (!line.contains(songMapSeparator)) {
            this->lastParseError = QObject::tr("no separator \"") + songMapSeparator + 
                                    QObject::tr("\" found in line: \"") + line + "\"";
            this->lastStatus = PlaylistStatus::ParseFailure;
            return this->lastStatus;
        }

        QStringList split = line.split(songMapSeparator, QString::KeepEmptyParts);

        // an existing separator does not guarantee two splits
        // well, it does with QString::KeepEmptyParts but that's subject to change
        if (split.size() < 2) {
            this->lastParseError = QObject::tr("invalid syntax in line: \"") + line + "\"";
            this->lastStatus = PlaylistStatus::ParseFailure;
            return this->lastStatus;
        }

        // we need this because we split with QString::KeepEmptyParts
        if (split.first().isEmpty()) {
            this->lastParseError = QObject::tr("missing song ID in line: \"") + line + "\"";
            this->lastStatus = PlaylistStatus::ParseFailure;
            return this->lastStatus;
        }

        // is the first part really a number?
        bool ok;
        QString tmp = split.takeFirst();
        int key = tmp.toInt(&ok);
        if (!ok) {
            this->lastParseError = QObject::tr("song ID \"") + tmp + QObject::tr("\" is not a valid number, in line: \"") + line + "\"";
            this->lastStatus = PlaylistStatus::ParseFailure;
            return this->lastStatus;
        }

        // use as value whatever comes after <ID><separator>
        newMap.insert(key, split.join(songMapSeparator));
    }

    this->songMap = newMap;
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


PlaylistStatus::StatusEnum Playlist::setSongDirectory(const QString &s)
{
    if (!s.isNull() && !s.isEmpty()) {
        this->songDirectory = s;
        this->lastStatus = PlaylistStatus::OK;
        return this->lastStatus;
    }

    this->lastStatus = PlaylistStatus::EmptySongDirectory;
    return this->lastStatus;
}


PlaylistStatus::StatusEnum Playlist::checkSongDirectory()
{
    int e = 0;
    QHash<int, QString>::const_iterator i = this->songMap.constBegin();
    while (i != songMap.constEnd()) {
        if (!QFileInfo(getSongPath(i.value())).isFile()) {
            QTextStream(stderr) << "file does not exist: " << getSongPath(i.value()) << endl;
            ++e;
        }
        ++i;
    }

    if (e > 0) {
        this->lastStatus = PlaylistStatus::PartialSongDirectory;
        return this->lastStatus;
    }

    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


inline QString Playlist::getSongPath(const QString &s)
{
    this->lastStatus = PlaylistStatus::OK;
    return this->songDirectory + QDir::separator() + s;
}


QString Playlist::getTitle()
{
    this->lastStatus = PlaylistStatus::OK;
    return this->title;
}


PlaylistStatus::StatusEnum Playlist::status()
{
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


QString Playlist::getLastParseError()
{
    this->lastStatus = PlaylistStatus::OK;
    return this->lastParseError;
}


Playlist::~Playlist()
{
}
