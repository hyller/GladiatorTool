@echo off
setlocal

call %GLADIATOR_HOME%\Scripts\svn\_svn_get_artf.bat

@echo on
svn ci -m"[%artf%] %~1"
@echo off

endlocal
@echo on