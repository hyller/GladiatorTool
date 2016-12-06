@echo off
setlocal
REM Create a branch and switch to the branch
REM Usage: svn_branch branch_name
REM Usage: svn_branch branch_id branch_name

call %GLADIATOR_HOME%/Scripts/svn/_svn_repos_root.bat

if "%1" == "" goto SHOW

if "%2" == "" (
  set BRANCH_NAME=%1
  set BRANCH_ARTFID=%1
) else (
  set BRANCH_NAME=%1_%2
  set BRANCH_ARTFID=%1
)

svn cp %REPOS_ROOT%/trunk %REPOS_ROOT%/branches/%BRANCH_NAME% -m"Create a branch to work on[%BRANCH_ARTFID%]"
svn sw %REPOS_ROOT%/trunk
svn sw %REPOS_ROOT%/branches/%BRANCH_NAME%
goto END

:SHOW
svn ls %repos_root%/branches/ -v

:END
endlocal
@echo on