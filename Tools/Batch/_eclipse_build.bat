@echo off

REM define ARM build tool path if not defined
IF NOT DEFINED ECLIPSE_EXE (SET ECLIPSE_EXE="C:\Aegis\Core\eclipse.exe")

%ECLIPSE_EXE% -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild --launcher.suppressErrors -data "tempWorkspace" -import "%1%" -cleanBuild "%1%/Debug"
rmdir tempWorkspace /s /q