@echo off
setlocal

python %~dp0\convertor.py %*

endlocal
@echo on