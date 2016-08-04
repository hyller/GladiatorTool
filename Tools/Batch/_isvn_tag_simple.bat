@echo off
setlocal

set /p input="Did you increase version?    [Y/N]:"
if not "%input%" == "Y" goto EXIT

set /p input="Did you rebuild project?     [Y/N]:"
if not "%input%" == "Y" goto EXIT

set /p input="Did you write release notes? [Y/N]:"
if not "%input%" == "Y" goto EXIT

set /p input="Did you commit all changes?  [Y/N]:"
if not "%input%" == "Y" goto EXIT

call %GLADIATOR_HOME%\Tools\Batch\_get_version_str.bat %*

if %VERSION_STR% == "" goto Error

call isvn tag %VERSION_STR%
@echo off
goto EXIT

:Error
echo "!!!Error Happen!!!"

:EXIT
endlocal
@echo on
