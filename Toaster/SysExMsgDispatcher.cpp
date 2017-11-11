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

enum class MsgType {
    SingleParameterChange = 0x01,
    MultiParameterChange = 0x02,
    StringParameter = 0x03,
    BLOB = 0x04,
    //0x05 reserved
    ExtendedParameterChange = 0x06,
    ExtendedStringParameterChange = 0x07,
    ResponseParameterValueRenderedString = 0x3c,
    // 0x40 Beacon
    RequestSingleParameter = 0x41,
    RequestMultiParameter = 0x42,
    RequestStringParameter = 0x43,
    RequestExtendedStringParameter = 0x47,
    RequestParameterValueRenderedString = 0x7C,
    //0x7E reserved
    //0x7F reserved
};

void SysExMsgDispatcher::consume(const ByteArray &msg) {
  if (msg.size() >= 9) {
    const ByteArray &header = Header();
    if (header[0] == msg[0] && header[1] == msg[1] &&
        header[2] == msg[2] && header[3] == msg[3] &&
        // 0x02 == msg[4] && // Product type = Kemper - this is sometimes 0x00?
        // msg[5] is midi channel
        0x00 == msg [7] && // Instance is always 0
        msg[msg.size()-1] == 0xF7) {
        uint16_t rawVal {0};
        MsgType fct = MsgType(msg[6]);
        unsigned char addressPage = msg[8];
        unsigned char paramId = 0;
        if (fct == MsgType::StringParameter ||
            fct == MsgType::ExtendedStringParameterChange) {
            std::lock_guard<std::mutex> l(this->lock);
            for (auto *consumer : mConsumer) {
                auto consumerId = consumer->getId();
                if (consumerId == addressPage) {
                    consumer->consumeSysExMsg(msg);
                }
            }
        } else {
            paramId = msg[9];
            if (msg.size() == 13) {
                rawVal = Utils::extractRawVal(msg[10], msg[11]);
            } else if (fct == MsgType::MultiParameterChange) {
                for(int i=10; i < msg.size()-2; i+=2) {
                    rawVal = Utils::extractRawVal(msg[i], msg[i+1]);
                    std::lock_guard<std::mutex> l(this->lock);
                    for (auto *consumer : mConsumer) {
                        auto consumerId = consumer->getId();
                        if (consumerId == addressPage) {
                            consumer->consumeSysExMsg(paramId++, rawVal);
                        }
                    }
                }
                return;
            } else {
                return;
            }
        }
        std::lock_guard<std::mutex> l(this->lock);
        for (auto *consumer : mConsumer) {
            auto consumerId = consumer->getId();
            if (consumerId == addressPage) {
                consumer->consumeSysExMsg(paramId, rawVal);
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
