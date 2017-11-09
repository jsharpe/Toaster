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
#include "SysExMsgDispatcher.h"
#include "VirtualKPA.h"

SysExMsgDispatcher::SysExMsgDispatcher() {
  Midi::get().addConsumer(this);
  VirtualKPA::get().addMidiConsumer(this);
}

SysExMsgDispatcher::~SysExMsgDispatcher() {
  Midi::get().removeConsumer(this);
  VirtualKPA::get().removeMidiConsumer(this);
}

SysExMsgDispatcher &SysExMsgDispatcher::get() {
  static SysExMsgDispatcher singleton;
  return singleton;
}

void SysExMsgDispatcher::consume(const ByteArray &msg) {
  if (msg.size() >= 8) {
    const ByteArray &header = Header();
    if (header[0] == msg[0] && header[1] == msg[1] &&
        header[2] == msg[2] && header[3] == msg[3]) {
      std::lock_guard<std::mutex> l(this->lock);
      for (auto *consumer : mConsumer) {
        auto consumerId = consumer->getId();
        if ((ExtParamChange()[0] == (msg)[6] &&
             consumerId ==
                 (msg)[6])) { // special handling for extended parameter function
          consumer->consumeSysExMsg(msg);
        }
        else if ((ExtParamChange()[0] == (msg)[7] &&
                  consumerId == (msg)[6])) { // special handling for extended
                                             // parameter function
          consumer->consumeSysExMsg(msg);
        }
        else if ((consumerId == (msg)[8] || consumerId == 0xFF)) {
          uint16_t rawVal = msg[10];
          if (msg.size() >= 12) {
            rawVal = Utils::extractRawVal(msg[10], msg[11]);
          }
          consumer->consumeSysExMsg(msg[9], rawVal);
        } else {
        }
      }
    }
  }
}

void SysExMsgDispatcher::addConsumer(ISysExConsumer *consumer) {
  if (consumer) {
    std::lock_guard<std::mutex> l(this->lock);
    mConsumer.push_back(consumer);
  }
}

void SysExMsgDispatcher::removeConsumer(ISysExConsumer *consumer) {
  if (consumer) {
    std::lock_guard<std::mutex> l(this->lock);
    auto entry = std::find(mConsumer.begin(), mConsumer.end(), consumer);
    mConsumer.erase(entry);
  }
}
