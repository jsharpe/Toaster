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
#include "Utils.h"
#include "VirtualExtendedParam.h"

VirtualExtendedParam::VirtualExtendedParam(ParamId id, VirtualModule* module)
  : VirtualParam(id, module)
{

}

bool VirtualExtendedParam::load(const ByteArray& buf)
{
  bool rc = false;
  int bufSize = buf.size();

  if(bufSize >= 15)
  {
    int noOfParams = (bufSize - 13) / 5;
    int valStartIdx = 12;
    while(noOfParams)
    {
      unsigned int val = Utils::extractRawVal(ByteArray(buf.begin() + valStartIdx, buf.begin() + valStartIdx + 5));
      valStartIdx += 5;
      mValues.push_back(val);
      noOfParams--;
    }
    rc = true;
  }
  return rc;
}

void VirtualExtendedParam::setValue(const ByteArray& cmd)
{

}

ByteArray VirtualExtendedParam::createResponse(bool includeLen)
{
  ByteArray response;
  if(mModule != nullptr)
  {
    response = createExtParamSetCmd(mId, mValues, includeLen);
  }
  return response;
}

ByteArray VirtualExtendedParam::createResponse(const ByteArray&, bool includeLen)
{
  return createResponse(includeLen);
}
