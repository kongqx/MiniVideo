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
 * \file      videobackends_ui.h
 * \author    Emeric Grange <emeric.grange@gmail.com>
 * \date      2017
 */

#ifndef VIDEOBACKENDS_UI_H
#define VIDEOBACKENDS_UI_H
/* ************************************************************************** */

#include "videobackends.h"

#include <QWidget>

namespace Ui {
class VideoBackendsUI;
}

class VideoBackendsUI : public QWidget
{
    Q_OBJECT

public:
    explicit VideoBackendsUI(QWidget *parent = 0);
    ~VideoBackendsUI();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::VideoBackendsUI *ui;

    VideoBackendInfos infos;
};

/* ************************************************************************** */
#endif // VIDEOBACKENDS_UI_H