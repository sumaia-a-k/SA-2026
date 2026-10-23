@echo off
REM Builds and runs the C++ project on Windows.
REM Usage: run.bat [program]   (in PowerShell: .\run.bat [program])
REM   run.bat                                  runs sa2026.Main
REM   run.bat sa2026.problems.maze.MazeDemo    runs the maze demo
REM Works even if the project folder path has spaces.

setlocal EnableExtensions EnableDelayedExpansion

REM Go to the project folder (the folder of this file)
cd /d "%~dp0"

REM 1. Check that the C++ compiler (g++) is installed
where g++ >nul 2>&1
if errorlevel 1 (
    echo ERROR: g++ not found. Install MinGW-w64 GCC and add it to PATH. See README.md.
    exit /b 1
)

REM 2. Find the file of the program:
REM    sa2026.problems.maze.MazeDemo  ->  src\sa2026\problems\maze\MazeDemo.cpp
set "program=%~1"
if "%program%"=="" set "program=sa2026.Main"
set "mainFile=src\%program:.=\%.cpp"
if not exist "%mainFile%" (
    echo ERROR: %mainFile% not found. Check the program name.
    exit /b 1
)

REM 3. Make the file out\all.cpp with one #include line for every .cpp file in src,
REM    but NOT the files with a main() function (Main.cpp and the *Demo.cpp files),
REM    because a program can have only one main(). At the end we add the program file.
REM    Then g++ compiles ONE file, not 20: this is about 10 times faster.
REM    The error messages still show the real file and line, for example src/sa2026/core/Node.cpp:12
if not exist "out" mkdir "out"
set "srcFolder=%CD%\src\"
(for /r "src" %%F in (*.cpp) do (
    set "name=%%~nF"
    set "isProgram=no"
    if "!name!"=="Main" set "isProgram=yes"
    if "!name:~-4!"=="Demo" set "isProgram=yes"
    if "!isProgram!"=="no" (
        set "file=%%~fF"
        set "file=!file:%srcFolder%=!"
        echo src/!file:\=/!
    )
)
set "file=%mainFile:\=/%"
echo !file!
) > "out\files.txt"
(for /f "usebackq delims=" %%L in ("out\files.txt") do (
    set "file=%%L"
    echo #include "!file:~4!"
)) > "out\all.cpp"

REM 4. Compile out\all.cpp into one .exe in the out folder
REM    -std=c++17  use the C++17 version of the language
REM    -Wall       show the common warnings
REM    -I src      look for the #include files in the src folder
REM    -static     put the C++ library inside the .exe, so it runs without extra DLL files
g++ -std=c++17 -Wall -static -I src "out\all.cpp" -o "out\%program%.exe" 2> "out\errors.txt"
if errorlevel 1 (
    REM If a file is broken at its end (for example a missing "}"), g++ can show the error
    REM in the NEXT file of all.cpp. So we check the files one by one (in the same order)
    REM and show the errors of the first broken file.
    for /f "usebackq delims=" %%L in ("out\files.txt") do (
        g++ -std=c++17 -Wall -I src -fsyntax-only "%%L" 2> "out\errors_one.txt"
        if errorlevel 1 (
            type "out\errors_one.txt"
            echo.
            echo Build failed. Fix the errors above.
            exit /b 1
        )
    )
    REM Every file is OK alone, so the error comes from linking (for example "undefined reference").
    type "out\errors.txt"
    echo.
    echo Build failed. Fix the errors above.
    exit /b 1
)
REM show the warnings, if there are any
type "out\errors.txt"

REM 5. Run the program
"out\%program%.exe"

endlocal
