@echo off
setlocal

if "%1" == "store_user" goto STORE_USER
if "%1" == "clean" goto CLEAN

echo "error input"
goto END

REM store user authority
:STORE_USER
git config --global credential.helper store
goto END

:CLEAN
for /f "usebackq tokens=2*" %%i in (`git status -s ^| findstr /r "^\??"`) do rm -rf "%%i"
goto END

:END
endlocal
@echo on