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
#ifndef HARMONICPITCHFRAME_H
#define HARMONICPITCHFRAME_H
#include "Stomp.h"
#include "StompEditorPage.h"
#include "ui_HarmonicPitchFrame.h"
#include <QWidget>

class HarmonicPitchFrame : public QWidget, public IStompEditorPage {
  Q_OBJECT

public:
  explicit HarmonicPitchFrame(QWidget *parent = 0);
  ~HarmonicPitchFrame();
  // IStompEditorPage
  virtual void activate(QObject &stomp);
  virtual void deactivate();
  virtual bool isActive() { return mpStomp != nullptr; }
  virtual QObject *getStomp() { return mpStomp; }
  virtual QToasterLCD::Page getMaxDisplayPage();
  virtual QToasterLCD::Page getCurrentDisplayPage();
  virtual void setCurrentDisplayPage(QToasterLCD::Page page);

  virtual void displayStompType(StompInstance stompInstance, FXType fxType);
  virtual void displayStompEnabled(StompInstance stompInstance, bool enabled);
  virtual void displayDelayEnabled(bool enabled);
  virtual void displayReverbEnabled(bool enabled);
  virtual void displayAmpName(const QString &ampName);
private slots:
  // ui => kpa
  void on_voice1IntervalDial_valueChanged(int value);
  void on_voice2IntervalDial_valueChanged(int value);
  void on_formantShiftDial_valueChanged(double value);
  void on_keyDial_valueChanged(int valueIndex);
  void on_voiceMixDial_valueChanged(double value);
  void on_mixDial_valueChanged(double value);
  void on_duckingDial_valueChanged(double value);
  void on_volumeDial_valueChanged(double value);
  void on_pureTuningDial_valueChanged(int valueIndex);
  void on_formantShiftOnOffDial_valueChanged(int valueIndex);
  void on_stereoDial_valueChanged(double value);
  // kpa => ui
  void onVoice1Interval(int value);
  void onVoice2Interval(int value);
  void onFormantShift(double value);
  void onKey(int value);
  void onVoiceMix(double value);
  void onMix(double value);
  void onDucking(double value);
  void onVolume(double value);
  void onPureTuning(bool onOff);
  void onFormantShiftOnOff(bool onOff);
  void onStereo(double value);

private:
  Ui::HarmonicPitchFrame ui;
  Stomp *mpStomp = nullptr;
};

#endif // HARMONICPITCHFRAME_H
