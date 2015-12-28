for %%i in ("%cd%") do ( set CURRENT_DIR_NAME=%%~nxi )
set CURRENT_DIR_NAME=%CURRENT_DIR_NAME:~0,-1%