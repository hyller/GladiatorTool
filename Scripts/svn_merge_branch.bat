@echo off
setlocal
rem merge branch
rem usage: svn_merge_branch xxx

if "%1" == "" goto ERROR

call _svn_repos_root.bat

svn up
svn merge %REPOS_ROOT%/branches/%1
goto END

:ERROR
echo !!!error happen!!!
echo usage: svn_merge_branch xxx

:END
endlocal
@echo on