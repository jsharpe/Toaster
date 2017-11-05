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
#include "Tuner.h"
#include "LookUpTables.h"

Tuner::Tuner() {}

Tuner::~Tuner() {}

Tuner &Tuner::get() {
  static Tuner tuner;
  return tuner;
}

void Tuner::midiNoteReceived(unsigned short rawVal) {
  emit noteReceived(LookUpTables::raw2Note(rawVal), Utils::raw2Octave(rawVal));
}

void Tuner::midiMuteSignalReceived(unsigned short rawVal) {
  emit muteSignalReceived(rawVal != 0);
}
