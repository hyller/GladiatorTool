@echo off
setlocal

python %~dp0\stat_sniffer.py %*

endlocal
@echo on