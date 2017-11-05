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
#include "InputFrame.h"
#include "Global.h"
#include "LookUpTables.h"

InputFrame::InputFrame(QWidget *parent) : QWidget(parent) { ui.setupUi(this); }

InputFrame::~InputFrame() {}

void InputFrame::activate(QObject &module) {
  show();
  mpInput = qobject_cast<Input *>(&module);

  if (mpInput != nullptr) {
    connect(mpInput, &Input::cleanSenseReceived, this,
            &InputFrame::OnCleanSens);
    connect(mpInput, &Input::distortionSenseReceived, this,
            &InputFrame::OnDistortionSens);
    connect(&globalObj, &Global::inputSourceReceived, this,
            &InputFrame::OnInputSource);
    connect(&globalObj, &Global::reampSensReceived, this,
            &InputFrame::OnReampSens);

    mpInput->requestAllValues();
    globalObj.requestInputSource();
    globalObj.requestReampSense();
  }
}

void InputFrame::deactivate() {
  if (mpInput != nullptr) {
    disconnect(mpInput, &Input::cleanSenseReceived, this,
               &InputFrame::OnCleanSens);
    disconnect(mpInput, &Input::distortionSenseReceived, this,
               &InputFrame::OnDistortionSens);
    disconnect(&globalObj, &Global::inputSourceReceived, this,
               &InputFrame::OnInputSource);
    disconnect(&globalObj, &Global::reampSensReceived, this,
               &InputFrame::OnReampSens);
    mpInput = nullptr;
  }
}

QToasterLCD::Page InputFrame::getMaxDisplayPage() {
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page InputFrame::getCurrentDisplayPage() {
  return ui.lcdDisplay->currentPage();
}

void InputFrame::setCurrentDisplayPage(QToasterLCD::Page /*page*/) {}

void InputFrame::displayStompType(StompInstance stompInstance, FXType fxType) {
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void InputFrame::displayStompEnabled(StompInstance stompInstance,
                                     bool enabled) {
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void InputFrame::displayDelayEnabled(bool enabled) {
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void InputFrame::displayReverbEnabled(bool enabled) {
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void InputFrame::displayAmpName(const QString &ampName) {
  ui.lcdDisplay->setAmpName(ampName);
}

void InputFrame::on_cleanSensDial_valueChanged(double value) {
  if (mpInput != nullptr)
    mpInput->applyCleanSense(value);
}

void InputFrame::on_distortionSensDial_valueChanged(double value) {
  if (mpInput != nullptr)
    mpInput->applyDistortionSense(value);
}

void InputFrame::on_inputSourceDial_valueChanged(int valueIndex) {
  globalObj.applyInputSource(valueIndex);
}

void InputFrame::on_reampSensDial_valueChanged(double value) {
  globalObj.applyReampSense(value);
}

void InputFrame::OnCleanSens(double value) {
  ui.cleanSensDial->setValue(value);
  update();
}

void InputFrame::OnDistortionSens(double value) {
  ui.distortionSensDial->setValue(value);
  update();
}

void InputFrame::OnInputSource(int valueIndex) {
  ui.inputSourceDial->setValue(valueIndex);
  update();
}

void InputFrame::OnReampSens(double value) {
  ui.reampSensDial->setValue(value);
}
