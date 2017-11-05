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
#include "DelayFrame.h"
#include "LookUpTables.h"

DelayFrame::DelayFrame(QWidget *parent)
  : QWidget(parent)
{
  ui.setupUi(this);
}

DelayFrame::~DelayFrame()
{
}

void DelayFrame::activate(QObject& stomp)
{
  mpDelay = qobject_cast<Delay*>(&stomp);
  if(mpDelay != nullptr)
  {
    connect(mpDelay, &Delay::bandwidthReceived, this, &DelayFrame::onBandwidth);
    connect(mpDelay, &Delay::centerFrequencyReceived, this, &DelayFrame::onCenterFrequency);
    connect(mpDelay, &Delay::modulationReceived, this, &DelayFrame::onModulation);
    connect(mpDelay, &Delay::duckingReceived, this, &DelayFrame::onDucking);
    connect(mpDelay, &Delay::timeReceived, this, &DelayFrame::onTime);
    connect(mpDelay, &Delay::ratioReceived, this, &DelayFrame::onRatio);
    connect(mpDelay, &Delay::volumeReceived, this, &DelayFrame::onVolume);

    mpDelay->requestBandwidth();
    mpDelay->requestCenterFrequency();
    mpDelay->requestModulation();
    mpDelay->requestDucking();
    mpDelay->requestTime();
    mpDelay->requestRatio();
    mpDelay->requestVolume();

    ui.lcdDisplay->setStompInstance("Delay Effect");
    ui.lcdDisplay->setStompName(LookUpTables::stompFXName(mpDelay->getDelayType()));
  }
}

void DelayFrame::deactivate()
{
  if(mpDelay != nullptr)
  {
    disconnect(mpDelay, &Delay::bandwidthReceived, this, &DelayFrame::onBandwidth);
    disconnect(mpDelay, &Delay::centerFrequencyReceived, this, &DelayFrame::onCenterFrequency);
    disconnect(mpDelay, &Delay::modulationReceived, this, &DelayFrame::onModulation);
    disconnect(mpDelay, &Delay::duckingReceived, this, &DelayFrame::onDucking);
    disconnect(mpDelay, &Delay::timeReceived, this, &DelayFrame::onTime);
    disconnect(mpDelay, &Delay::ratioReceived, this, &DelayFrame::onRatio);
    disconnect(mpDelay, &Delay::volumeReceived, this, &DelayFrame::onVolume);
    mpDelay = nullptr;
  }
}

QToasterLCD::Page DelayFrame::getMaxDisplayPage()
{
  return ui.lcdDisplay->maxPage();
}

QToasterLCD::Page DelayFrame::getCurrentDisplayPage()
{
  return ui.lcdDisplay->currentPage();
}

void DelayFrame::setCurrentDisplayPage(QToasterLCD::Page page)
{
  if(page <= ui.lcdDisplay->maxPage())
  {
    ui.lcdDisplay->setCurrentPage(page);
  }
}

void DelayFrame::displayStompType(StompInstance stompInstance, FXType fxType)
{
  ui.lcdDisplay->setStompFXType(stompInstance, fxType);
}

void DelayFrame::displayStompEnabled(StompInstance stompInstance, bool enabled)
{
  ui.lcdDisplay->setStompEnabled(stompInstance, enabled);
}

void DelayFrame::displayDelayEnabled(bool enabled)
{
  ui.lcdDisplay->setDelayEnabled(enabled);
}

void DelayFrame::displayReverbEnabled(bool enabled)
{
  ui.lcdDisplay->setReverbEnabled(enabled);
}

void DelayFrame::displayAmpName(const QString&  ampName)
{
  ui.lcdDisplay->setAmpName(ampName);
}

void DelayFrame::on_bandwidthDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyBandwidth(value);
}

void DelayFrame::on_centerFrequencyDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyCenterFrequency(value);
}

void DelayFrame::on_modulationDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyModulation(value);
}

void DelayFrame::on_duckingDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyDucking(value);
}

void DelayFrame::on_timeDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyTime(value);
}

void DelayFrame::on_ratioDial_valueChanged(int valueIndex)
{
  if(mpDelay != nullptr)
    mpDelay->applyRatio((::DelayRatio)valueIndex);
}

void DelayFrame::on_volumeDial_valueChanged(double value)
{
  if(mpDelay != nullptr)
    mpDelay->applyVolume(value);
}

void DelayFrame::onBandwidth(double value)
{
  ui.bandwidthDial->setValue(value);
  update();
}

void DelayFrame::onCenterFrequency(double value)
{
  ui.centerFrequencyDial->setValue(value);
  update();
}

void DelayFrame::onModulation(double value)
{
  ui.modulationDial->setValue(value);
  update();
}

void DelayFrame::onDucking(double value)
{
  ui.duckingDial->setValue(value);
  update();
}

void DelayFrame::onTime(double value)
{
  ui.timeDial->setValue(value);
  update();
}

void DelayFrame::onRatio(::DelayRatio ratio)
{
  ui.ratioDial->setValue((int)ratio);
  update();
}

void DelayFrame::onVolume(double value)
{
  ui.volumeDial->setValue(value);
  update();
}
