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
 * \file      mediawrapper.h
 * \author    Emeric Grange <emeric.grange@gmail.com>
 * \date      2017
 */

#ifndef MEDIAWRAPPER_H
#define MEDIAWRAPPER_H
/* ************************************************************************** */

// minivideo library
#include <minivideo.h>

#include <vector>

#include <QObject>
#include <QString>
#include <QDebug>
#include <QTimer>
#include <QFile>

/* ************************************************************************** */

class MediaWrapper : public QObject
{
    Q_OBJECT

public:
    MediaWrapper() {}
    MediaWrapper(QString &file) { mediaPath = file; }
    ~MediaWrapper() {}

    bool ready = false;
    MediaFile_t *media = nullptr;

    QString mediaPath;
    QString errorString;

    // Chronos
    std::chrono::time_point<std::chrono::steady_clock> start_parsing, end_parsing;
    std::chrono::time_point<std::chrono::steady_clock> start_ui, end_ui;

    // UI State
    QString currentTab;
    int currentVideoTrack = 0;
    int currentAudioTrack = 0;
    int currentSubtitlesTrack = 0;
    int containerMode = 0;
    int containerExplorerAtom = 0; // TODO
    int containerTrack = 0;
    int containerTrackSample = 0; // TODO
    int exportMode = 0;
    int exportFormat = 0;

    // Bitrate graph
    double xRangeMax = -1.0;
    double yRangeMax = -1.0;

public slots:
    void parsing()
    {
        if (mediaPath.isEmpty() == false)
        {
            start_parsing = std::chrono::steady_clock::now();

            char input_filepath[4096];
            strncpy(input_filepath, mediaPath.toLocal8Bit(), 4095);

            // Create and open the media file
            int retcode = minivideo_open(input_filepath, &media);

            if (retcode == SUCCESS)
            {
                retcode = minivideo_parse(media, true);
                ready = true;

                if (retcode != SUCCESS)
                {
                    qDebug() << "minivideo_parse() failed with retcode: " << retcode;
                }
            }
            else
            {
                qDebug() << "minivideo_open() failed with retcode: " << retcode;
            }
            end_parsing = std::chrono::steady_clock::now();

            qDebug() << "parsingFinished(" << mediaPath << ")";
            emit parsingFinished(mediaPath);
        }
    }

signals:
    void parsingFinished(QString mediaPath);
};

/* ************************************************************************** */
#endif // MEDIAWRAPPER_H
