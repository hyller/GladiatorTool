@echo off

cd src

call semver.bat %%1 version.h
make

cd ..

@echo on