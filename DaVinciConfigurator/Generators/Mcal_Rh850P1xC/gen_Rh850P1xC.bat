@ECHO off
SETLOCAL

:: Set MCAL generator's path
SET MCAL_GEN_EXEC=C:\Renesas\CodeGenerator\code_generator\MCALGenerator.exe

::Specify the Family and Micro Variant
:: Set root folder
SET ROOT_FOLDER=..\..\..\ThirdParty\Mcal_Rh850P1xC\Supply\AUTOSAR_RH850_P1M-C_MCAL_Ver4.02.00.D
SET MICRO_FAMILY=X1x
SET MICRO_VARIANT=P1x-C
SET VARIANT=P1H-C
SET CONFIG=Sample

::First parameter - Module name
IF /i "%1"=="" (
GOTO :Help
)
SET MODULE_NAME=%1

::Second parameter - Device Variant.
REM IF /i "%2"=="" (
REM GOTO :Help
REM ) 
REM IF /i "%2"=="P1H-C" (
REM SET VARIANT=P1H-C
REM echo.
REM ) ELSE IF /i "%2"=="P1H-CE" (
REM SET VARIANT=P1H-CE
REM echo.
REM ) ELSE IF /i "%2"=="P1H-C" (
REM SET VARIANT=P1H-C
REM echo.
REM ) ELSE (
REM echo Error! Device not supported.
REM echo.
REM GOTO :eof
REM )
SET DEVICE_NO=%2

::Description file
SET ROOT_DESC=%3

::Set Generated file's destination
SET DEST_FOLDER=%4

::Set path to Reference Description
SET REF_DESC=%5

::Set path to config.xml
SET CONF_PATH=%6

Cls

::Set WDG driver instance as A
SET WDG_DRIVER_INSTANCE=DRIVERA

rem call :Generate

:Generate

::Set AR package name and Set Template file path
SET GEN_FOLDER=%ROOT_FOLDER%\%MICRO_FAMILY%\%MICRO_VARIANT%\modules\%MODULE_NAME%\generator

IF /i "%MODULE_NAME%"=="Wdg" (
SET AR-PACKAGE-NAME=/Renesas/DriverA
SET TEMPLATE_PATH=%GEN_FOLDER%\config\DriverA
) ELSE (
SET AR-PACKAGE-NAME=/Renesas/EcucDefs_%MODULE_NAME%
SET TEMPLATE_PATH=%GEN_FOLDER%\config
)

::Validate all the folders
if not exist %DEST_FOLDER% (
echo Error! Folder %DEST_FOLDER% doesn't exist.
echo.
GOTO :End
)

if not exist %DEST_FOLDER%\include (
mkdir %DEST_FOLDER%\include
)

if not exist %DEST_FOLDER%\src (
mkdir %DEST_FOLDER%\src
)

if not exist "%GEN_FOLDER%" (
echo Error! Folder %GEN_FOLDER% doesn't exist.
echo.
GOTO :End
)
if not exist "%TEMPLATE_PATH%" (
echo Error! Folder %TEMPLATE_PATH% doesn't exist.
echo.
GOTO :eof
)
IF NOT EXIST "%MCAL_GEN_EXEC%" (
echo Error! Could not find MCAL Generator executable
echo %MCAL_GEN_EXEC%
echo.
goto :End
)

::Set description file paths
SET DEM_REF=%ROOT_FOLDER%\%MICRO_FAMILY%\common_platform\generic\stubs\4.0.3\Dem\config\Dem_%MODULE_NAME%.arxml
rem SET MCU_REF=%ROOT_FOLDER%\%MICRO_FAMILY%\common_platform\generic\stubs\4.0.3\Mcu\config\Mcu_%MODULE_NAME%.arxml
SET MCU_REF=E:\usr\usage\Components\Mcal2\Mcal_Rh850P1xCRen01Asr4Sub\external\BSWMD\Mcal_Rh850P1xC\Mcu_bswmd.arxml
SET BSW_REF=%ROOT_FOLDER%\%MICRO_FAMILY%\%MICRO_VARIANT%\modules\%MODULE_NAME%\generator\R403_%MODULE_NAME%_%MICRO_VARIANT%_BSWMDT.arxml
SET ECUM_REF=%ROOT_FOLDER%\%MICRO_FAMILY%\common_platform\generic\stubs\4.0.3\EcuM\config\EcuM_%MODULE_NAME%.arxml

if not exist %ROOT_DESC% (
echo Error! Folder %ROOT_DESC% doesn't exist.
echo.
GOTO :eof
)

IF /i "%MODULE_NAME%"=="Port" (
GOTO :Port_Module
)

IF /i "%MODULE_NAME%"=="Adc" (
GOTO :Adc_Module
)

IF /i "%MODULE_NAME%"=="Mcu" (
GOTO :Mcu_Module
)

IF /i "%MODULE_NAME%"=="Wdg" (
GOTO :Wdg_Module
)

IF /i "%MODULE_NAME%"=="Dio" (
GOTO :Dio_Module
)

IF /i "%MODULE_NAME%"=="Spi" (
GOTO :Spi_Module
)

IF /i "%MODULE_NAME%"=="Gpt" (
GOTO :Gpt_Module
)

IF /i "%MODULE_NAME%"=="Icu" (
GOTO :Icu_Module
)

IF /i "%MODULE_NAME%"=="Fls" (
GOTO :Fls_Module
)

IF /i "%MODULE_NAME%"=="Pwm" (
GOTO :Pwm_Module
)

GOTO :End

::Generate file for PORT module
:Port_Module
@echo off
rem "%MCAL_GEN_EXEC%" %ROOT_DESC% %MODULE_NAME% %AR-PACKAGE-NAME% "%TEMPLATE_PATH%" -o "%GEN_FOLDER%" -ref %MODULE_NAME%_Impl %BSW_REF% 
"%MCAL_GEN_EXEC%" %ROOT_DESC% Port ActiveEcuC %CONF_PATH% -o "%GEN_FOLDER%" -ref Port_Impl %REF_DESC%

::Move generated files to destination path
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cbk.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cfg.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_PBcfg.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.c" "%DEST_FOLDER%\src"

echo.
EXIT /B %errorlevel%

::Generate file for ADC module
:Adc_Module
@echo off
rem "%MCAL_GEN_EXEC%" %ROOT_DESC% %MODULE_NAME%0 %AR-PACKAGE-NAME% "%TEMPLATE_PATH%" -o "%GEN_FOLDER%" -ref %MODULE_NAME%_Impl %BSW_REF% 
"%MCAL_GEN_EXEC%" %ROOT_DESC% Adc ActiveEcuC %CONF_PATH% -o "%GEN_FOLDER%" -ref Adc_Impl %REF_DESC%


rem MCALGenerator.exe "E:\Renesas\P1xC\P1xC.ecuc.arxml" Spi ActiveEcuC "e:\usr\usage\Components\Mcal2\Mcal_Rh850P1xCRen01Asr4Sub_NEU\external\ThirdParty\Mcal_Rh850P1xC\Supply\AUTOSAR_RH850_P1H-C_P1H-CE_MCAL_Ver4.01.00.001\X1x\P1x-C\modules\spi\generator\Config" -o "E:\Temp" -ref Spi_Impl "e:\usr\usage\Components\Mcal2\Mcal_Rh850P1xCRen01Asr4Sub_NEU\external\ThirdParty\Mcal_Rh850P1xC\Supply\AUTOSAR_RH850_P1H-C_P1H-CE_MCAL_Ver4.01.00.001\X1x\P1x-C\modules\spi\generator\R403_SPI_P1x-C_BSWMDT.arxml"
rem MCALGenerator.exe "E:\Renesas\P1xC\ECUC_Internal_Xslt1213089060370460279.arxml" Spi Renesas/EcucDefs_Spi "E:\usr\usage\Components\Mcal2\Mcal_Rh850P1xCRen01Asr4Sub_NEU\external\ThirdParty\Mcal_Rh850P1xC\Supply\AUTOSAR_RH850_P1H-C_P1H-CE_MCAL_Ver4.01.00.001\X1x\P1x-C\modules\spi\generator\Config" -o "e:\usr\usage\Components\Mcal2\Mcal_Rh850P1xCRen01Asr4Sub_NEU\external\ThirdParty\Mcal_Rh850P1xC\Supply\AUTOSAR_RH850_P1H-C_P1H-CE_MCAL_Ver4.01.00.001\X1x\P1x-C\modules\spi\generator" -ref Dem "E:\Renesas\P1xC\ECUC_Internal_Xslt1213089060370460279.arxml" Spi_Impl "E:\usr\usage\Components\Mcal2\Mcal_Rh850P1xCRen01Asr4Sub_NEU\external\ThirdParty\Mcal_Rh850P1xC\Supply\AUTOSAR_RH850_P1H-C_P1H-CE_MCAL_Ver4.01.00.001\X1x\P1x-C\modules\spi\generator\R403_SPI_P1x-C_BSWMDT.arxml"
rem MCALGenerator.exe <Description_File_Path>\P1xC.ecuc.arxml Spi ActiveEcuC <configxml_file_path> -o <Output_Path -ref Spi_Impl <Reference_Description_XML_Path>\R403_SPI_P1x-C_BSWMDT.arxml



::Move generated files to destination path
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cfg.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cbk.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_PBcfg.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.c" "%DEST_FOLDER%\src"

echo.
EXIT /B %errorlevel%

::Generate file for MCU module
:Mcu_Module
@echo off
rem "%MCAL_GEN_EXEC%" %ROOT_DESC% %MODULE_NAME%0 %AR-PACKAGE-NAME% "%TEMPLATE_PATH%" -o "%GEN_FOLDER%" -ref Dem0 %DEM_REF% %MODULE_NAME%_Impl %BSW_REF% 
"%MCAL_GEN_EXEC%" %ROOT_DESC% Mcu ActiveEcuC %CONF_PATH% -o "%GEN_FOLDER%" -ref Mcu_Impl %REF_DESC%

::Move generated files to destination path
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cbk.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cfg.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_PBcfg.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.c" "%DEST_FOLDER%\src"

echo.
EXIT /B %errorlevel%

::Generate file for WDG module
:Wdg_Module
@echo off
rem "%MCAL_GEN_EXEC%" %ROOT_DESC% %MODULE_NAME%0 %AR-PACKAGE-NAME% "%TEMPLATE_PATH%" -o "%GEN_FOLDER%" -ref Dem0 %DEM_REF% Mcu0 %MCU_REF% %MODULE_NAME%_Impl %BSW_REF%
"%MCAL_GEN_EXEC%" %ROOT_DESC% Wdg ActiveEcuC %CONF_PATH% -o "%GEN_FOLDER%" -ref Wdg_Impl %REF_DESC%

::Move generated files to destination path
MOVE "%GEN_FOLDER%\%MODULE_NAME%_59_DriverA_Cbk.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_59_DriverA_Cfg.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_59_Hardware.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_59_DriverA_PBcfg.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_59_Hardware.c" "%DEST_FOLDER%\src"

echo.
EXIT /B %errorlevel%

::Generate file for DIO module
:Dio_Module
@echo off
rem "%MCAL_GEN_EXEC%" %ROOT_DESC% %MODULE_NAME%0 %AR-PACKAGE-NAME% "%TEMPLATE_PATH%" -o "%GEN_FOLDER%" -ref %MODULE_NAME%_Impl %BSW_REF% 
"%MCAL_GEN_EXEC%" %ROOT_DESC% Dio ActiveEcuC %CONF_PATH% -o "%GEN_FOLDER%" -ref Dio_Impl %REF_DESC%

::Move generated files to destination path
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cfg.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cbk.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_PBcfg.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Lcfg.c" "%DEST_FOLDER%\src"

echo.
EXIT /B %errorlevel%

:Spi_Module
@echo off
rem "%MCAL_GEN_EXEC%" %ROOT_DESC% %MODULE_NAME%0 %AR-PACKAGE-NAME% "%TEMPLATE_PATH%" -o "%GEN_FOLDER%" -ref Dem0 %DEM_REF% %MODULE_NAME%_Impl %BSW_REF% 
"%MCAL_GEN_EXEC%" %ROOT_DESC% Spi ActiveEcuC %CONF_PATH% -o "%GEN_FOLDER%" -ref Spi_Impl %REF_DESC%

::Move generated files to destination path
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cfg.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cbk.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_PBcfg.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Lcfg.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.c" "%DEST_FOLDER%\src"

echo.
EXIT /B %errorlevel%

::Generate file for Gpt module
:Gpt_Module
@echo off
rem "%MCAL_GEN_EXEC%" %ROOT_DESC% %MODULE_NAME%0 %AR-PACKAGE-NAME% "%TEMPLATE_PATH%" -o "%GEN_FOLDER%" -ref Dem0 %DEM_REF% %MODULE_NAME%_Impl %BSW_REF% 
"%MCAL_GEN_EXEC%" %ROOT_DESC% Gpt ActiveEcuC %CONF_PATH% -o "%GEN_FOLDER%" -ref Gpt_Impl %REF_DESC%

::Move generated files to destination path
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cfg.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cbk.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_PBcfg.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.c" "%DEST_FOLDER%\src"

echo.
EXIT /B %errorlevel%

::Generate file for Icu module
:Icu_Module
@echo off
rem "%MCAL_GEN_EXEC%" %ROOT_DESC% %MODULE_NAME%0 %AR-PACKAGE-NAME% "%TEMPLATE_PATH%" -o "%GEN_FOLDER%" -ref Dem0 %DEM_REF% %MODULE_NAME%_Impl %BSW_REF% 
"%MCAL_GEN_EXEC%" %ROOT_DESC% Icu ActiveEcuC %CONF_PATH% -o "%GEN_FOLDER%" -ref Icu_Impl %REF_DESC%

::Move generated files to destination path
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cfg.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cbk.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_PBcfg.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.c" "%DEST_FOLDER%\src"

echo.
EXIT /B %errorlevel%

::Generate file for Fls module
:Fls_Module
@echo off
rem "%MCAL_GEN_EXEC%" %ROOT_DESC% %MODULE_NAME%0 %AR-PACKAGE-NAME% "%TEMPLATE_PATH%" -o "%GEN_FOLDER%" -ref Dem0 %DEM_REF% Mcu %MCU_REF% %MODULE_NAME%_Impl %BSW_REF% 
"%MCAL_GEN_EXEC%" %ROOT_DESC% Fls ActiveEcuC %CONF_PATH% -o "%GEN_FOLDER%" -ref Fls_Impl %REF_DESC%

::Move generated files to destination path
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cfg.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cbk.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_PBcfg.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.c" "%DEST_FOLDER%\src"

echo.
EXIT /B %errorlevel%

::Generate file for Pwm module
:Pwm_Module
@echo off
rem "%MCAL_GEN_EXEC%" %ROOT_DESC% %MODULE_NAME%0 %AR-PACKAGE-NAME% "%TEMPLATE_PATH%" -o "%GEN_FOLDER%" -ref Dem0 %DEM_REF% Mcu %MCU_REF% %MODULE_NAME%_Impl %BSW_REF% 
"%MCAL_GEN_EXEC%" %ROOT_DESC% Pwm ActiveEcuC %CONF_PATH% -o "%GEN_FOLDER%" -ref Pwm_Impl %REF_DESC%

::Move generated files to destination path
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cfg.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Cbk.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.c" "%DEST_FOLDER%\src"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_Hardware.h" "%DEST_FOLDER%\include"
MOVE "%GEN_FOLDER%\%MODULE_NAME%_PBcfg.c" "%DEST_FOLDER%\src"

echo.
EXIT /B %errorlevel%


pause

:Help
@echo off.
Cls
echo Usage:
echo SampleApp.bat Msn Variant Compile_Option
echo.
echo Msn               - Module Short Name to be generated e.g. Port, Can, Adc, All,...
echo.
echo Variant           - Device variant e.g. 701325A, 701327...        
echo.
echo Compile_Option    - clean/build/generate.
echo                     clean for clean
echo                     build for incremental build
echo                     generate for code generation   
echo.           
echo Note: If Compile_Option is left blank, then batch will clean, generate and compile files.            
echo.
goto :END

:End
ENDLOCAL
@ECHO on
