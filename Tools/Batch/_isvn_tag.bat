@echo off
setlocal

call %GLADIATOR_HOME%\Tools\Batch\_get_version_str.bat %*
call %GLADIATOR_HOME%\Tools\Batch\_get_cd_name.bat

if %VERSION_STR% == "" goto Error
if %CURRENT_DIR_NAME% == "" goto Error

echo call isvn tag %CURRENT_DIR_NAME%_%VERSION_STR%
@echo off
goto EXIT

:Error
echo "!!!Error Happen!!!"

:EXIT
endlocal
@echo on
