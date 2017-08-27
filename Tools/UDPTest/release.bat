@echo off
setlocal

IF "%1" == "" GOTO SKIP_BUMP_VERSION

REM Bump version string
call semver.bat %1 version.h
IF NOT errorlevel 0 goto ERROR

:SKIP_BUMP_VERSION
REM Rebuild target
make clean
make
IF NOT errorlevel 0 goto ERROR

REM Delete Folder
RMDIR /S /Q UDPTest
REM Create Folder
mkdir UDPTest
IF NOT errorlevel 0 goto ERROR

REM Copy all to UDPTest
copy udps.exe UDPTest\
copy udpc.exe UDPTest\
copy readme.txt UDPTest\

REM Pack Them All
call %GLADIATOR_HOME%\Tools\Batch\_get_version_str.bat version.h
@echo off
if exist UDPTest_%VERSION_STR%.zip erase /Q UDPTest_%VERSION_STR%.zip
7z.exe a UDPTest_%VERSION_STR%.zip UDPTest\
IF NOT errorlevel 0 goto ERR

goto EXIT
:ERROR
echo "!!!Error Happen!!!"

:EXIT
endlocal
@echo on