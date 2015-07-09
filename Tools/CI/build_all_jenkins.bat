set work_dir=%WORKSPACE%

cd %work_dir%

rem green work copy
svn revert -R .
for /f "usebackq tokens=2*" %%i in (`svn status ^| findstr /r "^\?"`) do svn delete --force "%%i %%j"
svn up

rem start build
call %work_dir%\Tools\CI\build_all.bat

