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
#ifndef AMPMIDI_H
#define AMPMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"

class AmpMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer {
protected:
  // address pages
  BYTEARRAYDECL(AddressPage)
  // parameter
  BYTEARRAYDECL(OnOff)
  BYTEARRAYDECL(Gain)
  BYTEARRAYDECL(Definition)
  BYTEARRAYDECL(Clarity)
  BYTEARRAYDECL(PowerSagging)
  BYTEARRAYDECL(Pick)
  BYTEARRAYDECL(Compressor)
  BYTEARRAYDECL(TubeShape)
  BYTEARRAYDECL(TubeBias)
  BYTEARRAYDECL(DirectMix)

  AmpMidi();
  ~AmpMidi();

  // ISysExConsumer
  unsigned char getId() override final;
  void consumeSysExMsg(unsigned char param, uint16_t rawVal) override final;

  // parameter
  // OnOff
  void midiApplyOnOff(unsigned short rawVal);
  // Gain
  void midiApplyGain(unsigned short rawVal);
  // Definition
  void midiApplyDefinition(unsigned short rawVal);
  // Clarity
  void midiApplyClarity(unsigned short rawVal);
  // PowerSagging
  void midiApplyPowerSagging(unsigned short rawVal);
  // Pick
  void midiApplyPick(unsigned short rawVal);
  // Compressor
  void midiApplyCompressor(unsigned short rawVal);
  // TubeShape
  void midiApplyTubeShape(unsigned short rawVal);
  // TubeBias
  void midiApplyTubeBias(unsigned short rawVal);
  // DirectMix
  void midiApplyDirectMix(unsigned short rawVal);

  // receive callbacks for derived class
  virtual void midiOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiGainReceived(unsigned short rawVal) = 0;
  virtual void midiDefinitionReceived(unsigned short rawVal) = 0;
  virtual void midiClarityReceived(unsigned short rawVal) = 0;
  virtual void midiPowerSaggingReceived(unsigned short rawVal) = 0;
  virtual void midiPickReceived(unsigned short rawVal) = 0;
  virtual void midiCompressorReceived(unsigned short rawVal) = 0;
  virtual void midiTubeShapeReceived(unsigned short rawVal) = 0;
  virtual void midiTubeBiasReceived(unsigned short rawVal) = 0;
  virtual void midiDirectMixReceived(unsigned short rawVal) = 0;

  // utility methods
  ByteArray getAddressPage();
};

#endif // AMPMIDI_H
