@echo off
set CUR_DIR=%~dp0
cd src
make init
make
cd %CUR_DIR%
@echo on

call %CUR_DIR%src\semver.exe
call %CUR_DIR%src\semver.exe -v
call %CUR_DIR%src\semver.exe -h
call %CUR_DIR%src\semver.exe -i1.2.3 version.test
call %CUR_DIR%src\semver.exe version.test
call %CUR_DIR%src\semver.exe -x version.test
call %CUR_DIR%src\semver.exe -y version.test
call %CUR_DIR%src\semver.exe -z version.test
call %CUR_DIR%src\semver.exe -z -l2 version.test
call %CUR_DIR%src\semver.exe -aversion.test -l2 version.test 
call %CUR_DIR%src\semver.exe -s simple.test
call %CUR_DIR%src\semver.exe -g version.test
