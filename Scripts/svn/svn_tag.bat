@echo off
setlocal
REM Make a tag or show tags folder
REM Usage: svn_tag
REM Usage: svn_tag tag_name

call %GLADIATOR_HOME%/Scripts/svn/_svn_repos_root.bat

if "%1" == "" goto SHOW

svn cp %repos_root%/trunk %repos_root%/tags/%1 -m"Create tag %1"
goto END

:SHOW
svn ls %repos_root%/tags/

:END
endlocal
@echo on