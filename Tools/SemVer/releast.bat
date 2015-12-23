@echo off

call semver.exe %%1 version.h

make init
make

@echo on