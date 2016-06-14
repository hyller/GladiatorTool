rem get whole url
rem example: https://teamforge.xxxxxx.com/svn/repos/projectname/branches/artf103213_unit_test_achieve_coverage_Partial_GWidget_4
for /f "usebackq tokens=2*" %%i in (`svn info ^| findstr /r "^\URL:"`) do set url=%%i
for /f "usebackq tokens=2*" %%i in (`svn info ^| findstr /r "Root:"`) do set str=%%j

rem get relative url
rem example:/branches/artf103213_unit_test_achieve_coverage_Partial_GWidget_4
set "realtive_url=%url%"
rem set "str=%gaia_root%"
:count
set "realtive_url=%realtive_url:~1%"
set "str=%str:~1%"
if defined str goto count

rem set branch name
rem example:artf103213_unit_test_achieve_coverage_Partial_GWidget_4
set branch_name=%realtive_url:~10%

rem set artf id
rem example:artf103213
for /f "usebackq delims=_" %%i in ('%branch_name%') do set artf=%%i
