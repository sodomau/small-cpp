@echo off
setlocal
cd /d "%~dp0"
powershell.exe -NoProfile -ExecutionPolicy Bypass -File "%~dp0tools\package_release.ps1" %*
if errorlevel 1 (
    echo.
    echo Packaging failed.
    pause
    exit /b 1
)
echo.
echo Packaging completed successfully.
pause
