#include "stdafx.h"
#include "enumser.h"


int main()
{
  //Initialize COM (Required by CEnumerateSerial::UsingWMI)
  HRESULT hr = CoInitialize(nullptr);
  if (FAILED(hr))
  {
    _tprintf(_T("Failed to initialize COM, Error:%x\n"), hr);
    return hr;
  }

  //Initialize COM security (Required by CEnumerateSerial::UsingWMI)
  hr = CoInitializeSecurity(nullptr, -1, nullptr, nullptr, RPC_C_AUTHN_LEVEL_DEFAULT, RPC_C_IMP_LEVEL_IMPERSONATE, nullptr, EOAC_NONE, nullptr);
  if (FAILED(hr))
  {
    _tprintf(_T("Failed to initialize COM security, Error:%08X\n"), hr);
    CoUninitialize();
    return hr;
  }

  CEnumerateSerial::CPortsArray ports;
  CEnumerateSerial::CPortAndNamesArray portAndNames;
  CEnumerateSerial::CNamesArray names;

  ULONGLONG nStartTick = 0;
#ifndef NO_CENUMERATESERIAL_USING_CREATEFILE
  _tprintf(_T("CreateFile method reports\n"));
  nStartTick = GetTickCount64();
  if (CEnumerateSerial::UsingCreateFile(ports))
  {
    for (const auto& port : ports)
      _tprintf(_T("COM%u\n"), port);
  }
  else
    _tprintf(_T("CEnumerateSerial::UsingCreateFile failed, Error:%u\n"), GetLastError());
  _tprintf(_T(" Time taken: %I64u ms\n"), GetTickCount64() - nStartTick);
#endif //#ifndef NO_CENUMERATESERIAL_USING_CREATEFILE

#ifndef NO_CENUMERATESERIAL_USING_QUERYDOSDEVICE
  _tprintf(_T("QueryDosDevice method reports\n"));
  nStartTick = GetTickCount64();
  if (CEnumerateSerial::UsingQueryDosDevice(ports))
  {
    for (const auto& port: ports)
      _tprintf(_T("COM%u\n"), port);
  }
  else
    _tprintf(_T("CEnumerateSerial::UsingQueryDosDevice failed, Error:%u\n"), GetLastError());
  _tprintf(_T(" Time taken: %I64u ms\n"), GetTickCount64() - nStartTick);
#endif //#ifndef NO_CENUMERATESERIAL_USING_QUERYDOSDEVICE

#ifndef NO_CENUMERATESERIAL_USING_GETDEFAULTCOMMCONFIG
  _tprintf(_T("GetDefaultCommConfig method reports\n"));
  nStartTick = GetTickCount64();
  if (CEnumerateSerial::UsingGetDefaultCommConfig(ports))
  {
    for (const auto& port: ports)
      _tprintf(_T("COM%u\n"), port);
  }
  else
    _tprintf(_T("CEnumerateSerial::UsingGetDefaultCommConfig failed, Error:%u\n"), GetLastError());
  _tprintf(_T(" Time taken: %I64u ms\n"), GetTickCount64() - nStartTick);
#endif //#ifndef NO_CENUMERATESERIAL_USING_GETDEFAULTCOMMCONFIG

#ifndef NO_CENUMERATESERIAL_USING_SETUPAPI1
  _tprintf(_T("Device Manager (SetupAPI - GUID_DEVINTERFACE_COMPORT) reports\n"));
  nStartTick = GetTickCount64();
  if (CEnumerateSerial::UsingSetupAPI1(portAndNames))
  {
    for (const auto& port : portAndNames)
#pragma warning(suppress: 26489)
      _tprintf(_T("COM%u <%s>\n"), port.first, port.second.c_str());
  }
  else
    _tprintf(_T("CEnumerateSerial::UsingSetupAPI1 failed, Error:%u\n"), GetLastError());
  _tprintf(_T(" Time taken: %I64u ms\n"), GetTickCount64() - nStartTick);
#endif //#ifndef NO_CENUMERATESERIAL_USING_SETUPAPI1

#ifndef NO_CENUMERATESERIAL_USING_SETUPAPI2
  _tprintf(_T("Device Manager (SetupAPI - Ports Device information set) reports\n"));
  nStartTick = GetTickCount64();
  if (CEnumerateSerial::UsingSetupAPI2(portAndNames))
  {
    for (const auto& port : portAndNames)
#pragma warning(suppress: 26489)
      _tprintf(_T("COM%u <%s>\n"), port.first, port.second.c_str());
  }
  else
    _tprintf(_T("CEnumerateSerial::UsingSetupAPI2 failed, Error:%u\n"), GetLastError());
  _tprintf(_T(" Time taken: %I64u ms\n"), GetTickCount64() - nStartTick);
#endif //#ifndef NO_CENUMERATESERIAL_USING_SETUPAPI2

#ifndef NO_CENUMERATESERIAL_USING_ENUMPORTS
  _tprintf(_T("EnumPorts method reports\n"));
  nStartTick = GetTickCount64();
  if (CEnumerateSerial::UsingEnumPorts(portAndNames))
  {
    for (const auto& port : portAndNames)
#pragma warning(suppress: 26489)
      _tprintf(_T("COM%u <%s>\n"), port.first, port.second.c_str());
  }
  else
    _tprintf(_T("CEnumerateSerial::UsingEnumPorts failed, Error:%u\n"), GetLastError());
  _tprintf(_T(" Time taken: %I64u ms\n"), GetTickCount64() - nStartTick);
#endif //#ifndef NO_CENUMERATESERIAL_USING_ENUMPORTS

#ifndef NO_CENUMERATESERIAL_USING_WMI
  _tprintf(_T("WMI method reports\n"));
  nStartTick = GetTickCount64();
  hr = CEnumerateSerial::UsingWMI(portAndNames);
  if (SUCCEEDED(hr))
  {
    for (const auto& port : portAndNames)
#pragma warning(suppress: 26489)
      _tprintf(_T("COM%u <%s>\n"), port.first, port.second.c_str());
  }
  else
    _tprintf(_T("CEnumerateSerial::UsingWMI failed, Error:%08X\n"), hr);
  _tprintf(_T(" Time taken: %I64u ms\n"), GetTickCount64() - nStartTick);
#endif //#ifndef NO_CENUMERATESERIAL_USING_WMI

#ifndef NO_CENUMERATESERIAL_USING_COMDB
  _tprintf(_T("ComDB method reports\n"));
  nStartTick = GetTickCount64();
  if (CEnumerateSerial::UsingComDB(ports))
  {
    for (const auto& port : ports)
      _tprintf(_T("COM%u\n"), port);
  }
  else
    _tprintf(_T("CEnumerateSerial::UsingComDB failed, Error:%u\n"), GetLastError());
  _tprintf(_T(" Time taken: %I64u ms\n"), GetTickCount64() - nStartTick);
#endif //#ifndef NO_CENUMERATESERIAL_USING_COMDB

#ifndef NO_CENUMERATESERIAL_USING_REGISTRY
  _tprintf(_T("Registry method reports\n"));
  nStartTick = GetTickCount64();
  if (CEnumerateSerial::UsingRegistry(names))
  {
    for (const auto& name : names)
      _tprintf(_T("%s\n"), name.c_str());
  }
  else
    _tprintf(_T("CEnumerateSerial::UsingRegistry failed, Error:%u\n"), GetLastError());
  _tprintf(_T(" Time taken: %I64u ms\n"), GetTickCount64() - nStartTick);
#endif //#ifndef NO_CENUMERATESERIAL_USING_REGISTRY

#ifndef NO_CENUMERATESERIAL_USING_GETCOMMPORTS
  _tprintf(_T("UsingGetCommPorts method reports\n"));
  nStartTick = GetTickCount64();
  if (CEnumerateSerial::UsingGetCommPorts(ports))
  {
    for (const auto& port : ports)
      _tprintf(_T("COM%u\n"), port);
  }
  else
    _tprintf(_T("CEnumerateSerial::UsingGetCommPorts failed, Error:%u\n"), GetLastError());
  _tprintf(_T(" Time taken: %I64u ms\n"), GetTickCount64() - nStartTick);
#endif //#ifndef NO_CENUMERATESERIAL_USING_GETCOMMPORTS

  //Close down COM
  CoUninitialize();

  return 0;
}
