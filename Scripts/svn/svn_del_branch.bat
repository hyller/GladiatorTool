@echo off
setlocal
rem delete branch
rem usage: svn_del_branch branch_name comments

if "%~2" == "" goto ERROR

call %GLADIATOR_HOME%/Scripts/svn/_svn_repos_root.bat
call %GLADIATOR_HOME%\Scripts\svn\_svn_get_artf.bat

@echo on
svn del %REPOS_ROOT%/branches/%1 -m"[%artf%] %~2"
@echo off
goto END

:ERROR
echo !!!error happen!!!
echo usage: svn_del_branch branch_name comments

:END
endlocal
@echo on