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
#include "SpaceFrame.h"
#include "LookUpTables.h"
#include "Stomp.h"

SpaceFrame::SpaceFrame(QWidget *parent) : QWidget(parent) { ui.setupUi(this); }

SpaceFrame::~SpaceFrame() {}

void SpaceFrame::activate(QObject &stomp) {
  show();
  mpStomp = qobject_cast<Stomp *>(&stomp);

  if (mpStomp != nullptr) {
    connect(mpStomp, &Stomp::intensityReceived, this, &SpaceFrame::onIntensity);

    mpStomp->requestIntensity();

    ui.lcdDisplay->setStompInstance(
        LookUpTables::stompInstanceName(mpStomp->getInstance()));
    ui.lcdDisplay->setStompName(
        LookUpTables::stompFXName(mpStomp->getFXType()));
  }
}

void SpaceFrame::deactivate() {
  if (mpStomp != nullptr) {
    disconnect(mpStomp, &Stomp::intensityReceived, this,
               &SpaceFrame::onIntensity);
    mpStomp = nullptr;
  }
}

QToasterLCD::Page SpaceFrame::getMaxDisplayPage() {
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page SpaceFrame::getCurrentDisplayPage() {
  return ui.lcdDisplay->currentPage();
}

void SpaceFrame::setCurrentDisplayPage(QToasterLCD::Page page) {
  if (page <= ui.lcdDisplay->maxPage()) {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void SpaceFrame::displayStompType(StompInstance stompInstance, FXType fxType) {
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void SpaceFrame::displayStompEnabled(StompInstance stompInstance,
                                     bool enabled) {
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void SpaceFrame::displayDelayEnabled(bool enabled) {
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void SpaceFrame::displayReverbEnabled(bool enabled) {
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void SpaceFrame::displayAmpName(const QString &ampName) {
  ui.lcdDisplay->setAmpName(ampName);
}

void SpaceFrame::on_intensityDial_valueChanged(double value) {
  if (mpStomp != nullptr)
    mpStomp->applyIntensity(value * 10.0);
}

void SpaceFrame::onIntensity(double value) {
  ui.intensityDial->setValue(value / 10.0);
  update();
}
