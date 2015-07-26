@echo off
setlocal

svn revert -R .
for /f "usebackq tokens=2*" %%i in (`svn status ^| findstr /r "^\?"`) do svn delete --force "%%i %%j"
svn up

:END
endlocal
@echo on