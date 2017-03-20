@echo off
setlocal

rem brief: Compress directory
rem usage: gzipd dir_name

tar -aczf %1.zip %1

endlocal
@echo on