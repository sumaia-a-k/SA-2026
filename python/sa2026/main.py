"""
The start point of the program.
We solve the maze with BFS, then we compare the BFS versions and the DFS versions.
At the end we compare BFS and UCS on a city map where the roads have different lengths.

How to run (inside the SA-2026/python folder):
    python -m sa2026.main
"""
from sa2026.algorithms.bfs import BFS
from sa2026.algorithms.bfs_optimized import BFSOptimized
from sa2026.algorithms.depth_limited_dfs import DepthLimitedDFS
from sa2026.algorithms.dfs import DFS
from sa2026.algorithms.dfs_cycle_check import DFSCycleCheck
from sa2026.algorithms.iterative_deepening import IterativeDeepening
from sa2026.algorithms.ucs import UCS
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.problems.citymap.city_map import CityMap
from sa2026.problems.citymap.city_map_problem import CityMapProblem
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

    # 3. the DFS versions on the same maze (-1 steps = no solution found).
    # No DFS tree search: on this maze it goes around a cycle forever.
    print("\n=== Compare the DFS versions ===")
    print("Version                  Steps  Expanded  Generated")
    compare("DFS, graph search", DFS(True), problem)
    compare("DFS + cycle check", DFSCycleCheck(), problem)
    compare("DLS, limit 10", DepthLimitedDFS(10), problem)
    compare("DLS, limit 9", DepthLimitedDFS(9), problem)
    compare("IDS", IterativeDeepening(), problem)

    # 4. a city map: the roads have different lengths, so fewer steps is not always cheaper
    print("\n=== City map S -> G: BFS vs UCS ===")
    city_map = CityMapProblem("S", "G", CityMap.example())
    print("Version                  Steps   Cost  Expanded  Generated")
    compare_cost("BFS, graph search", BFS(True), city_map)
    compare_cost("UCS, graph search", UCS(True), city_map)
    compare_cost("UCS, tree search", UCS(False), city_map)

    print("\n=== UCS, graph search: the path ===")
    ucs = UCS(True)
    ucs.print_solution(city_map.solve(ucs))


# solves the problem and prints one line of numbers
def compare(name: str, algorithm: SearchAlgorithm, problem: Problem):
    goal = problem.solve(algorithm)
    steps = -1 if goal is None else goal.depth
    # {name:<24} = left side, 24 characters wide;  {steps:5} = right side, 5 characters wide
    print(f"{name:<24} {steps:5} {algorithm.nodes_actually_expanded:9} {algorithm.generated_nodes:10}")


# the same as compare(), with the path cost too ({cost:6.1f} = 6 characters, 1 digit after the point)
def compare_cost(name: str, algorithm: SearchAlgorithm, problem: Problem):
    goal = problem.solve(algorithm)
    steps = -1 if goal is None else goal.depth
    cost = -1 if goal is None else goal.path_cost
    print(f"{name:<24} {steps:5} {cost:6.1f} {algorithm.nodes_actually_expanded:9} {algorithm.generated_nodes:10}")


# run main() only when this file is started, not when another file imports it
if __name__ == "__main__":
    main()
