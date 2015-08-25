REM define MSP430 build tool path if not defined
IF NOT DEFINED IARBUILD_EXE_MSP (SET IARBUILD_EXE_MSP="C:\Program Files\IAR Systems\Embedded Workbench MSP430 5.40\common\bin\IarBuild.exe")

%IARBUILD_EXE_MSP% %1% -clean  Debug
%IARBUILD_EXE_MSP% %1% -build  Debug

%IARBUILD_EXE_MSP% %1% -clean  Release
%IARBUILD_EXE_MSP% %1% -build  Release


