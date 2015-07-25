@echo off
setlocal

REM Usage: igit store_user

if "%1" == "store_user" goto STORE_USER
if "%1" == "clean_unversion" goto CLEAN_UNVERSION

echo "error input"
goto END

:STORE_USER
git config --global credential.helper store
goto END

:CLEAN_UNVERSION
for /f "usebackq tokens=2*" %%i in (`git status -s ^| findstr /r "^\??"`) do rm -rf "%%i"
goto END



:END
endlocal
@echo on