@echo off
setlocal
REM iar2fl dep_name target_name

python %~dp0\iar2fl.py %1 %2

endlocal
@echo on