@echo off
setlocal
rem add new files and delete missed files

for /f "usebackq tokens=2*" %%i in (`svn status ^| findstr /r "^\!"`) do svn del --force "%%i %%j"
for /f "usebackq tokens=2*" %%i in (`svn status ^| findstr /r "^\?"`) do svn add --force "%%i %%j"

:END
endlocal
@echo on