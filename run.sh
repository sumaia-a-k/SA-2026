#!/usr/bin/env bash
# Builds and runs the project (Git Bash, macOS, Linux).
# Usage: ./run.sh   (or: bash run.sh)

cd "$(dirname "$0")" || exit 1

# 1. Find all .java files in src
mkdir -p out
find src -name "*.java" > out/sources.txt

# 2. Compile them into the out folder
if ! javac -encoding UTF-8 -d out @out/sources.txt; then
    echo
    echo "Build failed. Fix the errors above."
    exit 1
fi

# 3. Run the main class
java -cp out sa2026.Main "$@"
