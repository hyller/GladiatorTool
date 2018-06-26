@echo off
REM jflash project_file download_file
ECHO Open a project and data file, start auto processing and exit
"C:\Program Files (x86)\SEGGER\JLink_V632g\JFlash.exe" -openprj"%~1" -open"%~2"  -auto -exit
IF ERRORLEVEL 1 goto ERROR
goto END
:ERROR
ECHO J-Flash ARM:  Error!
pause
:END