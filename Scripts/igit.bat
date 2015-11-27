@echo off
setlocal

rem A wrapper on git, msysgit need installed 


if "%1" == "store_user" goto STORE_USER
if "%1" == "clean" goto CLEAN
if "%1" == "alias" goto ALIAS
if "%1" == "ci" goto COMMIT

echo "error input"
goto END

REM store user authority
:STORE_USER
git config --global credential.helper store
goto END

:CLEAN
for /f "usebackq tokens=2*" %%i in (`git status -s ^| findstr /r "^\??"`) do rm -rf "%%i"
goto END

:COMMIT
git commit -m"%2 %3 %4 %5 %6 %7 %8 %9"
git push
goto END

REM create alias for git command
:ALIAS
@echo on
git config --global alias.co checkout
git config --global alias.br branch
git config --global alias.ci commit
git config --global alias.st status
@echo off
goto END

:END
endlocal
@echo on