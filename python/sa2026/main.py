"""
The start point of the program.
We solve the maze with BFS, then we compare the BFS versions.

How to run (inside the SA-2026/python folder):
    python -m sa2026.main
"""
from sa2026.algorithms.bfs import BFS
from sa2026.algorithms.bfs_optimized import BFSOptimized
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.problems.maze.maze import Maze
from sa2026.problems.maze.maze_problem import MazeProblem


def main():
    maze = Maze.from_lines(
        "S.#....",
        ".##.##.",
        "....#..",
        ".##....",
        "...#.#G")
    problem = MazeProblem(maze)

    # 1. solve the maze with BFS (graph search) and print every step
    print("=== BFS, graph search ===")
    algorithm = BFS(True)
    goal = problem.solve(algorithm)
    algorithm.print_solution(goal)

    # 2. the same maze with every version, to compare the numbers
    print("\n=== Compare the BFS versions ===")
    print("Version                  Steps  Expanded  Generated")
    compare("BFS, tree search", BFS(False), problem)
    compare("BFS, graph search", BFS(True), problem)
    compare("BFSOptimized, graph", BFSOptimized(True), problem)


# solves the problem and prints one line of numbers
def compare(name: str, algorithm: SearchAlgorithm, problem: Problem):
    goal = problem.solve(algorithm)
    steps = -1 if goal is None else goal.depth
    # {name:<24} = left side, 24 characters wide;  {steps:5} = right side, 5 characters wide
    print(f"{name:<24} {steps:5} {algorithm.nodes_actually_expanded:9} {algorithm.generated_nodes:10}")


# run main() only when this file is started, not when another file imports it
if __name__ == "__main__":
    main()
