lcov --directory objs --capture --output-file app.info
genhtml --output-directory output --title "SemVer" app.info