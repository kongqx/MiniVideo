/*!
 * COPYRIGHT (C) 2017 Emeric Grange - All Rights Reserved
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
 * \file      tabcontainer.h
 * \author    Emeric Grange <emeric.grange@gmail.com>
 * \date      2017
 */

#ifndef TABCONTAINER_H
#define TABCONTAINER_H

// MiniVideo
#include "minivideo_mediafile.h"

#include "mediawrapper.h"

// QHexEdit widget
#include "thirdparty/qhexedit2/qhexedit.h"

// pugixml
#include "thirdparty/pugixml/pugixml.hpp"

#include <QWidget>
#include <QTreeWidgetItem>
#include <QResizeEvent>
#include <QFile>
#include <QIcon>

namespace Ui {
class tabContainer;
}

class tabContainer : public QWidget
{
    Q_OBJECT

public:
    explicit tabContainer(QWidget *parent = 0);
    ~tabContainer();

    void loadMedia(const MediaFile_t *media);
    void loadMedia(const MediaWrapper *wrapper);
    void loadTracks();
    void closeMedia();

public slots:
    void clearContent();
    void tabSwitch(int intex);
    void loadSamples(int track_id);
    void sampleSelection();
    void sampleSelection(int sample_id);
    void containerSelectionEmpty();
    void containerSelectionChanged();
    void containerSelection(QTreeWidgetItem *item, int column);

    bool loadXmlFile();
        bool xmlFileParser(pugi::xml_node &root);
        void xmlHeaderParser(pugi::xml_node &root);
        void xmlStructureParser(pugi::xml_node &root);
        void xmlAtomParser(pugi::xml_node &root, QTreeWidgetItem *item);

    bool findAtom(const pugi::xml_node &elem, const QString &attr, int value, pugi::xml_node &foundElement);

private slots:
    void on_tabWidget_currentChanged(int index);
    void on_tabWidget_tracks_currentChanged(int index);

private:
    Ui::tabContainer *ui;

    MediaFile_t *media = nullptr;
    MediaWrapper *wrapper = nullptr;

    MediaStream_t *track = nullptr;
    MediaStream_t *tracks[16] = {0};

    QFile mediaFile;
    QByteArray mediaDatas;

    QFile xmlMapFile;
    pugi::xml_document xmlMapDatas;

    QIcon icon_atom;
    QIcon icon_ext;
    QIcon icon_track;

    void resizeEvent(QResizeEvent *event);
};

#endif // TABCONTAINER_H
