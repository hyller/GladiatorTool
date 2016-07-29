REM ---------------------------------------------------------------------------
REM This script read version string from a file by calling semver.exe
REM Then set the version string to VERSION_STR envirament veriable
REM Usage:
REM   semverenv.bat file
REM   semverenv.bat -s file
REM
REM Pre-request, put semver.exe in the same folder to this batch file 
REM ---------------------------------------------------------------------------
SET semver_get_str=call semver -g %1 %2
FOR /F "usebackq tokens=2*" %%i IN (`%semver_get_str% ^| findstr /r "^\Input"`) DO  SET VERSION_STR=%%j
ECHO %VERSION_STR%
