@echo off
setlocal
REM Create a branch and switch to the branch
REM Usage: svn_cbsw description

call %GLADIATOR_HOME%/Scripts/svn/_svn_repos_root.bat

if "%1" == "" goto SHOW

svn cp %REPOS_ROOT%/trunk %REPOS_ROOT%/branches/%1 -m"Create a branch to work on[%1]"
svn sw %REPOS_ROOT%/trunk
svn sw %REPOS_ROOT%/branches/%1
goto END

:SHOW
svn ls %repos_root%/branches/

:END
endlocal
@echo on