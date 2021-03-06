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
#include "PedalVinylStopFrame.h"
#include "Global.h"
#include "LookUpTables.h"
#include "Stomp.h"

PedalVinylStopFrame::PedalVinylStopFrame(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
}

PedalVinylStopFrame::~PedalVinylStopFrame() {}

void PedalVinylStopFrame::activate(QObject &stomp) {
  show();
  mpStomp = qobject_cast<Stomp *>(&stomp);

  if (mpStomp != nullptr) {
    connect(mpStomp, &Stomp::volumeReceived, this,
            &PedalVinylStopFrame::onVolume);
    connect(mpStomp, &Stomp::mixReceived, this, &PedalVinylStopFrame::onMix);
    connect(&globalObj, &Global::wahPedalToPitchReceived, this,
            &PedalVinylStopFrame::onWahPedalToPitch);

    mpStomp->requestVolume();
    mpStomp->requestMix();
    globalObj.requestWahPedalToPitch();

    ui.lcdDisplay->setStompInstance(
        LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(
        LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void PedalVinylStopFrame::deactivate() {
  if (mpStomp != nullptr) {
    disconnect(mpStomp, &Stomp::volumeReceived, this,
               &PedalVinylStopFrame::onVolume);
    disconnect(mpStomp, &Stomp::mixReceived, this, &PedalVinylStopFrame::onMix);
    mpStomp = nullptr;
  }

  disconnect(&globalObj, &Global::wahPedalToPitchReceived, this,
             &PedalVinylStopFrame::onWahPedalToPitch);
}

QToasterLCD::Page PedalVinylStopFrame::getMaxDisplayPage() {
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page PedalVinylStopFrame::getCurrentDisplayPage() {
  return ui.lcdDisplay->currentPage();
}

void PedalVinylStopFrame::setCurrentDisplayPage(QToasterLCD::Page page) {
  if (page <= ui.lcdDisplay->maxPage()) {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void PedalVinylStopFrame::displayStompType(StompInstance stompInstance,
                                           FXType fxType) {
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void PedalVinylStopFrame::displayStompEnabled(StompInstance stompInstance,
                                              bool enabled) {
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void PedalVinylStopFrame::displayDelayEnabled(bool enabled) {
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void PedalVinylStopFrame::displayReverbEnabled(bool enabled) {
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void PedalVinylStopFrame::displayAmpName(const QString &ampName) {
  ui.lcdDisplay->setAmpName(ampName);
}

void PedalVinylStopFrame::on_volumeDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void PedalVinylStopFrame::on_mixDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void PedalVinylStopFrame::on_wahPedalToPitchDial_valueChanged(int valueIndex) {
  if (mpStomp != nullptr)
    globalObj.applyWahPedalToPitch(valueIndex != 0);
}

void PedalVinylStopFrame::onVolume(double value) {
  ui.volumeDial->setValue(value);
  update();
}

void PedalVinylStopFrame::onMix(double value) {
  ui.mixDial->setValue(value);
  update();
}

void PedalVinylStopFrame::onWahPedalToPitch(bool onOff) {
  ui.wahPedalToPitchDial->setValue(onOff ? 1 : 0);
  update();
}
