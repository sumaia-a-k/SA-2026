#!/usr/bin/env bash
# Builds and runs the C++ project (Git Bash, macOS, Linux).
# Usage: ./run.sh [program]   (or: bash run.sh [program])
#   ./run.sh                                 runs sa2026.Main
#   ./run.sh sa2026.problems.maze.MazeDemo   runs the maze demo

cd "$(dirname "$0")" || exit 1

# 1. Find the file of the program:
#    sa2026.problems.maze.MazeDemo  ->  src/sa2026/problems/maze/MazeDemo.cpp
program="${1:-sa2026.Main}"
mainFile="src/${program//.//}.cpp"
if [ ! -f "$mainFile" ]; then
    echo "ERROR: $mainFile not found. Check the program name."
    exit 1
fi

# 2. Make the file out/all.cpp with one #include line for every .cpp file in src,
#    but NOT the files with a main() function (Main.cpp and the *Demo.cpp files),
#    because a program can have only one main(). At the end we add the program file.
#    Then g++ compiles ONE file, not 20: this is about 10 times faster.
#    The error messages still show the real file and line, for example src/sa2026/core/Node.cpp:12
mkdir -p out
{ (cd src && find . -name "*.cpp" ! -name "Main.cpp" ! -name "*Demo.cpp" | sort | sed 's|^\./|src/|'); echo "$mainFile"; } > out/files.txt
sed 's|^src/\(.*\)$|#include "\1"|' out/files.txt > out/all.cpp

# 3. Compile out/all.cpp into one program in the out folder
#    -std=c++17  use the C++17 version of the language
#    -Wall       show the common warnings
#    -I src      look for the #include files in the src folder
#    On Windows (Git Bash) we also add -static, so the .exe runs without extra DLL files.
flags="-std=c++17 -Wall -I src"
case "$(uname -s)" in
    MINGW* | MSYS* | CYGWIN*) flags="$flags -static" ;;
esac
if ! g++ $flags out/all.cpp -o "out/$program" 2> out/errors.txt; then
    # If a file is broken at its end (for example a missing "}"), g++ can show the error
    # in the NEXT file of all.cpp. So we check the files one by one (in the same order)
    # and show the errors of the first broken file.
    while read -r file; do
        if ! g++ -std=c++17 -Wall -I src -fsyntax-only "$file" 2> out/errors_one.txt; then
            cat out/errors_one.txt
            echo
            echo "Build failed. Fix the errors above."
            exit 1
        fi
    done < out/files.txt
    # Every file is OK alone, so the error comes from linking (for example "undefined reference").
    cat out/errors.txt
    echo
    echo "Build failed. Fix the errors above."
    exit 1
fi
cat out/errors.txt  # the warnings, if there are any

# 4. Run the program
"./out/$program"
