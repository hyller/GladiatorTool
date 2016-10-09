@echo off
setlocal
rem sw tag
rem usage: svn_sw_tag xxx

if "%1" == "" goto ERROR

call %GLADIATOR_HOME%/Scripts/svn/_svn_repos_root.bat

svn sw %REPOS_ROOT%/tags/%1
goto END

:ERROR
echo !!!error happen!!!
echo usage: svn_sw_tag xxx

:END
endlocal
@echo on