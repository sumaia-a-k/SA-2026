@echo off
REM Builds and runs the project on Windows.
REM Usage: run.bat   (in PowerShell: .\run.bat)
REM Works even if the project folder path has spaces.

setlocal EnableExtensions EnableDelayedExpansion

REM Go to the project folder (the folder of this file)
cd /d "%~dp0"

REM 1. Check that the Java compiler (javac) is installed
where javac >nul 2>&1
if errorlevel 1 (
    echo ERROR: javac not found. Install a JDK and add it to PATH.
    exit /b 1
)

REM 2. Make a fresh list of all .java files in src
REM    Each path is put in quotes and uses "/" instead of "\",
REM    so javac can read paths that have spaces.
if not exist "out" mkdir "out"
(for /r "src" %%F in (*.java) do (
    set "file=%%~fF"
    set "file=!file:\=/!"
    echo "!file!"
)) > "out\sources.txt"

REM 3. Compile all files into the out folder
javac -encoding UTF-8 -d "out" @"out/sources.txt"
if errorlevel 1 (
    echo.
    echo Build failed. Fix the errors above.
    exit /b 1
)

REM 4. Run the main class
java -cp "out" sa2026.Main %*

endlocal
