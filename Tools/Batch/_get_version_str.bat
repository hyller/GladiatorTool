set semver_get_str=call semver -g %*
for /f "usebackq tokens=2*" %%i in (`%semver_get_str% ^| findstr /r "^\Input"`) do  set VERSION_STR=%%j
