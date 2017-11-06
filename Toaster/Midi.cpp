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
#include "Midi.h"
#include "VirtualKPA.h"

void cbProcessMidiInput(double, std::vector<unsigned char> *message, void *) {
  Midi::get().processMidiInput(message);
}

void cbMidiOutputError(RtMidiError::Type type, const std::string &errorText) {
  // Midi::get().midiOutputError(type, errorText);
}

Midi::Midi()
    : mName("Toaster"), mMidiIn(RtMidi::UNSPECIFIED, mName),
      mMidiOut(RtMidi::UNSPECIFIED, mName) {}

Midi::~Midi() { mConsumer.clear(); }

Midi &Midi::get() {
  static Midi singleton;
  return singleton;
}

bool Midi::openPorts(const QString &inPort, const QString &outPort) {
  int inPortNo = -1;
  int outPortNo = -1;

  auto inPorts = getInPorts();
  for (int i = 0; i < inPorts.size(); ++i) {
    if (inPorts[i] == inPort) {
      inPortNo = i;
      break;
    }
  }

  if (inPortNo >= 0)
    mMidiIn.openPort(inPortNo, "in");
  else
    mMidiIn.openVirtualPort("in");

  if (mMidiIn.isPortOpen()) {
    mMidiIn.setCallback(&cbProcessMidiInput);
    mMidiIn.ignoreTypes(false, false, false);

    auto outPorts = getOutPorts();
    for (int i = 0; i < outPorts.size(); ++i) {
      if (outPorts[i] == outPort) {
        outPortNo = i;
        break;
      }
    }

    if (outPortNo >= 0)
      mMidiOut.openPort(outPortNo, "out");
    else
      mMidiOut.openVirtualPort("out");

    if (mMidiOut.isPortOpen()) {
      mMidiOut.setErrorCallback(&cbMidiOutputError);
      return true;
    }

    mMidiIn.closePort();
  }
  return false;
}

void Midi::closePorts() {
  mMidiIn.closePort();
  mMidiOut.closePort();
}

void Midi::processMidiInput(std::vector<unsigned char> *msg) {
  if (msg && msg->size() > 0) {
    std::lock_guard<std::mutex> g(lock);
    for (IMidiConsumer *consumer : mConsumer) {
      if ((*msg)[0] == consumer->getStatusByte())
        consumer->consume(*msg);
    }
  }
}

QStringList Midi::getInPorts() {
  QStringList inPorts;

  for (unsigned int i = 0; i < mMidiIn.getPortCount(); ++i)
    inPorts.push_back(QString(mMidiIn.getPortName(i).c_str()));

  return inPorts;
}

QStringList Midi::getOutPorts() {
  QStringList outPorts;

  for (unsigned int i = 0; i < mMidiOut.getPortCount(); ++i)
    outPorts.push_back(QString(mMidiOut.getPortName(i).c_str()));

  return outPorts;
}

void Midi::sendCmd(const ByteArray &cmd) {
  if (cmd.size() > 0) {
    if (mMidiOut.isPortOpen()) {
      if (cmd[0] != 0xB0) {
        mMidiOut.sendMessage(&cmd);
      } else if (cmd.size() % 3 == 0) {
        auto it = cmd.begin();
        for (int i = 0; i < cmd.size() / 3; ++i) {
          std::vector<unsigned char> tmp(it, it + 3);
          mMidiOut.sendMessage(&tmp);
          it += 3;
        }
      }
    }

    VirtualKPA::get().midiIn(cmd);
  }
}

void Midi::addConsumer(IMidiConsumer *consumer) {
  if (consumer) {
    std::lock_guard<std::mutex> g(lock);
    mConsumer.push_back(consumer);
  }
}

void Midi::removeConsumer(IMidiConsumer *consumer) {
  std::lock_guard<std::mutex> g(lock);
  mConsumer.erase(std::find(mConsumer.begin(), mConsumer.end(), consumer));
}
