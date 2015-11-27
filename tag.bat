@echo off
setlocal

rem get version
for /f "usebackq tokens=2*" %%i in (`semver -g version ^| findstr /r "^\Input"`) do  set VERSION_STR=%%j

if %VERSION_STR% == "" goto EXIT

git tag GladiatorFirmware_%VERSION_STR%

:EXIT
endlocal
@echo on
