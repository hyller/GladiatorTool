@echo off
rem To see support commands
rem 	gi list
rem Appending Programming Language settings to your projects .gitignore.
rem 	gi java,python >> .gitignore
rem
rem Do not use "echo off" to not affect any child calls.
setlocal

rem Get the abolute path to the parent directory, which is assumed to be the
rem Git installation root.
for /F "delims=" %%I in ("%~dp0..") do @set git_install_root=%%~fI
for /F "delims=" %%I in ("%~dp0..") do @set git_mingw_root=%%~fI\mingw
if not exist "%git_mingw_root%" @set git_mingw_root=%git_install_root%\mingw64
set PATH=%git_install_root%\bin;%git_mingw_root%\bin;%PATH%

if not exist "%HOME%" @set HOME=%HOMEDRIVE%%HOMEPATH%
if not exist "%HOME%" @set HOME=%USERPROFILE%

curl.exe -L -s https://www.gitignore.io/api/%*
@echo on