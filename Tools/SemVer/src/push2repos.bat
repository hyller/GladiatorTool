@echo off
setlocal

set SEMVER_DIR="w:\SemVer"

rem copy semver.exe
rem copy readme.md
rem goto local folder
cp %GALADIATOR_HOME%\Tools\SemVer\src\semver.exe %SEMVER_DIR%\semver.exe
cp %GALADIATOR_HOME%\Tools\SemVer\doc\README.MD %SEMVER_DIR%\README.MD
cd %SEMVER_DIR%

rem push to repos
rem git add .
rem git commit -m"%%1"
rem git push

endlocal
@echo on