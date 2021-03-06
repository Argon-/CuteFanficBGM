# This file is part of CuteFanficBGM.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program.  If not, see <http://www.gnu.org/licenses/>.
#
 
QT      += widgets core gui multimedia
CONFIG  += c++11
TEMPLATE = app

macx 
{
    QMAKE_INFO_PLIST = template_Info.plist
    QMAKE_POST_LINK += ./update_info_plist.sh
}


TARGET = CuteFanficBGM

DESTDIR     = 
OBJECTS_DIR = objects
MOC_DIR     = generated

SOURCES += src/*.cpp
HEADERS += src/*.h
