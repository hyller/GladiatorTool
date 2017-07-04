@echo off
setlocal

if "%1" == "auto" goto AUTO
if "%1" == "backup" goto BACKUP
if "%1" == "br" goto BRANCH
if "%1" == "clean" goto CLEAN
if "%1" == "green" goto GREEN
if "%1" == "mebr" goto MERGE_BRANCH
if "%1" == "metr" goto MERGE_TRUNK
if "%1" == "swbr" goto SW_BRANCH
if "%1" == "delbr" goto DEL_BRANCH
if "%1" == "swtr" goto SW_TRUNK
if "%1" == "swtag" goto SW_TAG
if "%1" == "repos_root" goto REPOS_ROOT
if "%1" == "tag" goto TAG
if "%1" == "admin_dump" goto ADMIN_DUMP
if "%1" == "ci2" goto COMMIT
if "%1" == "ci" goto COMMITARTF
if "%1" == "cis" goto COMMITARTFS
if "%1" == "cib" goto COMMITARTFBACKUP
if "%1" == "smci" goto SYNCMERGECI
if "%1" == "archive_tag" goto ARCHIVE_TAG
if "%1" == "archive_tagnodoc" goto ARCHIVE_TAG_NODOC
if "%1" == "sebr" goto FILTER_BRANCH

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

:DEL_BRANCH
call %GLADIATOR_HOME%/Scripts/svn/svn_del_branch.bat %2 "%~3"
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
call %GLADIATOR_HOME%/Scripts/svn/svn_ci.bat "%~2"
@echo off
goto END

:COMMITARTF
call %GLADIATOR_HOME%/Scripts/svn/svn_ciartf.bat "%~2"
@echo off
goto END

:COMMITARTFS
call %GLADIATOR_HOME%/Scripts/svn/svn_ciartf.bat "sync merge"
@echo off
goto END

:COMMITARTFBACKUP
call %GLADIATOR_HOME%/Scripts/svn/svn_ciartf.bat "backup"
@echo off
goto END

:SYNCMERGECI
call %GLADIATOR_HOME%/Scripts/svn/svn_merge_trunk.bat
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

:FILTER_BRANCH
call %GLADIATOR_HOME%/Scripts/svn/svn_filter_branch.bat "%~2"
@echo off
goto END

:END
endlocal
@echo on