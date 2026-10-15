# SA-2026 – Intelligent Search Algorithms

This repository holds the code for the **Intelligent Search Algorithms** course at **Latakia University**, academic year 2026.

The code is added step by step, one session at a time.

## What you will learn

- How to describe a problem as states and actions.
- Uninformed search: BFS, DFS, Depth-Limited DFS, Uniform Cost Search.
- Informed search: Greedy Best-First Search and A*.
- How to design and use heuristic functions.

## How to run

You need a **JDK** (version 8 or newer, we suggest 21).

### What are `run.bat` and `run.sh`?

They are two small scripts that build and run the project for you, so you do not need to type long `javac` commands.
They do the same job. Only the terminal is different:

| Script | Use it in |
|---|---|
| `run.bat` | Windows: Command Prompt or PowerShell |
| `run.sh` | Git Bash, macOS or Linux |

Each script does three steps:

1. Finds all `.java` files in `src` and writes their list to `out/sources.txt`.
2. Compiles them with `javac` into the `out` folder (the `.class` files go there).
3. Runs the main class `sa2026.Main`.

If the code has an error, the script stops at step 2 and prints `Build failed`.

### How to run them

Open a terminal **inside the `SA-2026` folder** (the folder with `run.bat` in it), then:

**Windows:**

```
.\run.bat
```

**Git Bash, macOS or Linux:**

```
./run.sh
```

On macOS or Linux, if you get `Permission denied`, use `bash run.sh`, or run `chmod +x run.sh` once.

### Run another main class (for example a demo)

The scripts always run `sa2026.Main`. To run another class, first run the script to compile, then:

```
java -cp out sa2026.problems.maze.MazeDemo
```

`-cp out` tells Java: "look for the classes in the `out` folder".
Run the script again after every change, or Java runs the old code.

### Common error

```
Error: Could not find or load main class ...
```

You are in the wrong folder (Java can not find `out`), or you did not compile yet.
Go into the `SA-2026` folder and run the script first.

### VS Code

You can also open the `SA-2026` folder in **VS Code** (with the *Extension Pack for Java*) and click **Run** above `main`.

## Course sessions

Each session will have its own folder with code and notes. The list will grow during the semester.
