@echo off
setlocal

call %GLADIATOR_HOME%/Scripts/svn/_svn_repos_root.bat

@echo on
svn sw %REPOS_ROOT%/trunk
@echo off

:END
endlocal
@echo on