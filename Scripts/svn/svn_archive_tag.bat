@echo off
setlocal
REM Export a tag and archive it
REM Usage: svn_archive_tag tag_name

if "%1" == "" goto ERROR

call %GLADIATOR_HOME%/Scripts/svn/_svn_repos_root.bat

@echo on
svn export %REPOS_ROOT%/tags/%1
7z.exe a %1.7z %1\
@echo off
goto END

:ERROR
echo !!!error happen!!!
echo usage: svn_archive_tag tag_name

:END
endlocal
@echo on