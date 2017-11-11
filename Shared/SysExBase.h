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
#ifndef SYSEXBASE_H
#define SYSEXBASE_H
#include "Utils.h"
#include <QString>

class SysExBase {
public:
  SysExBase() = default;

  // sysex header & base struct
  static const ByteArray &Header() {
    static ByteArray header = {0xF0, 0x00, 0x20, 0x33,
                               0x02, 0x7F}; // syx: 0x0F; manufacturerID:
                                            // 0x00,0x20,0x33; productType:
                                            // 0x02; deviceID: 0x7F
    return header;
  }

  static const ByteArray Header(unsigned short len) {
    static ByteArray id = {0x00, 0x20, 0x33, 0x00, 0x02};
    ByteArray res = {0xF0};

    if (len < 128) {
      res.push_back((ByteArray::value_type)len);
    } else {
      ByteArray rawVal = Utils::packRawVal(len);
      rawVal[0] = rawVal[0] | 0x80;
      res.push_back(rawVal[0]);
    }
    for (auto v : id)
      res.push_back(v);

    return res;
  }

  static ByteArray::value_type Eox() { return 0xF7; }

  // function codes (with instance)
  static const ByteArray &SingleParamChange() {
    static ByteArray singleParamChange = {0x01, 0x00};
    return singleParamChange;
  }

  static const ByteArray &MultiParamChange() {
    static ByteArray multiParamChange = {0x02, 0x00};
    return multiParamChange;
  }

  static const ByteArray &StringParam() {
    static ByteArray stringParam = {0x03, 0x00};
    return stringParam;
  }

  static const ByteArray &Blob() {
    static ByteArray blob = {0x04, 0x00};
    return blob;
  }

  static const ByteArray &ExtParamChange() {
    static ByteArray extParamChange = {0x06, 0x00};
    return extParamChange;
  }

  static const ByteArray &ExtStringParamChange() {
    static ByteArray extStringParamChange = {0x07, 0x00};
    return extStringParamChange;
  }

  static const ByteArray &ReqSingleParamVal() {
    static ByteArray reqSingleParamVal = {0x41, 0x00};
    return reqSingleParamVal;
  }

  static const ByteArray &ReqMultiParamVals() {
    static ByteArray reqMultiParamVals = {0x42, 0x00};
    return reqMultiParamVals;
  }

  static const ByteArray &ReqStringParam() {
    static ByteArray reqStringParam = {0x43, 0x00};
    return reqStringParam;
  }

  static const ByteArray &ReqBlobParam() {
    static ByteArray reqBlobParam = {0x44, 0x00};
    return reqBlobParam;
  }

  static const ByteArray &ReqExtParam() {
    static ByteArray reqExtParam = {0x46, 0x00};
    return reqExtParam;
  }

  static const ByteArray &ReqExtStringParam() {
    static ByteArray reqExtStringParam = {0x47, 0x00};
    return reqExtStringParam;
  }

  static const ByteArray &ReqParamAsString() {
    static ByteArray reqParamAsString = {0x7C, 0x00};
    return reqParamAsString;
  }

  // these two functions are marked as reserved in the public midi spec
  static const ByteArray &ReservedFct7E() {
    static ByteArray reservedFct7E = {0x7E, 0x00};
    return reservedFct7E;
  }

  static const ByteArray &ReservedFct7F() {
    static ByteArray reservedFct7F = {0x7F, 0x00};
    return reservedFct7F;
  }

  //===========================================================================================================================
  // single parameter 0x01
  ByteArray createSingleParamGetCmd(const ByteArray &addressPage,
                                    const ByteArray &param) {
    ByteArray res = Header();
    for (auto v : ReqSingleParamVal())
      res.push_back(v);
    for (auto v : addressPage)
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  ByteArray createSingleParamSetCmd(const ByteArray &addressPage,
                                    const ByteArray &param,
                                    const ByteArray &val,
                                    bool includeLen = false) {
    ByteArray res = includeLen ? Header(val.size() + 10) : Header();
    for (auto v : SingleParamChange())
      res.push_back(v);
    for (auto v : addressPage)
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    for (auto v : val)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  ByteArray createSingleParamSetCmd(const ByteArray &addressPage,
                                    const ByteArray &param,
                                    unsigned short rawVal,
                                    bool includeLen = false) {
    return createSingleParamSetCmd(addressPage, param,
                                   Utils::packRawVal(rawVal), includeLen);
  }

  //===========================================================================================================================
  // multiparameter 0x02
  static ByteArray createMultiParamGetCmd(const ByteArray &addressPage,
                                          unsigned char startParam) {
    ByteArray res = Header();
    for (auto v : ReqMultiParamVals())
      res.push_back(v);
    for (auto v : addressPage)
      res.push_back(v);
    res.push_back(0x00);
    res.push_back(Eox());
    return res;
  }

  ByteArray createMultiParamSetCmd(const ByteArray &addressPage,
                                   const ByteArray &startParam,
                                   const std::vector<unsigned short> &vals,
                                   bool includeLen = false) {
    ByteArray rawVals;
    for (unsigned short val : vals) {
      ByteArray rawVal = Utils::packRawVal(val);
      for (auto v : rawVal)
        rawVals.push_back(v);
    }

    return createMultiParamSetCmd(addressPage, startParam, rawVals, includeLen);
  }

  ByteArray createMultiParamSetCmd(const ByteArray &addressPage,
                                   const ByteArray &startParam,
                                   const ByteArray &vals,
                                   bool includeLen = false) {
    ByteArray res = includeLen ? Header(vals.size() + 10) : Header();
    for (auto v : MultiParamChange())
      res.push_back(v);
    for (auto v : addressPage)
      res.push_back(v);
    for (auto v : startParam)
      res.push_back(v);
    for (auto v : vals)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  //===========================================================================================================================
  // string parameter 0x03
  ByteArray createStringParamGetCmd(const ByteArray &addressPage,
                                    const ByteArray &param) {
    ByteArray res = Header();
    for (auto val : ReqStringParam())
      res.push_back(val);
    for (auto val : addressPage)
      res.push_back(val);
    for (auto val : param)
      res.push_back(val);
    res.push_back(Eox());
    return res;
  }

  ByteArray createStringParamSetCmd(const ByteArray &addressPage,
                                    const ByteArray &param,
                                    const ByteArray &val,
                                    bool includeLen = false) {
    ByteArray res = includeLen ? Header(val.size() + 10) : Header();
    for (auto val : StringParam())
      res.push_back(val);
    for (auto v : addressPage)
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    for (auto v : val)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  ByteArray createStringParamSetCmd(const ByteArray &addressPage,
                                    const ByteArray &param,
                                    const QString &strVal,
                                    bool includeLen = false) {
    return createStringParamSetCmd(addressPage, param,
                                   Utils::packString(strVal), includeLen);
  }

  //===========================================================================================================================
  // blob parameter 0x04
  ByteArray createBlobParamGetCmd(const ByteArray &addressPage,
                                  const ByteArray &param) {
    ByteArray res = Header();
    for (auto val : ReqBlobParam())
      res.push_back(val);
    for (auto v : addressPage)
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  ByteArray createBlobParamSetCmd(const ByteArray &addressPage,
                                  const ByteArray &param, const ByteArray &val,
                                  bool includeLen = false) {
    ByteArray res = includeLen ? Header(val.size() + 10) : Header();
    for (auto v : Blob())
      res.push_back(v);
    for (auto v : addressPage)
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    for (auto v : val)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  //===========================================================================================================================
  // extended parameter 0x06
  ByteArray createExtParamGetCmd(const ByteArray &param) {
    ByteArray res = Header();
    for (auto v : ReqExtParam())
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  ByteArray createExtParamGetCmd(unsigned int param) {
    return createExtParamGetCmd(Utils::packRawVal(param));
  }

  ByteArray createExtParamSetCmd(const ByteArray &param, const ByteArray &vals,
                                 bool includeLen = false) {
    ByteArray res = includeLen ? Header(vals.size() + 13) : Header();

    if (includeLen) {
      // in extended parameter also the right product id is written
      if ((vals.size() + 13) < 128)
        res[5] = 0x02;
      else
        res[6] = 0x02;
    }

    for (auto v : ExtParamChange())
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    for (auto v : vals)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  ByteArray createExtParamSetCmd(unsigned int param, unsigned int val,
                                 bool includeLen = false) {
    return createExtParamSetCmd(Utils::packRawVal(param),
                                Utils::packRawVal(val), includeLen);
  }

  ByteArray createExtParamSetCmd(unsigned int param,
                                 const std::vector<unsigned int> &vals,
                                 bool includeLen = false) {
    ByteArray rawVals;
    for (unsigned int val : vals) {
      auto rawVal = Utils::packRawVal(val);
      for (auto v : rawVal)
        rawVals.push_back(v);
    }

    return createExtParamSetCmd(Utils::packRawVal(param), rawVals, includeLen);
  }

  //===========================================================================================================================
  // value as string
  ByteArray createValueAsStringGetCmd(const ByteArray &addressPage,
                                      const ByteArray &param,
                                      const ByteArray &val) {
    ByteArray res;
    for (auto v : Header())
      res.push_back(v);
    for (auto v : ReqParamAsString())
      res.push_back(v);
    for (auto v : addressPage)
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    for (auto v : val)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  ByteArray createValueAsStringGetCmd(const ByteArray &addressPage,
                                      const ByteArray &param,
                                      unsigned short rawVal) {
    return createValueAsStringGetCmd(addressPage, param,
                                     Utils::packRawVal(rawVal));
  }

  //===========================================================================================================================
  // extended string parameter
  ByteArray createExtStringParamGetCmd(const ByteArray &param) {
    ByteArray res;
    for (auto v : Header())
      res.push_back(v);
    for (auto v : ReqExtStringParam())
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  ByteArray createExtStringParamGetCmd(unsigned int param) {
    return createExtStringParamGetCmd(Utils::packRawVal(param));
  }

  //===========================================================================================================================
  //

  ByteArray createParamSetCmd(const ByteArray &func,
                              const ByteArray &addressPage,
                              const ByteArray &param, const ByteArray &val,
                              bool includeLen = false) {
    ByteArray res = includeLen ? Header(val.size() + 10) : Header();
    for (auto v : func)
      res.push_back(v);
    for (auto v : addressPage)
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    for (auto v : val)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  //===========================================================================================================================
  // reserved functions
  ByteArray createReservedFct7E(const ByteArray &addressPage,
                                const ByteArray &param, const ByteArray &val) {
    ByteArray res;
    for (auto v : Header())
      res.push_back(v);
    for (auto v : ReservedFct7E())
      res.push_back(v);
    for (auto v : addressPage)
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    for (auto v : val)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }

  ByteArray createReservedFct7F(const ByteArray &addressPage,
                                const ByteArray &param, const ByteArray &val) {
    ByteArray res;
    for (auto v : Header())
      res.push_back(v);
    for (auto v : ReservedFct7F())
      res.push_back(v);
    for (auto v : addressPage)
      res.push_back(v);
    for (auto v : param)
      res.push_back(v);
    for (auto v : val)
      res.push_back(v);
    res.push_back(Eox());
    return res;
  }
};

#endif // SYSEXBASE_H
