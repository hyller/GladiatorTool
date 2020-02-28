@echo off
setlocal

rem A wrapper on git, msysgit need installed 


if "%1" == "store_user" goto STORE_USER
if "%1" == "clean" goto CLEAN
if "%1" == "alias" goto ALIAS
if "%1" == "ci" goto COMMIT
if "%1" == "updateall" goto UPDATEALL

echo "error input"
goto END

REM store user authority
:STORE_USER
git config --global credential.helper store
goto END

:CLEAN
for /f "usebackq tokens=2*" %%i in (`git status -s ^| findstr /r "^\??"`) do rm -rf "%%i %%j"
goto END

:COMMIT
call %GLADIATOR_HOME%\Tools\Batch\_get_cd_name.bat
echo git commit -a -m"[%CURRENT_DIR_NAME%] %~2"
git commit -a -m"[%CURRENT_DIR_NAME%] %~2"
echo git pull
git pull
echo git push
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

:END
endlocal
@echo on