@echo off
setlocal

rem A wrapper on git, msysgit need installed 


if "%1" == "store_user" goto STORE_USER
if "%1" == "clean" goto CLEAN
if "%1" == "alias" goto ALIAS
if "%1" == "ci" goto COMMIT
if "%1" == "updateall" goto UPDATEALL
if "%1" == "sync" goto SYNC

echo "error input"
goto END

REM store user authority
:STORE_USER
git config --global credential.helper store
goto END

:CLEAN
git clean -fd
goto END

:COMMIT
git commit -a -m"%~2"
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

:UPDATEALL
@echo on
git pull 
git submodule init
git submodule update
@echo off
goto END

:SYNC
@echo on
git pull 
git submodule init
git submodule update
git add .
git commit -m"%~2"
git push
@echo off
goto END

:END
endlocal
@echo on