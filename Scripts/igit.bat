@echo off
setlocal

REM Usage: igit store_user

if "%1" == "store_user" goto STORE_USER

echo "error input"
goto END

:STORE_USER
echo git config --global credential.helper store

:END
endlocal
@echo on