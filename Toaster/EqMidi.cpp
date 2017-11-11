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
#include "EqMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(EqMidi, AddressPage, 0x0B)

// parameter
BYTEARRAYDEF(EqMidi, OnOff, 0x02)
BYTEARRAYDEF(EqMidi, Bass, 0x04)
BYTEARRAYDEF(EqMidi, Middle, 0x05)
BYTEARRAYDEF(EqMidi, Treble, 0x06)
BYTEARRAYDEF(EqMidi, Presence, 0x07)

EqMidi::EqMidi() { SysExMsgDispatcher::get().addConsumer(this); }

EqMidi::~EqMidi() {
    SysExMsgDispatcher::get().removeConsumer(this);
}

unsigned char EqMidi::getId() {
  return 0x0B;
}

void EqMidi::consumeSysExMsg(unsigned char param, uint16_t rawVal) {
    if (param == sOnOff[0])
      midiOnOffReceived(rawVal);
    else if (param == sBass[0])
      midiBassReceived(rawVal);
    else if (param == sMiddle[0])
      midiMiddleReceived(rawVal);
    else if (param == sTreble[0])
      midiTrebleReceived(rawVal);
    else if (param == sPresence[0])
      midiPresenceReceived(rawVal);
}

void EqMidi::midiApplyOnOff(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sOnOff, rawVal));
}

void EqMidi::midiApplyBass(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sBass, rawVal));
}

void EqMidi::midiApplyMiddle(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sMiddle, rawVal));
}

void EqMidi::midiApplyTreble(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sTreble, rawVal));
}

void EqMidi::midiApplyPresence(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sPresence, rawVal));
}

ByteArray EqMidi::getAddressPage() { return sAddressPage; }
