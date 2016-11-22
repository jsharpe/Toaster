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
#include "VirtualSingleParam.h"

VirtualSingleParam::VirtualSingleParam(ParamId id, VirtualModule* module)
  : VirtualParam(id, module)
{

}


bool VirtualSingleParam::load(const ByteArray& buf)
{
  bool rc = true;

  return rc;
}

void VirtualSingleParam::setValue(const ByteArray& cmd)
{

}

ByteArray VirtualSingleParam::createResponse(bool includeLen)
{
  ByteArray response;
  if(mModule != nullptr)
  {
  }
  return response;
}

ByteArray VirtualSingleParam::createResponse(const ByteArray&, bool includeLen)
{
  return createResponse(includeLen);
}