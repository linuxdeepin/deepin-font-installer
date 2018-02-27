/*
 * Copyright (C) 2017 ~ 2018 Deepin Technology Co., Ltd.
 *
 * Author:     rekols <rekols@foxmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "listview.h"
#include "listitem.h"
#include <QDebug>

ListView::ListView(QWidget *parent)
    : DSimpleListView(parent)
{
    // enable frame and radius.
    setFrame(true);
    setClipRadius(8);

    // set row height.
    setRowHeight(56);

    // set fixed height.
    setFixedHeight(280);

    // Enable hover effect.
    setHoverEffect(true);

    // init scrollbar attributes.
    scrollbarColor = "#101010";
    scrollbarNormalOpacity = 0.5;
    scrollbarHoverOpacity = 0.7;
    scrollbarPressOpacity = 0.8;
    scrollbarFrameNormalOpacity = 0;
    scrollbarFrameHoverOpacity = 0;
    scrollbarFramePressOpacity = 0;

    connect(this, &ListView::mouseHoverChanged, this, &ListView::handleMouseHoverChanged);
    connect(this, &ListView::mousePressChanged, this, &ListView::handleMousePressChanged);
    connect(this, &ListView::mouseReleaseChanged, this, &ListView::handleMouseReleaseChanged);
}

ListView::~ListView()
{
}

void ListView::handleMouseHoverChanged(DSimpleListItem* oldItem, DSimpleListItem* newItem, int columnIndex, QPoint pos)
{
    if (oldItem == NULL || !oldItem->sameAs(newItem)) {
        if (oldItem != NULL) {
            (static_cast<ListItem*>(oldItem))->setCloseButtonStatus(Hide);
        }

        if (newItem != NULL) {
            (static_cast<ListItem*>(newItem))->setCloseButtonStatus(Normal);
        }

        repaint();
    } else {
        if ((static_cast<ListItem*>(newItem))->isHoverCloseButton(pos)) {
            (static_cast<ListItem*>(newItem))->setCloseButtonStatus(Hover);

            qDebug() << "Hover";

            repaint();
        } else {
            (static_cast<ListItem*>(newItem))->setCloseButtonStatus(Normal);

            qDebug() << "Normal";

            repaint();
        }
    }
}

void ListView::handleMousePressChanged(DSimpleListItem* item, int columnIndex, QPoint pos)
{
    if (item != NULL) {
        if ((static_cast<ListItem*>(item))->isHoverCloseButton(pos)) {
            (static_cast<ListItem*>(item))->setCloseButtonStatus(Press);

            qDebug() << "Press";

            repaint();
        }
    }
}

void ListView::handleMouseReleaseChanged(DSimpleListItem* item, int columnIndex, QPoint pos)
{
    if ((static_cast<ListItem*>(item))->isHoverCloseButton(pos)) {
        (static_cast<ListItem*>(item))->setCloseButtonStatus(Hover);

        qDebug() << "Hover";

        repaint();
    } else {
        (static_cast<ListItem*>(item))->setCloseButtonStatus(Normal);

        qDebug() << "Normal";

        repaint();
    }
}