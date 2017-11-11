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
#include "StompMidi.h"
#include "Midi.h"
#include "Utils.h"
#include <vector>

// address pages
BYTEARRAYDEF(StompMidi, AddressPageA, 0x32)
BYTEARRAYDEF(StompMidi, AddressPageB, 0x33)
BYTEARRAYDEF(StompMidi, AddressPageC, 0x34)
BYTEARRAYDEF(StompMidi, AddressPageD, 0x35)
BYTEARRAYDEF(StompMidi, AddressPageX, 0x38)
BYTEARRAYDEF(StompMidi, AddressPageMod, 0x3A)
BYTEARRAYDEF(StompMidi, AddressPageDelay, 0x3C)

// parameter
BYTEARRAYDEF(StompMidi, Type, 0x00)
BYTEARRAYDEF(StompMidi, OnOff, 0x03)
BYTEARRAYDEF(StompMidi, Mix, 0x04)
BYTEARRAYDEF(StompMidi, Volume, 0x06)
BYTEARRAYDEF(StompMidi, Stereo, 0x07)
BYTEARRAYDEF(StompMidi, WahManual, 0x08)
BYTEARRAYDEF(StompMidi, WahPeak, 0x09)
BYTEARRAYDEF(StompMidi, WahRange, 0x0A)
BYTEARRAYDEF(StompMidi, WahPedalMode, 0x0C)
BYTEARRAYDEF(StompMidi, WahTouchAttack, 0x0D)
BYTEARRAYDEF(StompMidi, WahTouchRelease, 0x0E)
BYTEARRAYDEF(StompMidi, WahTouchBoost, 0x0F)
BYTEARRAYDEF(StompMidi, DistortionShaperDrive,
             0x10) // also for legacy delay bandwidth
BYTEARRAYDEF(StompMidi, DistortionBoosterTone,
             0x11) // also for legacy delay frequency
BYTEARRAYDEF(StompMidi, CompressorGateIntensity, 0x12)
BYTEARRAYDEF(StompMidi, CompressorAttack, 0x13)
BYTEARRAYDEF(StompMidi, ModulationRate, 0x14) // also for stereo widener tune
BYTEARRAYDEF(StompMidi, ModulationDepth,
             0x15) // also for stereo widener intensity and micro pitch detune
BYTEARRAYDEF(StompMidi, ModulationFeedback, 0x16)
BYTEARRAYDEF(StompMidi, ModulationCrossover,
             0x17) // also for analog octaver low cut
BYTEARRAYDEF(StompMidi, ModulationHyperChorusAmount, 0x18)
BYTEARRAYDEF(StompMidi, ModulationManual, 0x19)
BYTEARRAYDEF(StompMidi, ModulationPhaserPeakSpread, 0x1A)
BYTEARRAYDEF(StompMidi, ModulationPhaserStages, 0x1B)
BYTEARRAYDEF(StompMidi, RotarySpeed, 0x1E)
BYTEARRAYDEF(StompMidi, RotaryDistance, 0x1F)
BYTEARRAYDEF(StompMidi, RotaryBalance, 0x20)
BYTEARRAYDEF(StompMidi, CompressorSquash, 0x21)
BYTEARRAYDEF(StompMidi, GraphicEQBand1, 0x22)
BYTEARRAYDEF(StompMidi, GraphicEQBand2, 0x23)
BYTEARRAYDEF(StompMidi, GraphicEQBand3, 0x24)
BYTEARRAYDEF(StompMidi, GraphicEQBand4, 0x25)
BYTEARRAYDEF(StompMidi, GraphicEQBand5, 0x26)
BYTEARRAYDEF(StompMidi, GraphicEQBand6, 0x27)
BYTEARRAYDEF(StompMidi, GraphicEQBand7, 0x28)
BYTEARRAYDEF(StompMidi, GraphicEQBand8, 0x29)
BYTEARRAYDEF(StompMidi, ParametricEQLowGain, 0x2A) // also for metal ds low
BYTEARRAYDEF(StompMidi, ParametricEQLowFrequency, 0x2B)
BYTEARRAYDEF(StompMidi, ParametricEQHighGain, 0x2C) // also for metal ds high
BYTEARRAYDEF(StompMidi, ParametricEQHighFrequency, 0x2D)
BYTEARRAYDEF(StompMidi, ParametricEQPeakGain, 0x2E) // also for metal ds middle
BYTEARRAYDEF(StompMidi, ParametricEQPeakFrequency,
             0x2F) // also for metal ds mid freq
BYTEARRAYDEF(StompMidi, ParametricEQPeakQFactor, 0x30)
BYTEARRAYDEF(StompMidi, ParametricEQPeakGain2, 0x31)
BYTEARRAYDEF(StompMidi, ParametricEQPeakFrequency2, 0x32)
BYTEARRAYDEF(StompMidi, ParametricEQPeakQFactor2, 0x33)
BYTEARRAYDEF(StompMidi, WahPeakRange, 0x34)
BYTEARRAYDEF(StompMidi, Ducking, 0x35)
BYTEARRAYDEF(StompMidi, Intensity, 0x36) // also for analog octaver mix
BYTEARRAYDEF(StompMidi, VoiceMix, 0x37)
BYTEARRAYDEF(StompMidi, Voice1Pitch, 0x38)
BYTEARRAYDEF(StompMidi, Voice2Pitch, 0x39)
BYTEARRAYDEF(StompMidi, Detune, 0x3A)
BYTEARRAYDEF(StompMidi, SmoothChords, 0x3C)
BYTEARRAYDEF(StompMidi, PureTuning, 0x3D)
BYTEARRAYDEF(StompMidi, Voice1Interval, 0x3E)
BYTEARRAYDEF(StompMidi, Voice2Interval, 0x3F)
BYTEARRAYDEF(StompMidi, Key, 0x40)
BYTEARRAYDEF(StompMidi, FormantShiftOnOff, 0x41)
BYTEARRAYDEF(StompMidi, FormantShift, 0x42)
BYTEARRAYDEF(StompMidi, LowCut, 0x43)
BYTEARRAYDEF(StompMidi, HighCut, 0x44)
BYTEARRAYDEF(StompMidi, DelayMix, 0x45)
BYTEARRAYDEF(StompMidi, Delay1Time, 0x47)
BYTEARRAYDEF(StompMidi, Delay2Time, 0x48)
BYTEARRAYDEF(StompMidi, Delay2Ratio, 0x49)
BYTEARRAYDEF(StompMidi, Delay3Ratio, 0x4A)
BYTEARRAYDEF(StompMidi, Delay4Ratio, 0x4B)
BYTEARRAYDEF(StompMidi, DelayNoteValue1, 0x4C)
BYTEARRAYDEF(StompMidi, DelayNoteValue2, 0x4D)
BYTEARRAYDEF(StompMidi, DelayNoteValue3, 0x4E)
BYTEARRAYDEF(StompMidi, DelayNoteValue4, 0x4F)
BYTEARRAYDEF(StompMidi, DelayToTempo, 0x50)
BYTEARRAYDEF(StompMidi, Delay1Volume, 0x51)
BYTEARRAYDEF(StompMidi, Delay2Volume, 0x52)
BYTEARRAYDEF(StompMidi, Delay3Volume, 0x53)
BYTEARRAYDEF(StompMidi, Delay4Volume, 0x54)
BYTEARRAYDEF(StompMidi, Delay1Panorama, 0x55)
BYTEARRAYDEF(StompMidi, Delay2Panorama, 0x56)
BYTEARRAYDEF(StompMidi, Delay3Panorama, 0x57)
BYTEARRAYDEF(StompMidi, Delay4Panorama, 0x58)
BYTEARRAYDEF(StompMidi, Voice3Pitch, 0x59)
BYTEARRAYDEF(StompMidi, Voice4Pitch, 0x5A)
BYTEARRAYDEF(StompMidi, Voice3Interval, 0x5B)
BYTEARRAYDEF(StompMidi, Voice4Interval, 0x5C)
BYTEARRAYDEF(StompMidi, DelayFeedback, 0x5D)
BYTEARRAYDEF(StompMidi, DelayInfinityFeedback, 0x5E)
BYTEARRAYDEF(StompMidi, DelayInfinity, 0x5F)
BYTEARRAYDEF(StompMidi, DelayFeedback2, 0x60)
BYTEARRAYDEF(StompMidi, DelayFeedbackSyncSwitch, 0x61)
BYTEARRAYDEF(StompMidi, DelayLowCut, 0x62)
BYTEARRAYDEF(StompMidi, DelayHighCut, 0x63)
BYTEARRAYDEF(StompMidi, DelayFilterIntensity, 0x64)
BYTEARRAYDEF(StompMidi, DelayModulation, 0x65)
BYTEARRAYDEF(StompMidi, DelayChorus, 0x66)
BYTEARRAYDEF(StompMidi, DelayFlutterIntensity, 0x67)
BYTEARRAYDEF(StompMidi, DelayFlutterShape, 0x68)
BYTEARRAYDEF(StompMidi, DelayGrit, 0x69)
BYTEARRAYDEF(StompMidi, DelayReverseMix, 0x6A)
BYTEARRAYDEF(StompMidi, DelaySwell, 0x6B)
BYTEARRAYDEF(StompMidi, DelaySmear, 0x6C)
BYTEARRAYDEF(StompMidi, DelayDuckingPrePost, 0x6D)

StompMidi::FXType2MidiRawValMap StompMidi::sFXType2MidiRawValMap;
StompMidi::MidiRawValMap2FXType StompMidi::sMidiRawValMap2FXType;

StompMidi::StompMidi(StompInstance instance) : mInstance(instance) {
  SysExMsgDispatcher::get().addConsumer(this);
}

StompMidi::~StompMidi() { SysExMsgDispatcher::get().removeConsumer(this); }

void StompMidi::consumeSysExMsg(const ByteArray &msg) {}

void StompMidi::consumeSysExMsg(unsigned char param, uint16_t rawVal) {
    if (param == sOnOff[0])
      midiOnOffReceived(rawVal);
    else if (param == sType[0])
      midiTypeReceived(rawVal);
    else if (param == sMix[0])
      midiMixReceived(rawVal);
    else if (param == sVolume[0])
      midiVolumeReceived(rawVal);
    else if (param == sStereo[0])
      midiStereoReceived(rawVal);
    else if (param == sWahManual[0])
      midiWahManualReceived(rawVal);
    else if (param == sWahPeak[0])
      midiWahPeakReceived(rawVal);
    else if (param == sWahRange[0])
      midiWahRangeReceived(rawVal);
    else if (param == sWahPedalMode[0])
      midiWahPedalModeReceived(rawVal);
    else if (param == sWahTouchAttack[0])
      midiWahTouchAttackReceived(rawVal);
    else if (param == sWahTouchRelease[0])
      midiWahTouchReleaseReceived(rawVal);
    else if (param == sWahTouchBoost[0])
      midiWahTouchBoostReceived(rawVal);
    else if (param == sDistortionShaperDrive[0])
      midiDistortionShaperDriveReceived(rawVal);
    else if (param == sDistortionBoosterTone[0])
      midiDistortionBoosterToneReceived(rawVal);
    else if (param == sCompressorGateIntensity[0])
      midiCompressorGateIntensityReceived(rawVal);
    else if (param == sCompressorAttack[0])
      midiCompressorAttackReceived(rawVal);
    else if (param == sModulationRate[0])
      midiModulationRateReceived(rawVal);
    else if (param == sModulationDepth[0])
      midiModulationDepthReceived(rawVal);
    else if (param == sModulationFeedback[0])
      midiModulationFeedbackReceived(rawVal);
    else if (param == sModulationCrossover[0])
      midiModulationCrossoverReceived(rawVal);
    else if (param == sModulationHyperChorusAmount[0])
      midiModulationHyperChorusAmountReceived(rawVal);
    else if (param == sModulationManual[0])
      midiModulationManualReceived(rawVal);
    else if (param == sModulationPhaserPeakSpread[0])
      midiModulationPhaserPeakSpreadReceived(rawVal);
    else if (param == sModulationPhaserStages[0])
      midiModulationPhaserStagesReceived(rawVal);
    else if (param == sRotarySpeed[0])
      midiRotarySpeedReceived(rawVal);
    else if (param == sRotaryDistance[0])
      midiRotaryDistanceReceived(rawVal);
    else if (param == sRotaryBalance[0])
      midiRotaryBalanceReceived(rawVal);
    else if (param == sCompressorSquash[0])
      midiCompressorSquashReceived(rawVal);
    else if (param == sGraphicEQBand1[0])
      midiGraphicEQBand1Received(rawVal);
    else if (param == sGraphicEQBand2[0])
      midiGraphicEQBand2Received(rawVal);
    else if (param == sGraphicEQBand3[0])
      midiGraphicEQBand3Received(rawVal);
    else if (param == sGraphicEQBand4[0])
      midiGraphicEQBand4Received(rawVal);
    else if (param == sGraphicEQBand5[0])
      midiGraphicEQBand5Received(rawVal);
    else if (param == sGraphicEQBand6[0])
      midiGraphicEQBand6Received(rawVal);
    else if (param == sGraphicEQBand7[0])
      midiGraphicEQBand7Received(rawVal);
    else if (param == sGraphicEQBand8[0])
      midiGraphicEQBand8Received(rawVal);
    else if (param == sParametricEQLowGain[0])
      midiParametricEQLowGainReceived(rawVal);
    else if (param == sParametricEQLowFrequency[0])
      midiParametricEQLowFrequencyReceived(rawVal);
    else if (param == sParametricEQHighGain[0])
      midiParametricEQHighGainReceived(rawVal);
    else if (param == sParametricEQHighFrequency[0])
      midiParametricEQHighFrequencyReceived(rawVal);
    else if (param == sParametricEQPeakGain[0])
      midiParametricEQPeakGainReceived(rawVal);
    else if (param == sParametricEQPeakFrequency[0])
      midiParametricEQPeakFrequencyReceived(rawVal);
    else if (param == sParametricEQPeakQFactor[0])
      midiParametricEQPeakQFactorReceived(rawVal);
    else if (param == sParametricEQPeakGain2[0])
      midiParametricEQPeakGain2Received(rawVal);
    else if (param == sParametricEQPeakFrequency2[0])
      midiParametricEQPeakFrequency2Received(rawVal);
    else if (param == sParametricEQPeakQFactor2[0])
      midiParametricEQPeakQFactor2Received(rawVal);
    else if (param == sWahPeakRange[0])
      midiWahPeakRangeReceived(rawVal);
    else if (param == sDucking[0])
      midiDuckingReceived(rawVal);
    else if (param == sIntensity[0])
      midiIntensityReceived(rawVal);
    else if (param == sVoiceMix[0])
      midiVoiceMixReceived(rawVal);
    else if (param == sVoice1Pitch[0])
      midiVoice1PitchReceived(rawVal);
    else if (param == sVoice2Pitch[0])
      midiVoice2PitchReceived(rawVal);
    else if (param == sDetune[0])
      midiDetuneReceived(rawVal);
    else if (param == sSmoothChords[0])
      midiSmoothChordsReceived(rawVal);
    else if (param == sPureTuning[0])
      midiPureTuningReceived(rawVal);
    else if (param == sVoice1Interval[0])
      midiVoice1IntervalReceived(rawVal);
    else if (param == sVoice2Interval[0])
      midiVoice2IntervalReceived(rawVal);
    else if (param == sKey[0])
      midiKeyReceived(rawVal);
    else if (param == sFormantShiftOnOff[0])
      midiFormantShiftOnOffReceived(rawVal);
    else if (param == sFormantShift[0])
      midiFormantShiftReceived(rawVal);
    else if (param == sLowCut[0])
      midiLowCutReceived(rawVal);
    else if (param == sHighCut[0])
      midiHighCutReceived(rawVal);
    else if (param == sDelayMix[0])
      midiDelayMixReceived(rawVal);
    else if (param == sDelay1Time[0])
      midiDelay1TimeReceived(rawVal);
    else if (param == sDelay2Ratio[0])
      midiDelay2RatioReceived(rawVal);
    else if (param == sDelayNoteValue1[0])
      midiDelayNoteValue1Received(rawVal);
    else if (param == sDelayNoteValue2[0])
      midiDelayNoteValue2Received(rawVal);
    else if (param == sDelayFeedback[0])
      midiDelayFeedbackReceived(rawVal);
    else if (param == sDelayToTempo[0])
      midiDelayToTempoReceived(rawVal);
    else if (param == sDelayModulation[0])
      midiDelayModulationReceived(rawVal);
}

unsigned char StompMidi::getId() {
  unsigned char ret = 0x32; // 50 in decimal
  //offset for stomp slot
  ret += this->getInstance();
  return ret;
}

void StompMidi::midiApplyType(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sType, rawVal));
}

void StompMidi::midiApplyOnOff(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sOnOff, rawVal));
}

void StompMidi::midiApplyMix(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sMix, rawVal));
}

void StompMidi::midiApplyVolume(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sVolume, rawVal));
}

void StompMidi::midiApplyStereo(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sStereo, rawVal));
}

void StompMidi::midiApplyWahManual(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sWahManual, rawVal));
}

void StompMidi::midiApplyWahPeak(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sWahPeak, rawVal));
}

void StompMidi::midiApplyWahRange(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sWahRange, rawVal));
}

void StompMidi::midiApplyWahPedalMode(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sWahPedalMode, rawVal));
}

void StompMidi::midiApplyWahTouchAttack(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sWahTouchAttack, rawVal));
}

void StompMidi::midiApplyWahTouchRelease(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sWahTouchRelease, rawVal));
}

void StompMidi::midiApplyWahTouchBoost(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sWahTouchBoost, rawVal));
}

void StompMidi::midiApplyDistortionShaperDrive(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(),
                                              sDistortionShaperDrive, rawVal));
}

void StompMidi::midiApplyDistortionBoosterTone(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(),
                                              sDistortionBoosterTone, rawVal));
}

void StompMidi::midiApplyCompressorGateIntensity(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(
      getAddressPage(), sCompressorGateIntensity, rawVal));
}

void StompMidi::midiApplyCompressorAttack(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sCompressorAttack, rawVal));
}

void StompMidi::midiApplyModulationRate(unsigned short rawVal) {
      Midi::get().sendCmd(
              createSingleParamSetCmd(getAddressPage(), sModulationRate, rawVal));
}

void StompMidi::midiApplyModulationDepth(unsigned short rawVal) {
    Midi::get().sendCmd(
        createSingleParamSetCmd(getAddressPage(), sModulationDepth, rawVal));
}

void StompMidi::midiApplyModulationFeedback(unsigned short rawVal) {
    Midi::get().sendCmd(
        createSingleParamSetCmd(getAddressPage(), sModulationFeedback, rawVal));
}

void StompMidi::midiApplyModulationCrossover(unsigned short rawVal) {
    Midi::get().sendCmd(
        createSingleParamSetCmd(getAddressPage(), sModulationCrossover, rawVal));
}

void StompMidi::midiApplyModulationHyperChorusAmount(unsigned short rawVal) {
    Midi::get().sendCmd(createSingleParamSetCmd(
        getAddressPage(), sModulationHyperChorusAmount, rawVal));
}

void StompMidi::midiApplyModulationManual(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sModulationManual, rawVal));
}

void StompMidi::midiApplyModulationPhaserPeakSpread(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(
      getAddressPage(), sModulationPhaserPeakSpread, rawVal));
}

void StompMidi::midiApplyModulationPhaserStages(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(),
                                              sModulationPhaserStages, rawVal));
}

void StompMidi::midiApplyRotarySpeed(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sRotarySpeed, rawVal));
}

void StompMidi::midiApplyRotaryDistance(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sRotaryDistance, rawVal));
}

void StompMidi::midiApplyRotaryBalance(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sRotaryBalance, rawVal));
}

void StompMidi::midiApplyCompressorSquash(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sCompressorSquash, rawVal));
}

void StompMidi::midiApplyGraphicEQBand1(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sGraphicEQBand1, rawVal));
}

void StompMidi::midiApplyGraphicEQBand2(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sGraphicEQBand2, rawVal));
}

void StompMidi::midiApplyGraphicEQBand3(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sGraphicEQBand3, rawVal));
}

void StompMidi::midiApplyGraphicEQBand4(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sGraphicEQBand4, rawVal));
}

void StompMidi::midiApplyGraphicEQBand5(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sGraphicEQBand5, rawVal));
}

void StompMidi::midiApplyGraphicEQBand6(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sGraphicEQBand6, rawVal));
}

void StompMidi::midiApplyGraphicEQBand7(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sGraphicEQBand7, rawVal));
}

void StompMidi::midiApplyGraphicEQBand8(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sGraphicEQBand8, rawVal));
}

void StompMidi::midiApplyParametricEQLowGain(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sParametricEQLowGain, rawVal));
}

void StompMidi::midiApplyParametricEQLowFrequency(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(
      getAddressPage(), sParametricEQLowFrequency, rawVal));
}

void StompMidi::midiApplyParametricEQHighGain(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sParametricEQHighGain, rawVal));
}

void StompMidi::midiApplyParametricEQHighFrequency(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(
      getAddressPage(), sParametricEQHighFrequency, rawVal));
}

void StompMidi::midiApplyParametricEQPeakGain(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sParametricEQPeakGain, rawVal));
}

void StompMidi::midiApplyParametricEQPeakFrequency(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(
      getAddressPage(), sParametricEQPeakFrequency, rawVal));
}

void StompMidi::midiApplyParametricEQPeakQFactor(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(
      getAddressPage(), sParametricEQPeakQFactor, rawVal));
}

void StompMidi::midiApplyParametricEQPeakGain2(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(),
                                              sParametricEQPeakGain2, rawVal));
}

void StompMidi::midiApplyParametricEQPeakFrequency2(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(
      getAddressPage(), sParametricEQPeakFrequency2, rawVal));
}

void StompMidi::midiApplyParametricEQPeakQFactor2(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(
      getAddressPage(), sParametricEQPeakQFactor2, rawVal));
}

void StompMidi::midiApplyWahPeakRange(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sWahPeakRange, rawVal));
}

void StompMidi::midiApplyDucking(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sDucking, rawVal));
}

void StompMidi::midiApplyIntensity(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sIntensity, rawVal));
}

void StompMidi::midiApplyVoiceMix(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sVoiceMix, rawVal));
}

void StompMidi::midiApplyVoice1Pitch(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sVoice1Pitch, rawVal));
}

void StompMidi::midiApplyVoice2Pitch(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sVoice2Pitch, rawVal));
}

void StompMidi::midiApplyDetune(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sDetune, rawVal));
}

void StompMidi::midiApplySmoothChords(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sSmoothChords, rawVal));
}

void StompMidi::midiApplyVoice1Interval(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sVoice1Interval, rawVal));
}

void StompMidi::midiApplyVoice2Interval(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sVoice2Interval, rawVal));
}

void StompMidi::midiApplyPureTuning(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sPureTuning, rawVal));
}

void StompMidi::midiApplyKey(unsigned short rawVal) {
  Midi::get().sendCmd(createSingleParamSetCmd(getAddressPage(), sKey, rawVal));
}

void StompMidi::midiApplyFormantShiftOnOff(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sFormantShiftOnOff, rawVal));
}

void StompMidi::midiApplyFormantShift(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sFormantShift, rawVal));
}

void StompMidi::midiApplyLowCut(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sLowCut, rawVal));
}

void StompMidi::midiApplyHighCut(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sHighCut, rawVal));
}

void StompMidi::midiApplyDelayMix(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sDelayMix, rawVal));
}

void StompMidi::midiApplyDelay1Time(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sDelay1Time, rawVal));
}

void StompMidi::midiApplyDelay2Ratio(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sDelay2Ratio, rawVal));
}


void StompMidi::midiApplyDelayNoteValue1(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sDelayNoteValue1, rawVal));
}

void StompMidi::midiApplyDelayNoteValue2(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sDelayNoteValue2, rawVal));
}

void StompMidi::midiApplyDelayFeedback(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sDelayFeedback, rawVal));
}

void StompMidi::midiApplyDelayToTempo(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sDelayToTempo, rawVal));
}

void StompMidi::midiApplyDelayModulation(unsigned short rawVal) {
  Midi::get().sendCmd(
      createSingleParamSetCmd(getAddressPage(), sDelayModulation, rawVal));
}

ByteArray StompMidi::getAddressPage() {
  switch (mInstance) {
  case StompA:
    return sAddressPageA;
  case StompB:
    return sAddressPageB;
  case StompC:
    return sAddressPageC;
  case StompD:
    return sAddressPageD;
  case StompX:
    return sAddressPageX;
  case StompMod:
    return sAddressPageMod;
  case StompDelay:
    return sAddressPageDelay;
  }
}
