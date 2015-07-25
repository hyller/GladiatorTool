@echo off
setlocal

if "%1" == "auto" goto AUTO

echo "error input"
goto END

:AUTO
echo auto
goto END

:BAK_MODIFIED
echo bak_modified
goto END

:BRANCH
echo branch
goto END

:END
endlocal
@echo on