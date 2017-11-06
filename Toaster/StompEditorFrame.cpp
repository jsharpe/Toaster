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
#include "StompEditorFrame.h"
#include "AirChorusFrame.h"
#include "AmpFrame.h"
#include "AnalogOctaverFrame.h"
#include "CabFrame.h"
#include "ChromaticPitchFrame.h"
#include "CompressorFrame.h"
#include "Delay.h"
#include "DelayFrame.h"
#include "DriveAndToneDSFrame.h"
#include "DriveDSFrame.h"
#include "FlangerFrame.h"
#include "FlangerOnewayFrame.h"
#include "GateFrame.h"
#include "GraphicEqualizerFrame.h"
#include "HarmonicPitchFrame.h"
#include "HyperChorusFrame.h"
#include "Input.h"
#include "InputFrame.h"
#include "LegacyDelayFrame.h"
#include "LoopDistortionFrame.h"
#include "LoopFrame.h"
#include "MetalDSFrame.h"
#include "MetalEqualizerFrame.h"
#include "MicroPitchFrame.h"
#include "OutputFrame.h"
#include "PedalPitchFrame.h"
#include "PedalVinylStopFrame.h"
#include "PhaserFrame.h"
#include "PhaserOnewayFrame.h"
#include "Profile.h"
#include "PureBoosterFrame.h"
#include "RectiShaperFrame.h"
#include "Reverb.h"
#include "ReverbFrame.h"
#include "RotarySpeakerFrame.h"
#include "Settings.h"
#include "SpaceFrame.h"
#include "StereoWidenerFrame.h"
#include "Stomp.h"
#include "StompEditorPage.h"
#include "StudioEqualizerFrame.h"
#include "TapDelayFrame.h"
#include "ToneAndDuckingDSFrame.h"
#include "TransposeFrame.h"
#include "TremoloFrame.h"
#include "VibratoFrame.h"
#include "VintageChorusFrame.h"
#include "WahFormantShiftFrame.h"
#include "WahNoPeakFrame.h"
#include "WahPedalBoosterFrame.h"
#include "WahPhaserFrame.h"
#include "WahWahFrame.h"
#include <QLayout>

StompEditorFrame::StompEditorFrame(QWidget *parent)
    : QWidget(parent), mpActiveStomp(nullptr), mActiveStompType(-1),
      mpActivePage(nullptr) {
  ui.setupUi(this);
}

StompEditorFrame::~StompEditorFrame() {}

void StompEditorFrame::init(KemperStompState &stompState) {
  this->stompState = &stompState;
  // stomps
  connect(&stompState.stompA, &Stomp::onOffReceived, this,
          &StompEditorFrame::onStompAOnOff);
  connect(&stompState.stompB, &Stomp::onOffReceived, this,
          &StompEditorFrame::onStompBOnOff);
  connect(&stompState.stompC, &Stomp::onOffReceived, this,
          &StompEditorFrame::onStompCOnOff);
  connect(&stompState.stompD, &Stomp::onOffReceived, this,
          &StompEditorFrame::onStompDOnOff);
  connect(&stompState.stompX, &Stomp::onOffReceived, this,
          &StompEditorFrame::onStompXOnOff);
  connect(&stompState.stompMod, &Stomp::onOffReceived, this,
          &StompEditorFrame::onStompModOnOff);
  connect(&stompState.stompA, &Stomp::typeReceived, this,
          &StompEditorFrame::onStompAType);
  connect(&stompState.stompB, &Stomp::typeReceived, this,
          &StompEditorFrame::onStompBType);
  connect(&stompState.stompC, &Stomp::typeReceived, this,
          &StompEditorFrame::onStompCType);
  connect(&stompState.stompD, &Stomp::typeReceived, this,
          &StompEditorFrame::onStompDType);
  connect(&stompState.stompX, &Stomp::typeReceived, this,
          &StompEditorFrame::onStompXType);
  connect(&stompState.stompMod, &Stomp::typeReceived, this,
          &StompEditorFrame::onStompModType);
  // delay
  connect(&stompState.stompDelay, &Stomp::onOffReceived, this,
          &StompEditorFrame::onDelayOnOff);
  connect(&stompState.stompDelay, &Stomp::typeReceived, this,
          &StompEditorFrame::onStompDelayType);

  // reverb
  connect(&reverbObj, &Reverb::onOffCutsTailReceived, this,
          &StompEditorFrame::onReverbOnOff);
}

void StompEditorFrame::activate(QObject &stomp) {
  deactivate();
  mpActiveStomp = &stomp;

  if (mpActiveStomp != nullptr) {
    Stomp *pActiveStomp = qobject_cast<Stomp *>(mpActiveStomp);
    Reverb *pReverb = qobject_cast<Reverb *>(mpActiveStomp);
    Amp *pAmp = qobject_cast<Amp *>(mpActiveStomp);
    Cab *pCab = qobject_cast<Cab *>(mpActiveStomp);
    Global *pGlobal = qobject_cast<Global *>(mpActiveStomp);
    Input *pInput = qobject_cast<Input *>(mpActiveStomp);
    if (pActiveStomp != nullptr) {
      connect(pActiveStomp, SIGNAL(typeReceived(::FXType)), this,
              SLOT(onActiveStompType(::FXType)));
      onActiveStompType(pActiveStomp->getFXType());
      pActiveStomp->requestType();
    } else if (pReverb != nullptr) {
      connect(pReverb, SIGNAL(typeReceived(::ReverbType)), this,
              SLOT(onReverbType(::ReverbType)));
      onReverbType(pReverb->getReverbType());
      pReverb->requestType();
    } else if (pAmp != nullptr) {
      activatePage(std::unique_ptr<AmpFrame>(new AmpFrame(this)));
    } else if (pCab != nullptr) {
      activatePage(std::unique_ptr<CabFrame>(new CabFrame(this)));
    } else if (pGlobal != nullptr) {
      activatePage(std::unique_ptr<OutputFrame>(new OutputFrame(this)));
    } else if (pInput != nullptr) {
      activatePage(std::unique_ptr<InputFrame>(new InputFrame(this)));
    }
  }
}

void StompEditorFrame::deactivate() {
  if (mpActiveStomp != nullptr) {
    Stomp *pActiveStomp = qobject_cast<Stomp *>(mpActiveStomp);
    Delay *pDelay = qobject_cast<Delay *>(mpActiveStomp);
    Reverb *pReverb = qobject_cast<Reverb *>(mpActiveStomp);

    if (pActiveStomp != nullptr)
      disconnect(mpActiveStomp, SIGNAL(typeReceived(::FXType)), this,
                 SLOT(onActiveStompType(::FXType)));
    else if (pReverb != nullptr)
      connect(pReverb, SIGNAL(typeReceived(::ReverbType)), this,
              SLOT(onReverbType(::ReverbType)));

    mpActiveStomp = nullptr;
  }

  mActiveStompType = -1;

  if (mpActivePage != nullptr) {
    mpActivePage->deactivate();
    ui.dummyStompFrame->show();
    mpActivePage.reset();
    emit editorPageChanged(mpActivePage.get());
    requestValues();
  }
}

void StompEditorFrame::onActiveStompType(FXType fxType) {
  Stomp *pActiveStomp = nullptr;
  if (mpActivePage != nullptr) {
    // on rig change, while editor is active
    if (fxType != mActiveStompType) {
      mpActivePage->deactivate();
      mpActivePage.reset();
      emit editorPageChanged(mpActivePage.get());
      requestValues();
    }
  }

  pActiveStomp = qobject_cast<Stomp *>(mpActiveStomp);

  if (mpActivePage == nullptr) {
    switch (fxType) {
    case WahWah:
    case WahHighPass:
    case WahLowPass:
    case WahVowelFilter:
    case WahFlanger:
    case WahRateReducer:
      mpActivePage.reset(new WahWahFrame(this));
      break;
    case WahRingModulator:
    case WahFrequencyShifter:
      mpActivePage.reset(new WahNoPeakFrame(this));
      break;
    case WahFormantShifter:
      mpActivePage.reset(new WahFormantShiftFrame(this));
      break;
    case WahPhaser:
      mpActivePage.reset(new WahPhaserFrame(this));
      break;
    case PureBooster:
      mpActivePage.reset(new PureBoosterFrame(this));
      break;
    case SoftShaper:
    case HardShaper:
    case WaveShaper:
    case PlusDS:
    case FuzzDS:
      mpActivePage.reset(new DriveDSFrame(this));
      break;
    case BitShaper:
    case GreenScream:
    case OneDS:
    case Muffin:
    case MouseDS:
      mpActivePage.reset(new DriveAndToneDSFrame(this));
      break;
    case RectiShaper:
      mpActivePage.reset(new RectiShaperFrame(this));
      break;
    case TrebleBooster:
    case LeadBooster:
      mpActivePage.reset(new ToneAndDuckingDSFrame(this));
      break;
    case WahPedalBooster:
      mpActivePage.reset(new WahPedalBoosterFrame(this));
      break;
    case MetalDS:
      mpActivePage.reset(new MetalDSFrame(this));
      break;
    case GraphicEqualizer:
      mpActivePage.reset(new GraphicEqualizerFrame(this));
      break;
    case StudioEqualizer:
      mpActivePage.reset(new StudioEqualizerFrame(this));
      break;
    case MetalEqualizer:
      mpActivePage.reset(new MetalEqualizerFrame(this));
      break;
    case StereoWidener:
      mpActivePage.reset(new StereoWidenerFrame(this));
      break;
    case Compressor:
      mpActivePage.reset(new CompressorFrame(this));
      break;
    case NoiseGate21:
    case NoiseGate41:
      mpActivePage.reset(new GateFrame(this));
      break;
    case VintageChorus:
      mpActivePage.reset(new VintageChorusFrame(this));
      break;
    case HyperChorus:
      mpActivePage.reset(new HyperChorusFrame(this));
      break;
    case AirChorus:
      mpActivePage.reset(new AirChorusFrame(this));
      break;
    case MicroPitch:
      mpActivePage.reset(new MicroPitchFrame(this));
      break;
    case Vibrato:
      mpActivePage.reset(new VibratoFrame(this));
      break;
    case RotarySpeaker:
      mpActivePage.reset(new RotarySpeakerFrame(this));
      break;
    case Tremolo:
      mpActivePage.reset(new TremoloFrame(this));
      break;
    case Phaser:
    case PhaserVibe:
      mpActivePage.reset(new PhaserFrame(this));
      break;
    case PhaserOneway:
      mpActivePage.reset(new PhaserOnewayFrame(this));
      break;
    case Flanger:
      mpActivePage.reset(new FlangerFrame(this));
      break;
    case FlangerOneway:
      mpActivePage.reset(new FlangerOnewayFrame(this));
      break;
    case Space:
      mpActivePage.reset(new SpaceFrame(this));
      break;
    case Transpose:
      mpActivePage.reset(new TransposeFrame(this));
      break;
    case PedalPitch:
      mpActivePage.reset(new PedalPitchFrame(this));
      break;
    case PedalVinylStop:
      mpActivePage.reset(new PedalVinylStopFrame(this));
      break;
    case ChromaticPitch:
      mpActivePage.reset(new ChromaticPitchFrame(this));
      break;
    case HarmonicPitch:
      mpActivePage.reset(new HarmonicPitchFrame(this));
      break;
    case AnalogOctaver:
      mpActivePage.reset(new AnalogOctaverFrame(this));
      break;
    case LoopMono:
    case LoopStereo:
      mpActivePage.reset(new LoopFrame(this));
      break;
    case LoopDistortion:
      mpActivePage.reset(new LoopDistortionFrame(this));
      break;
    case LegacyDelay:
      mpActivePage.reset(new LegacyDelayFrame(this));
      break;
    case SingleDelay:
    case DualDelay:
    case TwoTapDelay:
    case SerialTwoTapDelay:
    case RhythmDelay:
    case QuadDelay:
    case CrystalDelay:
    case LoopPitchDelay:
    case FrequencyShifterDelay:
    case DualChromaticDelay:
    case DualHarmonicDelay:
    case DualCrystalDelay:
    case DualLoopPitchDelay:
    case MelodyDelay:
    case QuadChromaticDelay:
    case QuadHarmonicDelay:
    case DualCrystal:
    case None:
      ui.dummyStompFrame->show();
      break;
    }

    if (mpActivePage != nullptr && !mpActivePage->isActive()) {
      setUpdatesEnabled(false);
      mActiveStompType = fxType;
      ui.dummyStompFrame->hide();
      mpActivePage->activate(*pActiveStomp);
      setUpdatesEnabled(true);
      emit editorPageChanged(mpActivePage.get());
      requestValues();
    }
  }
}

void StompEditorFrame::onReverbType(::ReverbType reverbType) {
  Reverb *pActiveReverb = nullptr;
  if (mpActivePage != nullptr) {
    if (reverbType != mActiveStompType) {
      mpActivePage->deactivate();
      mpActivePage.reset();
      emit editorPageChanged(mpActivePage.get());
      requestValues();
    }
  }

  pActiveReverb = qobject_cast<Reverb *>(mpActiveStomp);

  if (mpActivePage == nullptr && pActiveReverb != nullptr) {
    switch (reverbType) {
    case Hall:
    case LargeRoom:
    case SmallRoom:
    case Ambience:
    case Matchbox:
      mpActivePage.reset(new ReverbFrame(this));
      break;
    default:
      ui.dummyStompFrame->show();
      break;
    }

    if (mpActivePage != nullptr && !mpActivePage->isActive()) {
      setUpdatesEnabled(false);
      mActiveStompType = reverbType;
      mpActivePage->activate(*pActiveReverb);
      ui.dummyStompFrame->hide();
      setUpdatesEnabled(true);
      emit editorPageChanged(mpActivePage.get());
      requestValues();
    }
  }
}

void StompEditorFrame::onStompAOnOff(bool onOff) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompA, onOff);
}

void StompEditorFrame::onStompBOnOff(bool onOff) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompB, onOff);
}

void StompEditorFrame::onStompCOnOff(bool onOff) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompC, onOff);
}

void StompEditorFrame::onStompDOnOff(bool onOff) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompD, onOff);
}

void StompEditorFrame::onStompXOnOff(bool onOff) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompX, onOff);
}

void StompEditorFrame::onStompModOnOff(bool onOff) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompEnabled(StompMod, onOff);
}

void StompEditorFrame::onStompAType(::FXType type) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompType(StompA, type);
}

void StompEditorFrame::onStompBType(::FXType type) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompType(StompB, type);
}

void StompEditorFrame::onStompCType(::FXType type) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompType(StompC, type);
}

void StompEditorFrame::onStompDType(::FXType type) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompType(StompD, type);
}

void StompEditorFrame::onStompXType(::FXType type) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompType(StompX, type);
}

void StompEditorFrame::onStompModType(::FXType type) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompType(StompMod, type);
}

void StompEditorFrame::onStompDelayType(::FXType type) {
  if (mpActivePage != nullptr)
    mpActivePage->displayStompType(StompDelay, type);
}

// delay
// kpa => ui
void StompEditorFrame::onDelayOnOff(bool onOff) {
  if (mpActivePage != nullptr)
    mpActivePage->displayDelayEnabled(onOff);
}
//------------------------------------------------------------------------------------------

// reverb
// kpa => ui
void StompEditorFrame::onReverbOnOff(bool onOff) {
  if (mpActivePage != nullptr)
    mpActivePage->displayReverbEnabled(onOff);
}
//------------------------------------------------------------------------------------------

void StompEditorFrame::nextDisplayPage() {
  if (mpActivePage != nullptr) {
    QToasterLCD::Page maxPage = mpActivePage->getMaxDisplayPage();
    QToasterLCD::Page currentPage = mpActivePage->getCurrentDisplayPage();
    QToasterLCD::Page pageToSet = currentPage;

    if (currentPage < maxPage)
      pageToSet = (QToasterLCD::Page)(currentPage + 1);

    if (pageToSet != currentPage) {
      mpActivePage->setCurrentDisplayPage(pageToSet);
      emit editorPageChanged(mpActivePage.get());
      requestValues();
    }
  }
}

void StompEditorFrame::prevDisplayPage() {
  if (mpActivePage != nullptr) {
    QToasterLCD::Page currentPage = mpActivePage->getCurrentDisplayPage();
    QToasterLCD::Page pageToSet = currentPage;
    if (currentPage > QToasterLCD::Page1)
      pageToSet = (QToasterLCD::Page)(currentPage - 1);

    if (pageToSet != currentPage) {
      mpActivePage->setCurrentDisplayPage(pageToSet);
      emit editorPageChanged(mpActivePage.get());
      requestValues();
    }
  }
}

void StompEditorFrame::requestValues() {
  stompState->requestAllValues();
  reverbObj.requestOnOffCutsTail();
}

void StompEditorFrame::activatePage(std::unique_ptr<IStompEditorPage> page) {
  mpActivePage = std::move(page);
  if (mpActivePage != nullptr && !mpActivePage->isActive()) {
    setUpdatesEnabled(false);
    mpActivePage->activate(*mpActiveStomp);
    ui.dummyStompFrame->hide();
    setUpdatesEnabled(true);
    emit editorPageChanged(mpActivePage.get());
    requestValues();
  }
}
