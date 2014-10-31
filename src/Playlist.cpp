/* This file is part of CuteFanficBGM.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */
 
#include "Playlist.h"
#include <QTextStream>
#include <QFileInfo>
#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <QCryptographicHash>



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


PlaylistStatus Playlist::nextChapter() 
{
    if (this->playList.isEmpty()) {
        this->lastStatus = PlaylistStatus::Uninitialized;
        return this->lastStatus;
    }

    if (this->playList.size() > 1) {
        ++this->currentChapter;
        if (this->currentChapter == this->playList.constEnd()) {
            this->currentChapter = this->playList.constBegin();
        }
    }
    this->currentSong = this->currentChapter->second.constBegin();
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


PlaylistStatus Playlist::prevChapter() 
{
    if (this->playList.isEmpty()) {
        this->lastStatus = PlaylistStatus::Uninitialized;
        return this->lastStatus;
    }

    if (this->playList.size() > 1) {
        if (this->currentChapter == this->playList.constBegin()) {
            this->currentChapter = this->playList.constEnd();
        }
        --this->currentChapter;
    }
    this->currentSong = this->currentChapter->second.constBegin();
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


PlaylistStatus Playlist::nextSong(bool turnAround)
 {
    if (this->currentChapter->second.isEmpty()) {
        this->lastStatus = PlaylistStatus::Uninitialized;
        return this->lastStatus;
    }

    if (this->currentChapter->second.size() > 1) {
        ++this->currentSong;
        if (this->currentSong == this->currentChapter->second.constEnd()) {
            if (!turnAround) {
                this->nextChapter();
            }
            this->currentSong = this->currentChapter->second.constBegin();
        }
    }
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


PlaylistStatus Playlist::prevSong(bool turnAround) 
{
    if (this->currentChapter->second.isEmpty()) {
        this->lastStatus = PlaylistStatus::Uninitialized;
        return this->lastStatus;
    }

    if (this->currentChapter->second.size() > 1) {
        if (this->currentSong == this->currentChapter->second.constBegin()) {
            if (!turnAround) {
                this->prevChapter();
            }
            this->currentSong = this->currentChapter->second.constEnd();
        }
        --this->currentSong;
    }
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


PlaylistStatus Playlist::reset() 
{
    if (this->playList.isEmpty()) {
        this->lastStatus = PlaylistStatus::Uninitialized;
        return this->lastStatus;
    }
    this->currentChapter = this->playList.constBegin();

    if (this->currentChapter->second.isEmpty()) {
        this->lastStatus = PlaylistStatus::Uninitialized;
        return this->lastStatus;
    }
    this->currentSong = currentChapter->second.constBegin();

    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


void Playlist::printPlaylist()
{
    QList<QPair<QString, QList<int> > >::const_iterator i;
    for (i = playList.constBegin(); i != playList.constEnd(); ++i) {
        QTextStream(stdout) << "currently at: " << i->first << endl;
        QList<int>::const_iterator e;
        for (e = i->second.constBegin(); e != i->second.constEnd(); ++e) {
            QTextStream(stdout) << "   " << *e << " (" 
                                << this->songMap.value(*e, "???") << ")" << endl;
        }
    }
}


QString Playlist::getCurrentChapter() 
{
    return currentChapter->first;
}


QString Playlist::getCurrentSong() 
{
    this->lastStatus = PlaylistStatus::OK;
    return *this->currentSong != 0 ? QString::number(abs(*this->currentSong)) : "---";
}


QString Playlist::getCurrentSongName() 
{
    this->lastStatus = PlaylistStatus::OK;
    if (*this->currentSong == 0)
        return "";
    QString s = this->songMap.value(abs(*this->currentSong), "");
    const int i = s.lastIndexOf(".");
    if (i == -1)
        return s;
    return s.left(i);
}


PlaylistStatus Playlist::createPlaylistFromFile(QTextStream &in)
{
    // empty file?
    if (in.atEnd()) {
        this->lastStatus = PlaylistStatus::EmptyFile;
        return this->lastStatus;
    }
    this->title = in.readLine();

    QList<QPair<QString, QList<int> > > newList;
    QCryptographicHash checksum(QCryptographicHash::Md5);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QByteArray a = line.toLocal8Bit();
        checksum.addData(a.data(), a.size());

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
            QTextStream(stdout) << "warning: line is not properly terminated: " 
                                << line << endl;

        QStringList split = line.split(playListSeparator, QString::SkipEmptyParts);

        // an existing separator does not guarantee two splits (QString::SkipEmptyParts)
        if (split.size() < 2) {
            this->lastParseError = QObject::tr("invalid syntax in line: \"") + 
                                   line + "\"";
            this->lastStatus = PlaylistStatus::ParseFailure;
            return this->lastStatus;
        }

        QString chapter = split.takeFirst();

        // create list of song ids
        // this might actually be empty, that's fine
        QStringList songIDList = split.join(playListSeparator)
                                      .split(playListSongSeparator, 
                                             QString::SkipEmptyParts);
        QList<int> songs;

        QStringList::const_iterator i;
        for (i = songIDList.constBegin(); i != songIDList.constEnd(); ++i) {
            bool ok;
            int n = i->toInt(&ok);
            if (!ok) {
                this->lastParseError = QObject::tr("song ID \"") + *i + 
                                       QObject::tr("\" is not a valid number, in line: \"") + 
                                       line + "\"";
                this->lastStatus = PlaylistStatus::ParseFailure;
                return this->lastStatus;
            }
            songs.append(n);
        }
        // wrap it all into a pair and append the data
        newList.append(QPair<QString, QList<int> >(chapter, songs));
    }

    this->playlistChecksum = checksum.result().toHex();
    this->playList = newList;
    this->currentChapter = this->playList.constBegin();
    this->currentSong = currentChapter->second.constBegin();
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


PlaylistStatus Playlist::createSongMapFromFile(QTextStream &in)
{
    // empty file?
    if (in.atEnd()) {
        this->lastStatus = PlaylistStatus::EmptyFile;
        return this->lastStatus;
    }

    QHash<int, QString> newMap;
    QCryptographicHash checksum(QCryptographicHash::Md5);

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        if (line.isEmpty())
            continue;

        QByteArray a = line.toLocal8Bit();
        checksum.addData(a.data(), a.size());

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
            this->lastParseError = QObject::tr("invalid syntax in line: \"") + 
                                   line + "\"";
            this->lastStatus = PlaylistStatus::ParseFailure;
            return this->lastStatus;
        }

        // we need this because we split with QString::KeepEmptyParts
        if (split.first().isEmpty()) {
            this->lastParseError = QObject::tr("missing song ID in line: \"") + 
                                   line + "\"";
            this->lastStatus = PlaylistStatus::ParseFailure;
            return this->lastStatus;
        }

        // is the first part really a number?
        bool ok;
        QString tmp = split.takeFirst();
        int key = tmp.toInt(&ok);
        if (!ok) {
            this->lastParseError = QObject::tr("song ID \"") + 
                                   tmp + 
                                   QObject::tr("\" is not a valid number, in line: \"") + 
                                   line + "\"";
            this->lastStatus = PlaylistStatus::ParseFailure;
            return this->lastStatus;
        }

        // use as value whatever comes after <ID><separator>
        newMap.insert(key, split.join(songMapSeparator));
    }

    this->songMapChecksum = checksum.result().toHex();
    this->songMap = newMap;
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


PlaylistStatus Playlist::setSongDirectory(const QString &s)
{
    if (!s.isNull() && !s.isEmpty()) {
        this->songDirectory = s;
        this->lastStatus = PlaylistStatus::OK;
        return this->lastStatus;
    }

    this->lastStatus = PlaylistStatus::EmptySongDirectory;
    return this->lastStatus;
}


PlaylistStatus Playlist::checkSongDirectory()
{
    int e = 0;
    QHash<int, QString>::const_iterator i = this->songMap.constBegin();
    while (i != songMap.constEnd()) {
        if (!QFileInfo(getSongPath(i.value())).isFile()) {
            QTextStream(stderr) << "file does not exist: " 
                                << getSongPath(i.value()) << endl;
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


QString Playlist::getSongPath(const QString &s)
{
    this->lastStatus = PlaylistStatus::OK;
    return this->songDirectory + QDir::separator() + s;
}


QString Playlist::getCurrentSongPath()
{
    this->lastStatus = PlaylistStatus::OK;
    if (*currentSong == 0)
        return "";
    return QFileInfo(this->songDirectory + 
                     QDir::separator() + 
                     songMap.value(abs(*currentSong))).absoluteFilePath();
}


bool Playlist::loopCurrentSong()
{
    return *this->currentSong > 0;
}


QString Playlist::getTitle()
{
    this->lastStatus = PlaylistStatus::OK;
    return this->title;
}


PlaylistStatus Playlist::status()
{
    this->lastStatus = PlaylistStatus::OK;
    return this->lastStatus;
}


QString Playlist::getLastParseError()
{
    this->lastStatus = PlaylistStatus::OK;
    return this->lastParseError;
}


QString Playlist::getPlaylistChecksum()
{
    return this->playlistChecksum;
}


QString Playlist::getSongMapChecksum()
{
    return this->songMapChecksum;
}


int Playlist::getCurrentChapterNumber()
{
    return this->currentChapter - this->playList.constBegin();
}


int Playlist::getCurrentSongNumber()
{
    return this->currentSong - this->currentChapter->second.constBegin();
}


PlaylistStatus Playlist::setCurrentChapterByNumber(const int i)
{
    QList<QPair<QString, QList<int> > >::const_iterator e = this->currentChapter;
    
    if (i > -1 && i < this->playList.size()) {
        this->currentChapter = this->playList.constBegin() + i;
        this->lastStatus = PlaylistStatus::OK;
    }
    else {
        this->lastStatus = PlaylistStatus::InvalidNumbersSet;
    }

    if (this->currentChapter == NULL) {
        this->currentChapter = e;
        this->lastStatus = PlaylistStatus::InvalidNumbersSet;
    }
    return this->lastStatus;
}


PlaylistStatus Playlist::setCurrentSongByNumber(const int i)
{
    QList<int>::const_iterator e = this->currentSong;

    if (i > -1 && i < this->currentChapter->second.size()) {
        this->currentSong = this->currentChapter->second.constBegin() + i;
        this->lastStatus = PlaylistStatus::OK;
    }
    else {
        this->lastStatus = PlaylistStatus::InvalidNumbersSet;
    }

    if (this->currentSong == NULL) {
        this->currentSong = e;
        this->lastStatus = PlaylistStatus::InvalidNumbersSet;
    }

    return this->lastStatus;
}


Playlist::~Playlist()
{
}
