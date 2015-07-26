@echo off
setlocal
rem Sync merged

call w:\GladiatorFirmware/Scripts/svn/_svn_repos_root.bat

@echo on
svn up
svn merge %REPOS_ROOT%/trunk
@echo off

:END
endlocal
@echo on