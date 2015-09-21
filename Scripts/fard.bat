@echo off
setlocal

rem brief: Replace string in all files under current directly
rem usage: fard str_old str_new
rem ex   : fard gaia gesp
rem        replace gaia by gesp

fart -r --svn . %1 %2

endlocal
@echo on