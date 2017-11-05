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
#include "WahNoPeakFrame.h"
#include "LookUpTables.h"
#include "Stomp.h"

WahNoPeakFrame::WahNoPeakFrame(QWidget *parent) : QWidget(parent) {
  ui.setupUi(this);
}

WahNoPeakFrame::~WahNoPeakFrame() {}

void WahNoPeakFrame::activate(QObject &stomp) {
  show();
  mpStomp = qobject_cast<Stomp *>(&stomp);

  if (mpStomp != nullptr) {
    connect(mpStomp, &Stomp::wahManualReceived, this,
            &WahNoPeakFrame::onManual);
    connect(mpStomp, &Stomp::wahRangeReceived, this,
            &WahNoPeakFrame::onPedalRange);
    connect(mpStomp, &Stomp::wahPedalModeReceived, this,
            &WahNoPeakFrame::onPedalMode);
    connect(mpStomp, &Stomp::mixReceived, this, &WahNoPeakFrame::onMix);
    connect(mpStomp, &Stomp::duckingReceived, this, &WahNoPeakFrame::onDucking);
    connect(mpStomp, &Stomp::volumeReceived, this, &WahNoPeakFrame::onVolume);
    connect(mpStomp, &Stomp::wahTouchAttackReceived, this,
            &WahNoPeakFrame::onTouchAttack);
    connect(mpStomp, &Stomp::wahTouchReleaseReceived, this,
            &WahNoPeakFrame::onTouchRelease);
    connect(mpStomp, &Stomp::wahTouchBoostReceived, this,
            &WahNoPeakFrame::onTouchBoost);

    mpStomp->requestWahManual();
    mpStomp->requestWahRange();
    mpStomp->requestWahPedalMode();
    mpStomp->requestMix();
    mpStomp->requestDucking();
    mpStomp->requestVolume();
    mpStomp->requestWahTouchAttack();
    mpStomp->requestWahTouchRelease();
    mpStomp->requestWahTouchBoost();

    ui.lcdDisplay->setStompInstance(
        LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(
        LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void WahNoPeakFrame::deactivate() {
  if (mpStomp != nullptr) {
    disconnect(mpStomp, &Stomp::wahManualReceived, this,
               &WahNoPeakFrame::onManual);
    disconnect(mpStomp, &Stomp::wahRangeReceived, this,
               &WahNoPeakFrame::onPedalRange);
    disconnect(mpStomp, &Stomp::wahPedalModeReceived, this,
               &WahNoPeakFrame::onPedalMode);
    disconnect(mpStomp, &Stomp::mixReceived, this, &WahNoPeakFrame::onMix);
    disconnect(mpStomp, &Stomp::duckingReceived, this,
               &WahNoPeakFrame::onDucking);
    disconnect(mpStomp, &Stomp::volumeReceived, this,
               &WahNoPeakFrame::onVolume);
    disconnect(mpStomp, &Stomp::wahTouchAttackReceived, this,
               &WahNoPeakFrame::onTouchAttack);
    disconnect(mpStomp, &Stomp::wahTouchReleaseReceived, this,
               &WahNoPeakFrame::onTouchRelease);
    disconnect(mpStomp, &Stomp::wahTouchBoostReceived, this,
               &WahNoPeakFrame::onTouchBoost);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page WahNoPeakFrame::getMaxDisplayPage() {
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page WahNoPeakFrame::getCurrentDisplayPage() {
  return ui.lcdDisplay->currentPage();
}

void WahNoPeakFrame::setCurrentDisplayPage(QToasterLCD::Page page) {
  if (page <= ui.lcdDisplay->maxPage()) {
    ui.lcdDisplay->setCurrentPage(page);
    ui.bigDials->setCurrentIndex((int)page);
    ui.smallDials->setCurrentIndex((int)page);
  }
}

void WahNoPeakFrame::displayStompType(StompInstance stompInstance,
                                      FXType fxType) {
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void WahNoPeakFrame::displayStompEnabled(StompInstance stompInstance,
                                         bool enabled) {
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void WahNoPeakFrame::displayDelayEnabled(bool enabled) {
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void WahNoPeakFrame::displayReverbEnabled(bool enabled) {
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void WahNoPeakFrame::displayAmpName(const QString &ampName) {
  ui.lcdDisplay->setAmpName(ampName);
}

void WahNoPeakFrame::on_manualDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyWahManual(value + 5.0);
}

void WahNoPeakFrame::on_pedalRangeDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyWahRange(value);
}

void WahNoPeakFrame::on_pedalModeDial_valueChanged(int valueIndex) {
  if (mpStomp != nullptr)
    mpStomp->applyWahPedalMode((::WahPedalMode)valueIndex);
}

void WahNoPeakFrame::on_mixDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyMix(value);
}

void WahNoPeakFrame::on_duckingDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyDucking(value);
}

void WahNoPeakFrame::on_volumeDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyVolume(value);
}

void WahNoPeakFrame::on_touchAttackDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyWahTouchAttack(value);
}

void WahNoPeakFrame::on_touchReleaseDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyWahTouchRelease(value);
}

void WahNoPeakFrame::on_touchBoostDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyWahTouchBoost(value);
}

void WahNoPeakFrame::onManual(double value) {
  ui.manualDial->setValue(value - 5.0);
  update();
}

void WahNoPeakFrame::onPedalRange(double value) {
  ui.pedalRangeDial->setValue(value);
  update();
}

void WahNoPeakFrame::onPedalMode(WahPedalMode value) {
  ui.pedalModeDial->setValue((int)value);
  update();
}

void WahNoPeakFrame::onMix(double value) {
  ui.mixDial->setValue(value);
  update();
}

void WahNoPeakFrame::onDucking(double value) {
  ui.duckingDial->setValue(value);
  update();
}

void WahNoPeakFrame::onVolume(double value) {
  ui.volumeDial->setValue(value);
  update();
}

void WahNoPeakFrame::onTouchAttack(double value) {
  ui.touchAttackDial->setValue(value);
  update();
}

void WahNoPeakFrame::onTouchRelease(double value) {
  ui.touchReleaseDial->setValue(value);
  update();
}

void WahNoPeakFrame::onTouchBoost(double value) {
  ui.touchBoostDial->setValue(value);
  update();
}
