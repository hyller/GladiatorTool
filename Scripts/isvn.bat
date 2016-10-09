@echo off
setlocal

if "%1" == "auto" goto AUTO
if "%1" == "backup" goto BACKUP
if "%1" == "branch" goto BRANCH
if "%1" == "clean" goto CLEAN
if "%1" == "green" goto GREEN
if "%1" == "merge_branch" goto MERGE_BRANCH
if "%1" == "merge_trunk" goto MERGE_TRUNK
if "%1" == "sw_branch" goto SW_BRANCH
if "%1" == "sw_trunk" goto SW_TRUNK
if "%1" == "sw_tag" goto SW_TAG
if "%1" == "repos_root" goto REPOS_ROOT
if "%1" == "tag" goto TAG
if "%1" == "admin_dump" goto ADMIN_DUMP
if "%1" == "ci" goto COMMIT
if "%1" == "ci2" goto COMMITARTF
if "%1" == "ci2s" goto COMMITARTFS
if "%1" == "archive_tag" goto ARCHIVE_TAG
if "%1" == "archive_tagnodoc" goto ARCHIVE_TAG_NODOC

echo "error input"
goto END

:AUTO
call %GLADIATOR_HOME%/Scripts/svn/svn_auto.bat
@echo off
goto END

:BACKUP
call %GLADIATOR_HOME%/Scripts/svn/svn_bak_modified.bat
@echo off
goto END

:BRANCH
call %GLADIATOR_HOME%/Scripts/svn/svn_branch.bat %2 %3
@echo off
goto END

:CLEAN
call %GLADIATOR_HOME%/Scripts/svn/svn_clean_unversion.bat
@echo off
goto END

:GREEN
call %GLADIATOR_HOME%/Scripts/svn/svn_green.bat
@echo off
goto END

:MERGE_BRANCH
call %GLADIATOR_HOME%/Scripts/svn/svn_merge_branch.bat %2
@echo off
goto END

:MERGE_TRUNK
call %GLADIATOR_HOME%/Scripts/svn/svn_merge_trunk.bat
@echo off
goto END

:SW_BRANCH
call %GLADIATOR_HOME%/Scripts/svn/svn_sw_branch.bat %2
@echo off
goto END

:SW_TRUNK
call %GLADIATOR_HOME%/Scripts/svn/svn_sw_trunk.bat
@echo off
goto END

:SW_TAG
call %GLADIATOR_HOME%/Scripts/svn/svn_sw_tag.bat %2
@echo off
goto END

:REPOS_ROOT
call %GLADIATOR_HOME%/Scripts/svn/svn_repos_root.bat
@echo off
goto END

:TAG
call %GLADIATOR_HOME%/Scripts/svn/svn_tag.bat %2
@echo off
goto END

:ADMIN_DUMP
call %GLADIATOR_HOME%/Scripts/svn/svn_admin_dump.bat %2
@echo off
goto END

:COMMIT
call %GLADIATOR_HOME%/Scripts/svn/svn_ci.bat %2 %3 %4 %5 %6 %7 %8 %9
@echo off
goto END

:COMMITARTF
call %GLADIATOR_HOME%/Scripts/svn/svn_ciartf.bat %2 %3 %4 %5 %6 %7 %8 %9
@echo off
goto END

:COMMITARTFS
call %GLADIATOR_HOME%/Scripts/svn/svn_ciartf.bat "sync merge"
@echo off
goto END

:ARCHIVE_TAG
call %GLADIATOR_HOME%/Scripts/svn/svn_archive_tag.bat %2
@echo off
goto END

:ARCHIVE_TAG_NODOC
call %GLADIATOR_HOME%/Scripts/svn/svn_archive_tag_nodoc.bat %2
@echo off
goto END


:END
endlocal
@echo on