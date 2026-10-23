"""
A small demo of the maze problem. There is no search algorithm yet.
We only check that the state, the actions and the goal test work.

How to run (inside the SA-2026/python folder, NOT its parent folder):
    python -m sa2026.problems.incomplete_code.maze.maze_demo
There is no compile step: Python always runs the newest code.
"""
from sa2026.core.problem import Problem
from sa2026.core.state import State
from sa2026.problems.incomplete_code.maze.maze import Maze
from sa2026.problems.incomplete_code.maze.maze_problem import MazeProblem


def main():
    maze = Maze.from_lines(
        "S.#....",
        ".##.##.",
        "....#..",
        ".##....",
        "...#.#G")

    problem = MazeProblem(maze)
    start = problem.get_initial_state()

    print("=== Initial state ===")
    print(start)
    print(f"Is it a goal? {problem.is_goal(start)}")

    # try every action on the initial state
    print("\n=== Try each action on the initial state ===")
    for action in problem.get_actions():
        result = action.apply(start)
        if len(result) == 0:
            print(action.get_name() + ": not allowed\n")
        else:
            print(action.get_name() + ": allowed")
            print(result[0])

    # walk by hand to the goal: down 2, right 3, down 1, right 3, down 1
    print("=== Walk by hand to the goal ===")
    path = ["Move down", "Move down",
            "Move right", "Move right", "Move right",
            "Move down",
            "Move right", "Move right", "Move right",
            "Move down"]
    current = start
    for step in path:
        current = apply_by_name(problem, current, step)
        if current is None:
            print(f'Stopped: "{step}" is not allowed here.')
            return
    print(current)
    print(f"Is it a goal? {problem.is_goal(current)}")


# finds the action with this name and applies it on the state
def apply_by_name(problem: Problem, state: State, name: str) -> State | None:
    for action in problem.get_actions():
        if action.get_name() == name:
            result = action.apply(state)
            return None if len(result) == 0 else result[0]
    return None


# run main() only when this file is started, not when another file imports it
if __name__ == "__main__":
    main()
