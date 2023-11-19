@echo off
rem ###############################################################################
rem # File Name  : Script_MCAL_Prepare.bat                                        #
rem # Description: Batch file for Mcal to proceed necessary actions after         #
rem #              installation of the Mcal package                               #
rem #                                                                             #
rem #			   												 				  #
rem #-----------------------------------------------------------------------------#
rem #               C O P Y R I G H T                                             #
rem #-----------------------------------------------------------------------------#
rem # Copyright (c) 2016 by Vector Informatik GmbH.  All rights reserved.         #
rem #                                                                             #
rem #-----------------------------------------------------------------------------#
rem #               A U T H O R   I D E N T I T Y                                 #
rem #-----------------------------------------------------------------------------#
rem # Initials     Name                      Company                              #
rem # --------     ---------------------     -------------------------------------#
rem # Refer to MIPconfig.xml         											  #
rem #-----------------------------------------------------------------------------#
rem #               R E V I S I O N   H I S T O R Y                               #
rem #-----------------------------------------------------------------------------#
rem # Date         Version   Sign     Description                                 #
rem # ----------   -------  ------  ----------------------------------------------#
rem # Refer to MIPconfig.xml         											  #
rem #-----------------------------------------------------------------------------#
rem ###############################################################################

title Script_MCAL_prepare.bat
echo.
echo ***************script by Vector Informatik GmbH***************
echo.

set DERIVATIVE=

if "%1"==""           goto description
if "%1"=="--prepare"  goto prepare
if "%1"=="--undo"     goto undo
if "%1"=="--delivery" goto remove
if "%1"=="--auto" (
  if "%2"=="" (
    echo ERROR: No derivative provided by option --auto, script will exit without any action!
	goto end
  )
  set DERIVATIVE=%2
  goto prepare
)

rem ELSE Description
:description
echo This File starts the so called 3rdPartyMcalIntegrationHelper which prepares the MCAL for further use.
echo.
echo Options:
echo    --prepare: prepares the MCAL for usage. Copies plugins, renames file duplicated, copies BSMWD files, ...
echo    --undo: invert the steps described above
echo    --remove: removes all 
echo    --auto:    prepares the MCAL for usage as prepare but without any user interaction needed. 
echo               Needs as second input parameter the derivative number (file fragment, see MIPconfig.xml)
goto end

:prepare
rem #####################################################################################################
rem # Description of command line options for 3rdPartyMcalIntegrationHelper:
rem #----------------------------------------------------------------------------------------------------
rem # MANDATORY
rem #   - NONE
rem #----------------------------------------------------------------------------------------------------
rem # OPTIONAL
rem #   -f:"<pathToConfigFile>"
rem #      Path to a valid configuration file which shall be used.
rem #      If not specified the default file (ThirdParty\Mcal_XYZ\VectorIntegration\MIPconfig.xml will be used.
rem #   -b:"<pathToThisFile>"
rem #      Complete path of this batch file (including file name)
rem #      Only needed if the tool shall manipulate this file e.g. by writing the variable MIH_EXITCODE (see below).
rem #      Manipulation must be specified in MIPconfig.xml anyway.
rem #   -mode:<Prepare|UndoPrepare|Remove>
rem #      Prepare:     Execute immediately all steps needed to use the MCAL without any user input.
rem #                   This options needs the parameter 'derivative' (see below) if derivative specific actions 
rem #                   must be executed (e.g. copying of BSMWD files)
rem #      UndoPrepare: Invert the steps done during 'prepare' immediately without any user input
rem #      Remove:      Remove the MCAL packages from the SIP immediately without any user input
rem #                   ATTENTION: This actions deletes the configured packages (within MIPconfig.xml) on hard drive!
rem #   -derivative:<FileFragement>
rem #      Use this parameter to specify the BSWMD file name fragment which identifies the derivative you want to use.
rem #      Hint: you may have a look in the file MIPconfig.xml (Bswmd->Derivatives) for possible values.
if "%DERIVATIVE%"=="" (
call ..\..\McalIntegrationHelper\3rdPartyMcalIntegrationHelper.exe -b:"%~dpnx0"
) else (
  call ..\..\McalIntegrationHelper\3rdPartyMcalIntegrationHelper.exe -b:"%~dpnx0" -mode:Prepare -derivative:%DERIVATIVE%
)
rem   MIH_EXITCODE will be set by 3rdPartyMcalIntegrationHelper
rem   0=OK, 1=Cancel, 2=Error (default)
set MIH_EXITCODE=0
goto end

:undo
call ..\..\McalIntegrationHelper\3rdPartyMcalIntegrationHelper.exe -mode:UndoPrepare
goto end

:remove
SET BATCH_FILE_PATH=%~dp0
pushd %BATCH_FILE_PATH%
call ..\..\McalIntegrationHelper\3rdPartyMcalIntegrationHelper.exe -mode:UndoPrepare
call ..\..\McalIntegrationHelper\3rdPartyMcalIntegrationHelper.exe -mode:Remove
goto end


:end

