@echo off
setlocal EnableExtensions EnableDelayedExpansion

REM Move to the project folder
cd /d "%~dp0"

REM Check Java compiler
where javac >nul 2>&1
if errorlevel 1 (
    echo ERROR: javac not found.
    exit /b 1
)

REM Create output folder
if not exist "out" mkdir "out"

REM Create a fresh list of Java files
if exist "out\sources.txt" del "out\sources.txt"

REM Use forward slashes to handle spaces in paths
(for /r "src" %%F in (*.java) do (
    set "file=%%~fF"
    set "file=!file:\=/!"
    echo "!file!"
)) > "out\sources.txt"

REM Compile all Java files
javac -encoding UTF-8 -d "out" @"out/sources.txt"
if errorlevel 1 (
    echo.
    echo Build failed. Fix the errors above.
    exit /b 1
)

REM Run the main class
java -cp "out" sa2026.Main %*

endlocal