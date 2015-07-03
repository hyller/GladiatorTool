@echo off
setlocal

REM usage: generate dump file, source is current dir, destination is ../RepositoryBak/
REM Usage: svnadmin_dump
REM Usage: svnadmin_dump repos_name

if "%1" == "" goto ALL

svnadmin dump %1 > ../RepositoryBak/%1.dump
goto END

:ALL
for /f %%i in ('dir /b /a:d .') do svnadmin dump %%i > ../RepositoryBak/%%i.dump

:END
endlocal
@echo on