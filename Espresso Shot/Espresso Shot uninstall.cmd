@echo off
:: This code is almost entirely not mine, it is heavily inspired by UNINSTALL.cmd from https://github.com/EmilianC/Jewel3D - please check out Jewel3D!
:: Check for permissions.
net session >nul 2>&1
if %ERRORLEVEL% NEQ 0 (
    ECHO Espresso Shot Uninstall.cmd must be run as admin.
    Pause
    Exit
)

ECHO Removing Environment Variable...
set EspressoShotPath=
ECHO Done!
ECHO.

ECHO Removing Template Project...
del "%USERPROFILE%\Documents\Visual Studio 2019\Templates\ProjectTemplates\Espresso Game.zip" > nul
ECHO Done!
ECHO.

ECHO IMPORTANT: You may need to restart your PC in order for the environment variable to be set properly!
Pause