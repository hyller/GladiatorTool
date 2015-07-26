rem get project reposity root
for /f "usebackq tokens=2*" %%i in (`svn info ^| findstr /r "Root:"`) do  set REPOS_ROOT=%%j