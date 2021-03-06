/*  This file is part of Toaster, the editor and remote control for Kemper
 * profiling amplifier.
 *
 *   Copyright (C) 2016  Thomas Langer
 *
 *   Toaster is free software: you can redistribute it and/or modify it under
 * the terms of the GNU General Public License as published by the Free Software
 * Foundation, either version 3 of the License, or (at your option) any later
 * version.
 *
 *   Toaster is distributed in the hope that it will be useful, but WITHOUT ANY
 * WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR
 * A PARTICULAR PURPOSE. See the GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License along
 * with Toaster. If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef CONNECTIONSTATUSFRAME_H
#define CONNECTIONSTATUSFRAME_H

#include "ui_ConnectionStatusFrame.h"
#include <QWidget>

class ConnectionStatusFrame : public QWidget {
  Q_OBJECT

public:
  explicit ConnectionStatusFrame(QWidget *parent = 0);
  ~ConnectionStatusFrame();

public slots:
  void setMidiStatus(bool isConnected);
  void setKPAStatus(bool isConnected, bool dataReceived);

private:
  Ui::ConnectionStatusFrame ui;
};

#endif // CONNECTIONSTATUSFRAME_H
