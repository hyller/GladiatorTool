@echo off
setlocal

if "%1" == "" goto ERROR

call %GLADIATOR_HOME%/Scripts/svn/_svn_repos_root.bat

rem Display my branches on gaia repository
for /f "usebackq tokens=*" %%i in (`svn ls %REPOS_ROOT%/branches/ -v ^| findstr "%1"`) do echo %%i
goto END

:ERROR
echo !!!error happen!!!
echo usage: svn_filter_branch xxx

:END
endlocal
@echo on
