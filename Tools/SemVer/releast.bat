@echo off

cd src

call semver.exe %%1 version.h
make init
make

cd ..

@echo on