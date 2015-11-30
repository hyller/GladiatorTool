@echo off
setlocal
rem sw branch
rem usage: svn_sw_branch xxx

if "%1" == "" goto ERROR

call %GLADIATOR_HOME%/Scripts/svn/_svn_repos_root.bat

svn sw %REPOS_ROOT%/branches/%1
goto END

:ERROR
echo !!!error happen!!!
echo usage: svn_sw_branch xxx

:END
endlocal
@echo on