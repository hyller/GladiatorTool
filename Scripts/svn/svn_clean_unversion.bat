@echo off
setlocal

REM Delete unversioned files and folders from work copy

for /f "usebackq tokens=2*" %%i in (`svn status ^| findstr /r "^\?"`) do svn delete --force "%%i %%j"

:END
endlocal
@echo on