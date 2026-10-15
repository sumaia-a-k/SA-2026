@echo off
REM Builds and runs the project on Windows.
REM Usage: run.bat   (in PowerShell: .\run.bat)

cd /d "%~dp0"

REM 1. Find all .java files in src
if not exist out mkdir out
dir /s /b src\*.java > out\sources.txt

REM 2. Compile them into the out folder
javac -encoding UTF-8 -d out @out\sources.txt
if errorlevel 1 (
    echo.
    echo Build failed. Fix the errors above.
    exit /b 1
)

REM 3. Run the main class
java -cp out sa2026.Main %*
