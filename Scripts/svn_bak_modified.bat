@echo off
setlocal

for /f "usebackq tokens=2*" %%i in (`svn status ^| findstr /r "^\M"`) do cp %%i %%i.bak

:END
endlocal
@echo on