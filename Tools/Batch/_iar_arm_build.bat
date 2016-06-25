REM define ARM build tool path if not defined
IF NOT DEFINED IARBUILD_EXE_ARM (SET IARBUILD_EXE_ARM="C:\Program Files\IAR Systems\Embedded Workbench ARM 6.30.7\common\bin\IarBuild.exe")

%IARBUILD_EXE_ARM% %1 -clean  Debug
%IARBUILD_EXE_ARM% %1 -build  Debug

%IARBUILD_EXE_ARM% %1 -clean  Release
%IARBUILD_EXE_ARM% %1 -build  Release

