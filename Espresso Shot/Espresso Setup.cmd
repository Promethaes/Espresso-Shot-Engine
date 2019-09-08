@echo off
:: This code is almost entirely not mine, it is heavily inspired by INSTALL.cmd from https://github.com/EmilianC/Jewel3D - please check out Jewel3D!
:: Check for permissions. 
net session >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    ECHO Espresso Setup.cmd must be run as admin.
    Pause
    goto :eof
)

ECHO.
ECHO Installing Espresso Shot...
ECHO.
ECHO Setting Environment Variable...
SETX EspressoShotPath "%~dp0\" -m > nul
ECHO Done!
ECHO.

ECHO Installing Template Project...
XCOPY "%~dp0\Template Game\Espresso Game v. 0.1.zip" "%USERPROFILE%\Documents\Visual Studio 2019\Templates\ProjectTemplates\" /Y /V > nul
ECHO Done!
ECHO.

ECHO IMPORTANT: You may need to restart your PC in order for the environment variable to be set properly!
Pause