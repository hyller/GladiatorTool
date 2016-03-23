@echo off
setlocal

REM USAGE: bin2ihex binname hexname
REM 
REM bin2inhe name 
REM biname is name.bin, hexname is name.hex

if "%2" == "" goto EMPTY
SET INPUT_FILE=%1
SET OUTPUT_FILE=%2
goto START

:EMPTY
SET INPUT_FILE=%1.bin
SET OUTPUT_FILE=%1.hex

:START
"%GLADIATOR_HOME%\ThirdParty\srecord-1.63-win32\srec_cat.exe" %INPUT_FILE% -binary -o %OUTPUT_FILE% -Intel 

endlocal
@echo on