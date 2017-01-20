@echo off
setlocal
rem delete branch
rem usage: svn_del_branch xxx

if "%1" == "" goto ERROR

call %GLADIATOR_HOME%/Scripts/svn/_svn_repos_root.bat
call %GLADIATOR_HOME%\Scripts\svn\_svn_get_artf.bat

svn del %REPOS_ROOT%/branches/%1 -m"[%artf%] Delete this branch"
goto END

:ERROR
echo !!!error happen!!!
echo usage: svn_del_branch xxx

:END
endlocal
@echo on