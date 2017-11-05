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
#ifndef MIDICLIENT_H
#define MIDICLIENT_H
#include "Commons.h"
#include "MidiConsumer.h"
#include <QString>
#include <QStringList>
#include <RtMidi.h>
#include <list>
#include <vector>

using namespace std;

class Midi {

private:
  Midi();
  ~Midi();

public:
  static Midi &get();

  bool openPorts(const QString &inPort, const QString &outPort);
  void closePorts();

  bool arePortsOpen() { return mMidiIn.isPortOpen() && mMidiOut.isPortOpen(); }

  void processMidiInput(std::vector<unsigned char> *msg);

  QStringList getInPorts();
  QStringList getOutPorts();

  void sendCmd(const ByteArray &cmd);

  void addConsumer(IMidiConsumer *consumer);
  void removeConsumer(IMidiConsumer *consumer);

private:
  string mName;
  RtMidiIn mMidiIn;
  RtMidiOut mMidiOut;

  std::vector<IMidiConsumer *> mConsumer;
};

#endif // MIDICLIENT_H
