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
#include "WahPedalBoosterFrame.h"
#include "LookUpTables.h"
#include "Stomp.h"

WahPedalBoosterFrame::WahPedalBoosterFrame(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
}

WahPedalBoosterFrame::~WahPedalBoosterFrame() {}

void WahPedalBoosterFrame::activate(QObject &stomp) {
  show();
  mpStomp = qobject_cast<Stomp *>(&stomp);

  if (mpStomp != nullptr) {
    connect(mpStomp, &Stomp::volumeReceived, this,
            &WahPedalBoosterFrame::onVolume);
    connect(mpStomp, &Stomp::wahRangeReceived, this,
            &WahPedalBoosterFrame::onPedalRange);

    mpStomp->requestVolume();
    mpStomp->requestWahRange();

    ui.lcdDisplay->setStompInstance(
        LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(
        LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void WahPedalBoosterFrame::deactivate() {
  if (mpStomp != nullptr) {
    disconnect(mpStomp, &Stomp::volumeReceived, this,
               &WahPedalBoosterFrame::onVolume);
    disconnect(mpStomp, &Stomp::wahRangeReceived, this,
               &WahPedalBoosterFrame::onPedalRange);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page WahPedalBoosterFrame::getMaxDisplayPage() {
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page WahPedalBoosterFrame::getCurrentDisplayPage() {
  return ui.lcdDisplay->currentPage();
}

void WahPedalBoosterFrame::setCurrentDisplayPage(QToasterLCD::Page page) {
  if (page <= ui.lcdDisplay->maxPage()) {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void WahPedalBoosterFrame::displayStompType(StompInstance stompInstance,
                                            FXType fxType) {
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void WahPedalBoosterFrame::displayStompEnabled(StompInstance stompInstance,
                                               bool enabled) {
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void WahPedalBoosterFrame::displayDelayEnabled(bool enabled) {
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void WahPedalBoosterFrame::displayReverbEnabled(bool enabled) {
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void WahPedalBoosterFrame::displayAmpName(const QString &ampName) {
  ui.lcdDisplay->setAmpName(ampName);
}

void WahPedalBoosterFrame::on_volumeDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void WahPedalBoosterFrame::on_pedalRangeDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyWahRange(value);
}

void WahPedalBoosterFrame::onVolume(double value) {
  ui.volumeDial->setValue(value);
  update();
}

void WahPedalBoosterFrame::onPedalRange(double value) {
  ui.pedalRangeDial->setValue(value);
  update();
}
