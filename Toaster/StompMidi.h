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
#ifndef STOMPMIDI_H
#define STOMPMIDI_H
#include "SysExBase.h"
#include "SysExMsgDispatcher.h"
#include <map>

class StompMidi : public SysExBase, public SysExMsgDispatcher::ISysExConsumer {
public:
  StompInstance getInstance() { return mInstance; }

protected:
  // address pages
  BYTEARRAYDECL(AddressPageA)
  BYTEARRAYDECL(AddressPageB)
  BYTEARRAYDECL(AddressPageC)
  BYTEARRAYDECL(AddressPageD)
  BYTEARRAYDECL(AddressPageX)
  BYTEARRAYDECL(AddressPageMod)
  BYTEARRAYDECL(AddressPageDelay)

  // parameter
  BYTEARRAYDECL(Type)
  BYTEARRAYDECL(OnOff)
  BYTEARRAYDECL(Mix)
  BYTEARRAYDECL(Volume)
  BYTEARRAYDECL(Stereo)
  BYTEARRAYDECL(WahManual)
  BYTEARRAYDECL(WahPeak)
  BYTEARRAYDECL(WahRange)
  BYTEARRAYDECL(WahPedalMode)
  BYTEARRAYDECL(WahTouchAttack)
  BYTEARRAYDECL(WahTouchRelease)
  BYTEARRAYDECL(WahTouchBoost)
  BYTEARRAYDECL(DistortionShaperDrive)
  BYTEARRAYDECL(DistortionBoosterTone)
  BYTEARRAYDECL(CompressorGateIntensity)
  BYTEARRAYDECL(CompressorAttack)
  BYTEARRAYDECL(ModulationRate)
  BYTEARRAYDECL(ModulationDepth)
  BYTEARRAYDECL(ModulationFeedback)
  BYTEARRAYDECL(ModulationCrossover)
  BYTEARRAYDECL(ModulationHyperChorusAmount)
  BYTEARRAYDECL(ModulationManual)
  BYTEARRAYDECL(ModulationPhaserPeakSpread)
  BYTEARRAYDECL(ModulationPhaserStages)
  BYTEARRAYDECL(RotarySpeed)
  BYTEARRAYDECL(RotaryDistance)
  BYTEARRAYDECL(RotaryBalance)
  BYTEARRAYDECL(CompressorSquash)
  BYTEARRAYDECL(GraphicEQBand1)
  BYTEARRAYDECL(GraphicEQBand2)
  BYTEARRAYDECL(GraphicEQBand3)
  BYTEARRAYDECL(GraphicEQBand4)
  BYTEARRAYDECL(GraphicEQBand5)
  BYTEARRAYDECL(GraphicEQBand6)
  BYTEARRAYDECL(GraphicEQBand7)
  BYTEARRAYDECL(GraphicEQBand8)
  BYTEARRAYDECL(ParametricEQLowGain)
  BYTEARRAYDECL(ParametricEQLowFrequency)
  BYTEARRAYDECL(ParametricEQHighGain)
  BYTEARRAYDECL(ParametricEQHighFrequency)
  BYTEARRAYDECL(ParametricEQPeakGain)
  BYTEARRAYDECL(ParametricEQPeakFrequency)
  BYTEARRAYDECL(ParametricEQPeakQFactor)
  BYTEARRAYDECL(ParametricEQPeakGain2)
  BYTEARRAYDECL(ParametricEQPeakFrequency2)
  BYTEARRAYDECL(ParametricEQPeakQFactor2)
  BYTEARRAYDECL(WahPeakRange)
  BYTEARRAYDECL(Ducking)
  BYTEARRAYDECL(Intensity)
  BYTEARRAYDECL(VoiceMix)
  BYTEARRAYDECL(Voice1Pitch)
  BYTEARRAYDECL(Voice2Pitch)
  BYTEARRAYDECL(Voice3Pitch)
  BYTEARRAYDECL(Voice4Pitch)
  BYTEARRAYDECL(Detune)
  BYTEARRAYDECL(SmoothChords)
  BYTEARRAYDECL(PureTuning)
  BYTEARRAYDECL(Voice1Interval)
  BYTEARRAYDECL(Voice2Interval)
  BYTEARRAYDECL(Voice3Interval)
  BYTEARRAYDECL(Voice4Interval)
  BYTEARRAYDECL(Key)
  BYTEARRAYDECL(FormantShiftOnOff)
  BYTEARRAYDECL(FormantShift)
  BYTEARRAYDECL(LowCut)
  BYTEARRAYDECL(HighCut)
  BYTEARRAYDECL(DelayMix)
  BYTEARRAYDECL(Delay1Time)
  BYTEARRAYDECL(Delay2Time)
  BYTEARRAYDECL(Delay3Time)
  BYTEARRAYDECL(Delay4Time)
  BYTEARRAYDECL(Delay1Volume)
  BYTEARRAYDECL(Delay2Volume)
  BYTEARRAYDECL(Delay3Volume)
  BYTEARRAYDECL(Delay4Volume)
  BYTEARRAYDECL(Delay1Panorama)
  BYTEARRAYDECL(Delay2Panorama)
  BYTEARRAYDECL(Delay3Panorama)
  BYTEARRAYDECL(Delay4Panorama)
  BYTEARRAYDECL(Delay2Ratio)
  BYTEARRAYDECL(Delay3Ratio)
  BYTEARRAYDECL(Delay4Ratio)
  BYTEARRAYDECL(DelayNoteValue1)
  BYTEARRAYDECL(DelayNoteValue2)
  BYTEARRAYDECL(DelayNoteValue3)
  BYTEARRAYDECL(DelayNoteValue4)
  BYTEARRAYDECL(DelayFeedback)
  BYTEARRAYDECL(DelayFeedback2)
  BYTEARRAYDECL(DelayToTempo)
  BYTEARRAYDECL(DelayModulation)
  BYTEARRAYDECL(DelayInfinity)
  BYTEARRAYDECL(DelayInfinityFeedback)
  BYTEARRAYDECL(DelayFilterIntensity)
  BYTEARRAYDECL(DelayFlutterIntensity)
  BYTEARRAYDECL(DelayFlutterShape)
  BYTEARRAYDECL(DelayLowCut)
  BYTEARRAYDECL(DelayHighCut)
  BYTEARRAYDECL(DelaySwell)
  BYTEARRAYDECL(DelaySmear)
  BYTEARRAYDECL(DelayChorus)
  BYTEARRAYDECL(DelayGrit)
  BYTEARRAYDECL(DelayReverseMix)
  BYTEARRAYDECL(DelayFeedbackSyncSwitch)
  BYTEARRAYDECL(DelayDuckingPrePost)

  StompMidi(StompInstance instance);
  ~StompMidi();

  // ISysExConsumer
  void consumeSysExMsg(const ByteArray &msg) override final;
  void consumeSysExMsg(unsigned char, uint16_t rawVal) override final;
  unsigned char getId() override final;

  // parameter
  // Type
  void midiApplyType(unsigned short rawVal);
  // OnOff
  void midiApplyOnOff(unsigned short rawVal);
  // Mix
  void midiApplyMix(unsigned short rawVal);
  // Volume
  void midiApplyVolume(unsigned short rawVal);
  // Stereo
  void midiApplyStereo(unsigned short rawVal);
  // WahManual
  void midiApplyWahManual(unsigned short rawVal);
  // WahPeak
  void midiApplyWahPeak(unsigned short rawVal);
  // WahRange
  void midiApplyWahRange(unsigned short rawVal);
  // WahPedalMode
  void midiApplyWahPedalMode(unsigned short rawVal);
  // WahTouchAttack
  void midiApplyWahTouchAttack(unsigned short rawVal);
  // WahTouchRelease
  void midiApplyWahTouchRelease(unsigned short rawVal);
  // WahTouchBoost
  void midiApplyWahTouchBoost(unsigned short rawVal);
  // DistortionShaperDrive
  void midiApplyDistortionShaperDrive(unsigned short rawVal);
  // DistortionBoosterTone
  void midiApplyDistortionBoosterTone(unsigned short rawVal);
  // CompressorGateIntensity
  void midiApplyCompressorGateIntensity(unsigned short rawVal);
  // CompressorAttack
  void midiApplyCompressorAttack(unsigned short rawVal);
  // ModulationRate
  void midiApplyModulationRate(unsigned short rawVal);
  // ModulationDepth
  void midiApplyModulationDepth(unsigned short rawVal);
  // ModulationFeedback
  void midiApplyModulationFeedback(unsigned short rawVal);
  // ModulationCrossover
  void midiApplyModulationCrossover(unsigned short rawVal);
  // ModulationHyperChorusAmount
  void midiApplyModulationHyperChorusAmount(unsigned short rawVal);
  // ModulationManual
  void midiApplyModulationManual(unsigned short rawVal);
  // ModulationPhaserPeakSpread
  void midiApplyModulationPhaserPeakSpread(unsigned short rawVal);
  // ModulationPhaserStages
  void midiApplyModulationPhaserStages(unsigned short rawVal);
  // RotarySpeed
  void midiApplyRotarySpeed(unsigned short rawVal);
  // RotaryDistance
  void midiApplyRotaryDistance(unsigned short rawVal);
  // RotaryBalance
  void midiApplyRotaryBalance(unsigned short rawVal);
  // CompressorSquash
  void midiApplyCompressorSquash(unsigned short rawVal);
  // GraphicEQBand1
  void midiApplyGraphicEQBand1(unsigned short rawVal);
  // GraphicEQBand2
  void midiApplyGraphicEQBand2(unsigned short rawVal);
  // GraphicEQBand3
  void midiApplyGraphicEQBand3(unsigned short rawVal);
  // GraphicEQBand4
  void midiApplyGraphicEQBand4(unsigned short rawVal);
  // GraphicEQBand5
  void midiApplyGraphicEQBand5(unsigned short rawVal);
  // GraphicEQBand6
  void midiApplyGraphicEQBand6(unsigned short rawVal);
  // GraphicEQBand7
  void midiApplyGraphicEQBand7(unsigned short rawVal);
  // GraphicEQBand8
  void midiApplyGraphicEQBand8(unsigned short rawVal);
  // ParametricEQLowGain
  void midiApplyParametricEQLowGain(unsigned short rawVal);
  // ParametricEQLowFrequency
  void midiApplyParametricEQLowFrequency(unsigned short rawVal);
  // ParametricEQHighGain
  void midiApplyParametricEQHighGain(unsigned short rawVal);
  // ParametricEQHighFrequency
  void midiApplyParametricEQHighFrequency(unsigned short rawVal);
  // ParametricEQPeakGain
  void midiApplyParametricEQPeakGain(unsigned short rawVal);
  // ParametricEQPeakFrequency
  void midiApplyParametricEQPeakFrequency(unsigned short rawVal);
  // ParametricEQPeakQFactor
  void midiApplyParametricEQPeakQFactor(unsigned short rawVal);
  // ParametricEQPeakGain2
  void midiApplyParametricEQPeakGain2(unsigned short rawVal);
  // ParametricEQPeakFrequency2
  void midiApplyParametricEQPeakFrequency2(unsigned short rawVal);
  // ParametricEQPeakQFactor2
  void midiApplyParametricEQPeakQFactor2(unsigned short rawVal);
  // WahPeakRange
  void midiApplyWahPeakRange(unsigned short rawVal);
  // Ducking
  void midiApplyDucking(unsigned short rawVal);
  // Intensity
  void midiApplyIntensity(unsigned short rawVal);
  // VoiceMix
  void midiApplyVoiceMix(unsigned short rawVal);
  // Voice1Pitch
  void midiApplyVoice1Pitch(unsigned short rawVal);
  // Voice2Pitch
  void midiApplyVoice2Pitch(unsigned short rawVal);
  // Detune
  void midiApplyDetune(unsigned short rawVal);
  // SmoothChords
  void midiApplySmoothChords(unsigned short rawVal);
  // PureTuning
  void midiApplyPureTuning(unsigned short rawVal);
  // Voice1Interval
  void midiApplyVoice1Interval(unsigned short rawVal);
  // Voice2Interval
  void midiApplyVoice2Interval(unsigned short rawVal);
  // Key
  void midiApplyKey(unsigned short rawVal);
  // FormantShiftOnOff
  void midiApplyFormantShiftOnOff(unsigned short rawVal);
  // FormantShift
  void midiApplyFormantShift(unsigned short rawVal);
  // LowCut
  void midiApplyLowCut(unsigned short rawVal);
  // HighCut
  void midiApplyHighCut(unsigned short rawVal);
  // DelayMix
  void midiApplyDelayMix(unsigned short rawVal);
  // Delay1Time
  void midiApplyDelay1Time(unsigned short rawVal);
  // Delay2Ratio
  void midiApplyDelay2Ratio(unsigned short rawVal);
  // DelayNoteValue1
  void midiApplyDelayNoteValue1(unsigned short rawVal);
  // DelayNoteValue2
  void midiApplyDelayNoteValue2(unsigned short rawVal);
  // DelayFeedback
  void midiApplyDelayFeedback(unsigned short rawVal);
  // DelayToTempo
  void midiApplyDelayToTempo(unsigned short rawVal);
  // DelayModulation
  void midiApplyDelayModulation(unsigned short rawVal);

  // receive callbacks for derived class
  virtual void midiTypeReceived(unsigned short rawVal) = 0;
  virtual void midiOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiMixReceived(unsigned short rawVal) = 0;
  virtual void midiVolumeReceived(unsigned short rawVal) = 0;
  virtual void midiStereoReceived(unsigned short rawVal) = 0;
  virtual void midiWahManualReceived(unsigned short rawVal) = 0;
  virtual void midiWahPeakReceived(unsigned short rawVal) = 0;
  virtual void midiWahRangeReceived(unsigned short rawVal) = 0;
  virtual void midiWahPedalModeReceived(unsigned short rawVal) = 0;
  virtual void midiWahTouchAttackReceived(unsigned short rawVal) = 0;
  virtual void midiWahTouchReleaseReceived(unsigned short rawVal) = 0;
  virtual void midiWahTouchBoostReceived(unsigned short rawVal) = 0;
  virtual void midiDistortionShaperDriveReceived(unsigned short rawVal) = 0;
  virtual void midiDistortionBoosterToneReceived(unsigned short rawVal) = 0;
  virtual void midiCompressorGateIntensityReceived(unsigned short rawVal) = 0;
  virtual void midiCompressorAttackReceived(unsigned short rawVal) = 0;
  virtual void midiModulationRateReceived(unsigned short rawVal) = 0;
  virtual void midiModulationDepthReceived(unsigned short rawVal) = 0;
  virtual void midiModulationFeedbackReceived(unsigned short rawVal) = 0;
  virtual void midiModulationCrossoverReceived(unsigned short rawVal) = 0;
  virtual void
  midiModulationHyperChorusAmountReceived(unsigned short rawVal) = 0;
  virtual void midiModulationManualReceived(unsigned short rawVal) = 0;
  virtual void
  midiModulationPhaserPeakSpreadReceived(unsigned short rawVal) = 0;
  virtual void midiModulationPhaserStagesReceived(unsigned short rawVal) = 0;
  virtual void midiRotarySpeedReceived(unsigned short rawVal) = 0;
  virtual void midiRotaryDistanceReceived(unsigned short rawVal) = 0;
  virtual void midiRotaryBalanceReceived(unsigned short rawVal) = 0;
  virtual void midiCompressorSquashReceived(unsigned short rawVal) = 0;
  virtual void midiGraphicEQBand1Received(unsigned short rawVal) = 0;
  virtual void midiGraphicEQBand2Received(unsigned short rawVal) = 0;
  virtual void midiGraphicEQBand3Received(unsigned short rawVal) = 0;
  virtual void midiGraphicEQBand4Received(unsigned short rawVal) = 0;
  virtual void midiGraphicEQBand5Received(unsigned short rawVal) = 0;
  virtual void midiGraphicEQBand6Received(unsigned short rawVal) = 0;
  virtual void midiGraphicEQBand7Received(unsigned short rawVal) = 0;
  virtual void midiGraphicEQBand8Received(unsigned short rawVal) = 0;
  virtual void midiParametricEQLowGainReceived(unsigned short rawVal) = 0;
  virtual void midiParametricEQLowFrequencyReceived(unsigned short rawVal) = 0;
  virtual void midiParametricEQHighGainReceived(unsigned short rawVal) = 0;
  virtual void midiParametricEQHighFrequencyReceived(unsigned short rawVal) = 0;
  virtual void midiParametricEQPeakGainReceived(unsigned short rawVal) = 0;
  virtual void midiParametricEQPeakFrequencyReceived(unsigned short rawVal) = 0;
  virtual void midiParametricEQPeakQFactorReceived(unsigned short rawVal) = 0;
  virtual void midiParametricEQPeakGain2Received(unsigned short rawVal) = 0;
  virtual void
  midiParametricEQPeakFrequency2Received(unsigned short rawVal) = 0;
  virtual void midiParametricEQPeakQFactor2Received(unsigned short rawVal) = 0;
  virtual void midiWahPeakRangeReceived(unsigned short rawVal) = 0;
  virtual void midiDuckingReceived(unsigned short rawVal) = 0;
  virtual void midiIntensityReceived(unsigned short rawVal) = 0;
  virtual void midiVoiceMixReceived(unsigned short rawVal) = 0;
  virtual void midiVoice1PitchReceived(unsigned short rawVal) = 0;
  virtual void midiVoice2PitchReceived(unsigned short rawVal) = 0;
  virtual void midiDetuneReceived(unsigned short rawVal) = 0;
  virtual void midiSmoothChordsReceived(unsigned short rawVal) = 0;
  virtual void midiPureTuningReceived(unsigned short rawVal) = 0;
  virtual void midiVoice1IntervalReceived(unsigned short rawVal) = 0;
  virtual void midiVoice2IntervalReceived(unsigned short rawVal) = 0;
  virtual void midiKeyReceived(unsigned short rawVal) = 0;
  virtual void midiFormantShiftOnOffReceived(unsigned short rawVal) = 0;
  virtual void midiFormantShiftReceived(unsigned short rawVal) = 0;
  virtual void midiLowCutReceived(unsigned short rawVal) = 0;
  virtual void midiHighCutReceived(unsigned short rawVal) = 0;
  virtual void midiDelayMixReceived(unsigned short rawVal) = 0;
  virtual void midiDelay1TimeReceived(unsigned short rawVal) = 0;
  virtual void midiDelay2RatioReceived(unsigned short rawVal) = 0;
  virtual void midiDelayNoteValue1Received(unsigned short rawVal) = 0;
  virtual void midiDelayNoteValue2Received(unsigned short rawVal) = 0;
  virtual void midiDelayFeedbackReceived(unsigned short rawVal) = 0;
  virtual void midiDelayToTempoReceived(unsigned short rawVal) = 0;
  virtual void midiDelayModulationReceived(unsigned short rawVal) = 0;

  StompInstance mInstance;

  class FXType2MidiRawValMap : public std::map<FXType, unsigned short> {
  public:
    FXType2MidiRawValMap() {
      (*this)[None] = 0x00;
      (*this)[WahWah] = 0x01;
      (*this)[WahLowPass] = 0x02;
      (*this)[WahHighPass] = 0x03;
      (*this)[WahVowelFilter] = 0x04;
      (*this)[WahPhaser] = 0x06;
      (*this)[WahFlanger] = 0x07;
      (*this)[WahRateReducer] = 0x08;
      (*this)[WahRingModulator] = 0x09;
      (*this)[WahFrequencyShifter] = 0x0A;
      (*this)[WahFormantShifter] = 0x0C;
      (*this)[BitShaper] = 0x11;
      (*this)[RectiShaper] = 0x12;
      (*this)[SoftShaper] = 0x13;
      (*this)[HardShaper] = 0x14;
      (*this)[WaveShaper] = 0x15;
      (*this)[GreenScream] = 0x21;
      (*this)[PlusDS] = 0x22;
      (*this)[OneDS] = 0x23;
      (*this)[Muffin] = 0x24;
      (*this)[MouseDS] = 0x25;
      (*this)[FuzzDS] = 0x26;
      (*this)[MetalDS] = 0x27;
      (*this)[TrebleBooster] = 0x71;
      (*this)[LeadBooster] = 0x72;
      (*this)[PureBooster] = 0x73;
      (*this)[WahPedalBooster] = 0x74;
      (*this)[GraphicEqualizer] = 0x61;
      (*this)[StudioEqualizer] = 0x62;
      (*this)[MetalEqualizer] = 0x63;
      (*this)[StereoWidener] = 0x65;
      (*this)[Compressor] = 0x31;
      (*this)[NoiseGate21] = 0x39;
      (*this)[NoiseGate41] = 0x3A;
      (*this)[VintageChorus] = 0x41;
      (*this)[HyperChorus] = 0x42;
      (*this)[AirChorus] = 0x43;
      (*this)[MicroPitch] = 0x47;
      (*this)[Vibrato] = 0x44;
      (*this)[RotarySpeaker] = 0x45;
      (*this)[Tremolo] = 0x46;
      (*this)[Phaser] = 0x51;
      (*this)[PhaserVibe] = 0x52;
      (*this)[PhaserOneway] = 0x53;
      (*this)[Flanger] = 0x59;
      (*this)[FlangerOneway] = 0x5B;
      (*this)[Space] = 0x40;
      (*this)[LegacyDelay] = 0x91;
      (*this)[SingleDelay] = 0x92;
      (*this)[DualDelay] = 0x93;
      (*this)[TwoTapDelay] = 0x94;
      (*this)[SerialTwoTapDelay] = 0x95;
      (*this)[RhythmDelay] = 0xA1;
      (*this)[QuadDelay] = 0xA4;
      (*this)[DualCrystal] = 0x8B;
      (*this)[Transpose] = 0x81;
      (*this)[PedalPitch] = 0x0B;
      (*this)[PedalVinylStop] = 0x0D;
      (*this)[ChromaticPitch] = 0x82;
      (*this)[HarmonicPitch] = 0x83;
      (*this)[AnalogOctaver] = 0x84;
      (*this)[LoopMono] = 0x79;
      (*this)[LoopStereo] = 0x7A;
      (*this)[LoopDistortion] = 0x7B;
    }
    ~FXType2MidiRawValMap() { clear(); }
  };

  class MidiRawValMap2FXType : public std::map<unsigned short, FXType> {
  public:
    MidiRawValMap2FXType() {
      (*this)[0x00] = None;
      (*this)[0x01] = WahWah;
      (*this)[0x02] = WahLowPass;
      (*this)[0x03] = WahHighPass;
      (*this)[0x04] = WahVowelFilter;
      (*this)[0x06] = WahPhaser;
      (*this)[0x07] = WahFlanger;
      (*this)[0x08] = WahRateReducer;
      (*this)[0x09] = WahRingModulator;
      (*this)[0x0A] = WahFrequencyShifter;
      (*this)[0x0C] = WahFormantShifter;
      (*this)[0x11] = BitShaper;
      (*this)[0x12] = RectiShaper;
      (*this)[0x13] = SoftShaper;
      (*this)[0x14] = HardShaper;
      (*this)[0x15] = WaveShaper;
      (*this)[0x21] = GreenScream;
      (*this)[0x22] = PlusDS;
      (*this)[0x23] = OneDS;
      (*this)[0x24] = Muffin;
      (*this)[0x25] = MouseDS;
      (*this)[0x26] = FuzzDS;
      (*this)[0x27] = MetalDS;
      (*this)[0x71] = TrebleBooster;
      (*this)[0x72] = LeadBooster;
      (*this)[0x73] = PureBooster;
      (*this)[0x74] = WahPedalBooster;
      (*this)[0x61] = GraphicEqualizer;
      (*this)[0x62] = StudioEqualizer;
      (*this)[0x63] = MetalEqualizer;
      (*this)[0x65] = StereoWidener;
      (*this)[0x31] = Compressor;
      (*this)[0x39] = NoiseGate21;
      (*this)[0x3A] = NoiseGate41;
      (*this)[0x41] = VintageChorus;
      (*this)[0x42] = HyperChorus;
      (*this)[0x43] = AirChorus;
      (*this)[0x47] = MicroPitch;
      (*this)[0x44] = Vibrato;
      (*this)[0x45] = RotarySpeaker;
      (*this)[0x46] = Tremolo;
      (*this)[0x51] = Phaser;
      (*this)[0x52] = PhaserVibe;
      (*this)[0x53] = PhaserOneway;
      (*this)[0x59] = Flanger;
      (*this)[0x5B] = FlangerOneway;
      (*this)[0x40] = Space;
      (*this)[0x91] = LegacyDelay;
      (*this)[0x92] = SingleDelay;
      (*this)[0x93] = DualDelay;
      (*this)[0x94] = TwoTapDelay;
      (*this)[0x95] = SerialTwoTapDelay;
      (*this)[0xA1] = RhythmDelay;
      (*this)[0xA4] = QuadDelay;
      (*this)[0x8B] = DualCrystal;
      (*this)[0x81] = Transpose;
      (*this)[0x0B] = PedalPitch;
      (*this)[0x0D] = PedalVinylStop;
      (*this)[0x82] = ChromaticPitch;
      (*this)[0x83] = HarmonicPitch;
      (*this)[0x84] = AnalogOctaver;
      (*this)[0x79] = LoopMono;
      (*this)[0x7A] = LoopStereo;
      (*this)[0x7B] = LoopDistortion;
    }

    ~MidiRawValMap2FXType() { clear(); }
  };

  static FXType2MidiRawValMap sFXType2MidiRawValMap;
  static MidiRawValMap2FXType sMidiRawValMap2FXType;

  // utility methods
  ByteArray getAddressPage();
  unsigned short fxType2Raw(FXType fxType) {
    return sFXType2MidiRawValMap[fxType];
  }
  FXType &raw2FXType(unsigned short rawVal) {
    return sMidiRawValMap2FXType[rawVal];
  }
};

#endif // STOMPMIDI_H
