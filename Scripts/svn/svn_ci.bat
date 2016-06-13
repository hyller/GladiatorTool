@echo off
setlocal

call %GLADIATOR_HOME%\Tools\Batch\_get_cd_name.bat

@echo on
svn ci -m"[%CURRENT_DIR_NAME%] %~1"
@echo off

endlocal
@echo on