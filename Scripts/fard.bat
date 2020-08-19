@echo off
setlocal

rem brief: Replace string in all files under current directly
rem usage: fard str_old str_new
rem ex   : fard gaia gesp
rem        replace gaia by gesp
rem to be safe, only do find in this script, if you want to find and replace, please use `fart -r --svn . old new`
rem 

fart -r --svn . %1

endlocal
@echo on