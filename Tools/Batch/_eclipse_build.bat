REM Build Eclipse Project From Command
REM Usage: 
REM Param 1: Project Path
REM Param 2: Pojectname
REM Param 3: Config

REM define ARM build tool path if not defined
IF NOT DEFINED ECLIPSE_EXE (SET ECLIPSE_EXE="C:\Aegis\Core\eclipsec.exe")

%ECLIPSE_EXE% -nosplash -application org.eclipse.cdt.managedbuilder.core.headlessbuild --launcher.suppressErrors -data "tempWorkspace" -import "%1" -cleanBuild "%2/%3"
rmdir tempWorkspace /s /q