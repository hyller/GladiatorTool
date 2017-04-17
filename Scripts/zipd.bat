@echo off
setlocal

rem brief: Compress directory
rem usage: gzipd zip_name dir_name

7z.exe a %1 %2

endlocal
@echo on