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
#include "DelayCtxMenu.h"
#include "Delay.h"
#include "Commons.h"
#include "Settings.h"

#include <vector>

DelayCtxMenu::DelayCtxMenu(Delay& delay)
  : mDelay(delay)
{
}

void createDelayMenu(QMenu & menu)
{
    struct DelayNames {
        QString name;
        FXType type;
    };

    std::vector<DelayNames> delays = {
        DelayNames { "Legacy Delay", LegacyDelay },
        DelayNames { "Single Delay", SingleDelay},
        DelayNames { "Dual Delay", DualDelay},
        DelayNames { "Two Tap Delay", TwoTapDelay},
        DelayNames { "Serial Two Tap Delay", SerialTwoTapDelay},
        DelayNames { "Rhythm Delay", RhythmDelay},
        DelayNames { "Quad Delay", QuadDelay},
        DelayNames { "Dual Crystal", DualCrystal},
        DelayNames { "Crystal Delay", CrystalDelay},
        DelayNames { "Loop Pitch Delay", LoopPitchDelay},
        DelayNames { "Frequency Shifter Delay", FrequencyShifterDelay},
        DelayNames { "Dual Chromatic Delay", DualChromaticDelay},
        DelayNames { "Dual Harmonic Delay", DualHarmonicDelay},
        DelayNames { "Dual Crystal Delay", DualCrystalDelay},
        DelayNames { "Dual Loop Pitch Delay", DualLoopPitchDelay},
        DelayNames { "Melody Delay", MelodyDelay},
        DelayNames { "Quad Chromatic Delay", QuadChromaticDelay},
        DelayNames { "Quad Harmonic Delay", QuadHarmonicDelay},
        DelayNames { "Crystal Delay", CrystalDelay },
    };

    for (auto delay: delays) {
      menu.addAction(delay.name)
          ->setData(QVariant((unsigned int)delay.type));
    }
}

void DelayCtxMenu::createMenu(QMenu& menu)
{
  connect(&menu, SIGNAL(triggered(QAction*)), this, SLOT(setType(QAction*)));

  if(Settings::get().getKPAOSVersion() >= 0x04000000)
  {
     createDelayMenu(menu);
  }
}

void DelayCtxMenu::setType(QAction* action)
{
  FXType delayType = (FXType)action->data().toUInt();
  mDelay.applyType(delayType);
}

