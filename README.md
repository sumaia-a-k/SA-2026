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
They do the same job. **Choose the script by your terminal, not by your computer:**

| Your terminal | Script to use | Command |
|---|---|---|
| Windows **Command Prompt** (cmd) | `run.bat` | `run.bat` |
| Windows **PowerShell** (also the default VS Code terminal on Windows) | `run.bat` | `.\run.bat` |
| **Git Bash** (on Windows) | `run.sh` | `./run.sh` |
| **Linux** or **macOS** terminal | `run.sh` | `./run.sh` |

> Git Bash runs on Windows, but it is a Linux-style terminal. So in Git Bash use `run.sh`, not `run.bat`.

**Not sure which terminal you have?** Look at the prompt:

| The prompt looks like | Your terminal | Use |
|---|---|---|
| `PS D:\uni\SA-2026>` | PowerShell | `.\run.bat` |
| `D:\uni\SA-2026>` | Command Prompt | `run.bat` |
| `user@PC MINGW64 /d/uni/SA-2026 $` | Git Bash | `./run.sh` |
| `user@pc:~/SA-2026$` | Linux / macOS | `./run.sh` |

Both scripts do the same steps:

1. Find all `.java` files in `src` and write their list to `out/sources.txt`.
2. Compile them with `javac` into the `out` folder (the `.class` files go there).
3. Run the main class `sa2026.Main`.

If the code has an error, the script stops at step 2 and prints `Build failed`.
`run.bat` also checks first that `javac` is installed. It works even if your folder path has spaces.

### How to run them

Open a terminal **inside the `SA-2026` folder** (the folder with `run.bat` and `run.sh` in it), then type the command from the table above.

On Git Bash, macOS or Linux, if you get `Permission denied`, use `bash run.sh`, or run `chmod +x run.sh` once.

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
