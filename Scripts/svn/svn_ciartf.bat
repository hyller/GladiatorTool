@echo off
setlocal

call %GLADIATOR_HOME%\Scripts\svn\_svn_get_artf.bat
call %GLADIATOR_HOME%\Tools\Batch\_get_cd_name.bat

if "%artf%" == "" set artf=%CURRENT_DIR_NAME%

@echo on
svn ci -m"[%artf%] %~1"
@echo off

endlocal
@echo on