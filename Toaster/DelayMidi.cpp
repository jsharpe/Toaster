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
#include "DelayMidi.h"
#include "Midi.h"

// address page
BYTEARRAYDEF(DelayMidi, AddressPage, 0x4A)
// parameter
BYTEARRAYDEF(DelayMidi, Type, 0x00)
BYTEARRAYDEF(DelayMidi, OnOffCutsTail, 0x02)
BYTEARRAYDEF(DelayMidi, Mix, 0x03)
BYTEARRAYDEF(DelayMidi, Volume, 0x04)
BYTEARRAYDEF(DelayMidi, Time, 0x05)
BYTEARRAYDEF(DelayMidi, Ratio, 0x06)
BYTEARRAYDEF(DelayMidi, ClockLeft, 0x07)
BYTEARRAYDEF(DelayMidi, ClockRight, 0x08)
BYTEARRAYDEF(DelayMidi, Feedback, 0x09)
BYTEARRAYDEF(DelayMidi, Bandwidth, 0x0A)
BYTEARRAYDEF(DelayMidi, CenterFrequency, 0x0B)
BYTEARRAYDEF(DelayMidi, Modulation, 0x0C)
BYTEARRAYDEF(DelayMidi, OnOffKeepsTail, 0x0D)
BYTEARRAYDEF(DelayMidi, Ducking, 0x0E)

DelayMidi::DelayMidi() { SysExMsgDispatcher::get().addConsumer(this); }

DelayMidi::~DelayMidi() {
    SysExMsgDispatcher::get().removeConsumer(this);
}

unsigned char DelayMidi::getId() {
  unsigned char ret = 0x00;
  ByteArray addressPage = getAddressPage();
  if (addressPage.size() > 0)
    ret = addressPage[0];

  return ret;
}

void DelayMidi::consumeSysExMsg(const ByteArray &msg) {
  if (msg.size() >= 12) {
    auto rawVal = Utils::extractRawVal(msg[10], msg[11]);
    const char param = msg[9];
    if (param == sType[0])
      midiTypeReceived(rawVal);
    if (param == sOnOffCutsTail[0])
      midiOnOffCutsTailReceived(rawVal);
    if (param == sMix[0])
      midiMixReceived(rawVal);
    if (param == sVolume[0])
      midiVolumeReceived(rawVal);
    if (param == sTime[0])
      midiTimeReceived(rawVal);
    if (param == sRatio[0])
      midiRatioReceived(rawVal);
    if (param == sClockLeft[0])
      midiClockLeftReceived(rawVal);
    if (param == sClockRight[0])
      midiClockRightReceived(rawVal);
    if (param == sFeedback[0])
      midiFeedbackReceived(rawVal);
    if (param == sBandwidth[0])
      midiBandwidthReceived(rawVal);
    if (param == sCenterFrequency[0])
      midiCenterFrequencyReceived(rawVal);
    if (param == sModulation[0])
      midiModulationReceived(rawVal);
    if (param == sOnOffKeepsTail[0])
      midiOnOffKeepsTailReceived(rawVal);
    if (param == sDucking[0])
      midiDuckingReceived(rawVal);
  }
}

void DelayMidi::midiApplyType(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sType, rawVal));
}

void DelayMidi::midiApplyOnOffCutsTail(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sOnOffCutsTail, rawVal));
}

void DelayMidi::midiApplyMix(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMix, rawVal));
}

void DelayMidi::midiApplyVolume(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sVolume, rawVal));
}

void DelayMidi::midiApplyTime(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sTime, rawVal));
}

void DelayMidi::midiApplyRatio(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sRatio, rawVal));
}

void DelayMidi::midiApplyClockLeft(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sClockLeft, rawVal));
}

void DelayMidi::midiApplyClockRight(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sClockRight, rawVal));
}

void DelayMidi::midiApplyFeedback(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sFeedback, rawVal));
}

void DelayMidi::midiApplyBandwidth(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sBandwidth, rawVal));
}

void DelayMidi::midiApplyCenterFrequency(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sCenterFrequency, rawVal));
}

void DelayMidi::midiApplyModulation(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sModulation, rawVal));
}

void DelayMidi::midiApplyOnOffKeepsTail(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sOnOffKeepsTail, rawVal));
}

void DelayMidi::midiApplyDucking(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sDucking, rawVal));
}

ByteArray DelayMidi::getAddressPage() { return sAddressPage; }
