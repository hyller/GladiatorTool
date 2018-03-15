REM Build EWARM Project From Command
REM Usage: 
REM Param 1: .ewp ProjectPath
REM Param 2: Config

REM define ARM build tool path if not defined
IF NOT DEFINED IARBUILD_EXE_ARM (SET IARBUILD_EXE_ARM="C:\Program Files\IAR Systems\Embedded Workbench ARM 7.80.4\common\bin\IarBuild.exe")

%IARBUILD_EXE_ARM% %1 -build %2


