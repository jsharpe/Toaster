/*  This file is part of Toaster, the editor and remote control for Kemper profiling amplifier.
*
*   Copyright (C) 2016  Thomas Langer
*
*   Toaster is free software: you can redistribute it and/or modify it under the terms of the
*   GNU General Public License as published by the Free Software Foundation, either version 3
*   of the License, or (at your option) any later version.
*
*   Toaster is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without
*   even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
*   See the GNU General Public License for more details.
*
*   You should have received a copy of the GNU General Public License along with Toaster.
*   If not, see <http://www.gnu.org/licenses/>.
*/
#include "BrowserFrame.h"
#include "ui_BrowserFrame.h"
#include "Delay.h"
#include "Eq.h"
#include "ExtParam.h"
#include "Profile.h"
#include "Stomp.h"
#include "Reverb.h"
#include "Settings.h"

BrowserFrame::BrowserFrame(QWidget *parent)
  : QFrame(parent)
{
  ui.setupUi(this);
  ui.browseModeDial->setValues(ui.lcdDisplay->getBrowserModeViews());
  // reverb
  connect(&reverbObj, &Reverb::onOffCutsTailReceived, this, &BrowserFrame::onReverbOnOff);
  // eq
  connect(&eqObj, &Eq::bassReceived, this, &BrowserFrame::onEqBass);
  connect(&eqObj, &Eq::middleReceived, this, &BrowserFrame::onEqMiddle);
  connect(&eqObj, &Eq::trebleReceived, this, &BrowserFrame::onEqTreble);
  connect(&eqObj, &Eq::presenceReceived, this, &BrowserFrame::onEqPresence);
  // profile
  connect(&profileObj, &Profile::rigNameReceived, this, &BrowserFrame::onRigName);
  connect(&profileObj, &Profile::rigAuthorReceived, this, &BrowserFrame::onRigAuthor);
  connect(&profileObj, &Profile::ampNameReceived, this, &BrowserFrame::onAmpName);
  // extended parameter
  connect(&extParamObj, &ExtParam::browserViewReceived, this, &BrowserFrame::onBrowserView);
}

void BrowserFrame::init(KemperStompState & stompState)
{
  this->stompState = &stompState;
  // stomps
  connect(&stompState.stompA, &Stomp::onOffReceived, this, &BrowserFrame::onStompAOnOff);
  connect(&stompState.stompB, &Stomp::onOffReceived, this, &BrowserFrame::onStompBOnOff);
  connect(&stompState.stompC, &Stomp::onOffReceived, this, &BrowserFrame::onStompCOnOff);
  connect(&stompState.stompD, &Stomp::onOffReceived, this, &BrowserFrame::onStompDOnOff);
  connect(&stompState.stompX, &Stomp::onOffReceived, this, &BrowserFrame::onStompXOnOff);
  connect(&stompState.stompMod, &Stomp::onOffReceived, this, &BrowserFrame::onStompModOnOff);
  connect(&stompState.stompA, &Stomp::typeReceived, this, &BrowserFrame::onStompAType);
  connect(&stompState.stompB, &Stomp::typeReceived, this, &BrowserFrame::onStompBType);
  connect(&stompState.stompC, &Stomp::typeReceived, this, &BrowserFrame::onStompCType);
  connect(&stompState.stompD, &Stomp::typeReceived, this, &BrowserFrame::onStompDType);
  connect(&stompState.stompX, &Stomp::typeReceived, this, &BrowserFrame::onStompXType);
  connect(&stompState.stompMod, &Stomp::typeReceived, this, &BrowserFrame::onStompModType);
  // delay
  if(Settings::get().getKPAOSVersion() >= 0x04000000)
  {
    connect(&stompState.stompDelay, &Stomp::onOffReceived, this, &BrowserFrame::onDelayOnOff);
    connect(&stompState.stompDelay, &Stomp::typeReceived, this, &BrowserFrame::onStompDelayType);
  }
  else
  {
    connect(&delayObj, &Delay::onOffCutsTailReceived, this, &BrowserFrame::onDelayOnOff);
  }
}

void BrowserFrame::requestValues()
{
  stompState->requestAllValues();
  extParamObj.requestAllValues();
}

//------------------------------------------------------------------------------------------

// stomps
// ui => kpa
// kpa => ui
void BrowserFrame::onStompAOnOff(bool onOff)
{
  ui.lcdDisplay->setStompAEnabled(onOff);
}

void BrowserFrame::onStompBOnOff(bool onOff)
{
  ui.lcdDisplay->setStompBEnabled(onOff);
}

void BrowserFrame::onStompCOnOff(bool onOff)
{
  ui.lcdDisplay->setStompCEnabled(onOff);
}

void BrowserFrame::onStompDOnOff(bool onOff)
{
  ui.lcdDisplay->setStompDEnabled(onOff);
}

void BrowserFrame::onStompXOnOff(bool onOff)
{
  ui.lcdDisplay->setStompXEnabled(onOff);
}

void BrowserFrame::onStompModOnOff(bool onOff)
{
  ui.lcdDisplay->setStompModEnabled(onOff);
}

void BrowserFrame::onStompAType(::FXType type)
{
  ui.lcdDisplay->setStompAFXType(type);
}

void BrowserFrame::onStompBType(::FXType type)
{
  ui.lcdDisplay->setStompBFXType(type);
}

void BrowserFrame::onStompCType(::FXType type)
{
  ui.lcdDisplay->setStompCFXType(type);
}

void BrowserFrame::onStompDType(::FXType type)
{
  ui.lcdDisplay->setStompDFXType(type);
}

void BrowserFrame::onStompXType(::FXType type)
{
  ui.lcdDisplay->setStompXFXType(type);
}

void BrowserFrame::onStompModType(::FXType type)
{
  ui.lcdDisplay->setStompModFXType(type);
}

void BrowserFrame::onStompDelayType(::FXType type)
{
  ui.lcdDisplay->setStompDelayFXType(type);
}

//------------------------------------------------------------------------------------------

// delay
// ui => kpa
// kpa => ui
void BrowserFrame::onDelayOnOff(bool onOff)
{
  ui.lcdDisplay->setDelayEnabled(onOff);
}
//------------------------------------------------------------------------------------------

// reverb
// ui => kpa
// kpa => ui
void BrowserFrame::onReverbOnOff(bool onOff)
{
  ui.lcdDisplay->setReverbEnabled(onOff);
}
//------------------------------------------------------------------------------------------

// eq
// ui => kpa
void BrowserFrame::on_eqBassDial_valueChanged(double value)
{
  eqObj.applyBass(value);
}

void BrowserFrame::on_eqBassDial_valueChanged(const QString &value)
{
  ui.lcdDisplay->setBrowserModeBassValueText(value);
}

void BrowserFrame::on_eqMiddleDial_valueChanged(double value)
{
  eqObj.applyMiddle(value);
}

void BrowserFrame::on_eqMiddleDial_valueChanged(const QString &value)
{
  ui.lcdDisplay->setBrowserModeMiddleValueText(value);
}

void BrowserFrame::on_eqTrebleDial_valueChanged(double value)
{
  eqObj.applyTreble(value);
}

void BrowserFrame::on_eqTrebleDial_valueChanged(const QString &value)
{
  ui.lcdDisplay->setBrowserModeTrebleValueText(value);
}

void BrowserFrame::on_eqPresenceDial_valueChanged(double value)
{
  eqObj.applyPresence(value);
}

void BrowserFrame::on_eqPresenceDial_valueChanged(const QString &value)
{
  ui.lcdDisplay->setBrowserModePresenceValueText(value);
}

// kpa => ui
void BrowserFrame::onEqBass(double bass)
{
  ui.eqBassDial->setValue(bass);
  update();
}

void BrowserFrame::onEqMiddle(double middle)
{
  ui.eqMiddleDial->setValue(middle);
  update();
}

void BrowserFrame::onEqTreble(double treble)
{
  ui.eqTrebleDial->setValue(treble);
  update();
}

void BrowserFrame::onEqPresence(double presence)
{
  ui.eqPresenceDial->setValue(presence);
  update();
}
//------------------------------------------------------------------------------------------

// profile
// ui => kpa
// kpa => ui
void BrowserFrame::onRigName(const QString& rigName)
{
  ui.lcdDisplay->setBrowserModeRigName(rigName);
}

void BrowserFrame::onRigAuthor(const QString& rigAuthor)
{
  ui.lcdDisplay->setBrowserModeRigAuthor(rigAuthor);
}

void BrowserFrame::onAmpName(const QString& ampName)
{
  ui.lcdDisplay->setBrowserModeAmpName(ampName);
}
//------------------------------------------------------------------------------------------

// extParam
// ui => kpa
void BrowserFrame::on_browseModeDial_valueChanged(int view)
{
  extParamObj.applyBrowserView(view);
}

// kpa => ui
void BrowserFrame::onBrowserView(unsigned int view)
{
  ui.lcdDisplay->setBrowserModeView(view);
}
//------------------------------------------------------------------------------------------





