@echo off
set CUR_DIR=%~dp0
cd ../src
make init
make
cd %CUR_DIR%
@echo on

call semver -v
call semver -h
call semver -x version.test
call semver -y version.test
call semver -z version.test
call semver version.test


