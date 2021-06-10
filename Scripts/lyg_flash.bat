@echo off

if "%1" == "reset" goto RESET
if "%2" == "" goto NORMAL

:BIN
REM jflash project_file download_file
ECHO Open a project and data file, start auto processing and exit
"C:\Program Files (x86)\SEGGER\JLink\JFlash.exe" -openprj"%GLADIATOR_HOME%\Scripts\JFlashPro\lyg.jflash" -open"%~1,%2" -auto -exit
IF ERRORLEVEL 1 goto ERROR
goto END

:RESET
"C:\Program Files (x86)\SEGGER\JLink\JFlash.exe" -openprj"%GLADIATOR_HOME%\Scripts\JFlashPro\lyg.jflash" -startapp -exit
goto END

:NORMAL
REM jflash project_file download_file
ECHO Open a project and data file, start auto processing and exit
"C:\Program Files (x86)\SEGGER\JLink\JFlash.exe" -openprj"%GLADIATOR_HOME%\Scripts\JFlashPro\lyg.jflash" -open"%~1" -auto -exit
IF ERRORLEVEL 1 goto ERROR
goto END

:ERROR
ECHO J-Flash ARM:  Error!
pause

:END