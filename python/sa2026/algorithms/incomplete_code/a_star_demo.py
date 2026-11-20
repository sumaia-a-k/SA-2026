"""
Checks YOUR AStar (in this folder) with the finished one (in sa2026.algorithms).
Both solve the same problems. The answers and the numbers must be the same.

How to run (inside the SA-2026/python folder, NOT its parent folder):
    python -m sa2026.algorithms.incomplete_code.a_star_demo
There is no compile step: Python always runs the newest code.

The maps and the guesses are the same as on the lesson pages (heuristics.html, astar.html).
If the program does not stop, your search never ends. Stop it with Ctrl+C.
"""
from sa2026.algorithms import a_star as finished_a_star  # the finished AStar
from sa2026.algorithms.incomplete_code.a_star import AStar  # your AStar
from sa2026.algorithms.ucs import UCS  # the finished UCS
from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.problems.citymap.city_heuristic import CityHeuristic
from sa2026.problems.citymap.city_map import CityMap
from sa2026.problems.citymap.city_map_problem import CityMapProblem
from sa2026.problems.maze.maze import Maze
from sa2026.problems.maze.maze_problem import MazeProblem
from sa2026.problems.npuzzle.misplaced_tiles import MisplacedTiles
from sa2026.problems.npuzzle.npuzzle_problem import NpuzzleProblem


def main():
    # "AStar" is your class (this folder). The finished one is finished_a_star.AStar
    ok = 0

    # the city map with the GPS guess (goal G): admissible and consistent
    city_map = CityMapProblem("S", "G", CityMap.example(), CityHeuristic.gps_guess_to_g())
    ok += check("A*, graph search, city map S -> G", AStar(True), finished_a_star.AStar(True), city_map)
    ok += check("A*, tree search, city map S -> G", AStar(False), finished_a_star.AStar(False), city_map)

    # h = 0 for every city: then f = g, so A* must work exactly like UCS
    no_guess = CityMapProblem("S", "G", CityMap.example(), zero_guess())
    ok += check("A* with h = 0 is the same as UCS", AStar(True), UCS(True), no_guess)

    # the small map: the guess is admissible, but NOT consistent (road B - A).
    # Graph search returns 9 km here (not the cheapest, 7 km). Your A* must do the same.
    small_map = small_map_problem()
    ok += check("A*, graph search, small map", AStar(True), finished_a_star.AStar(True), small_map)
    ok += check("A*, tree search, small map", AStar(False), finished_a_star.AStar(False), small_map)

    # the maze: the heuristic is the Manhattan distance
    maze = MazeProblem(Maze.from_lines(
        "S.#....",
        ".##.##.",
        "....#..",
        ".##....",
        "...#.#G"))
    ok += check("A*, graph search, maze", AStar(True), finished_a_star.AStar(True), maze)

    # a wall closes the way to G: there is no solution
    closed = MazeProblem(Maze.from_lines(
        "S..#...",
        "...#.G.",
        "...#..."))
    ok += check("A*, graph search, no solution", AStar(True), finished_a_star.AStar(True), closed)

    # the 8-puzzle with two heuristics: h2 (Manhattan, the default) and h1 (misplaced tiles)
    puzzle = NpuzzleProblem.hard()
    ok += check("A*, graph search, 8-puzzle, h2", AStar(True), finished_a_star.AStar(True), puzzle)
    puzzle.set_heuristic_function(MisplacedTiles())
    ok += check("A*, graph search, 8-puzzle, h1", AStar(True), finished_a_star.AStar(True), puzzle)

    print(f"\n{ok} of 9 checks are OK.")


# a guess of 0 for every city of the example map
def zero_guess() -> CityHeuristic:
    return CityHeuristic({city: 0 for city in ["S", "A", "B", "C", "D", "E", "F", "G"]})


# the small map of the lesson pages: roads S-A 4, S-B 1, B-A 1, A-G 5
# guesses: h(S) = 4, h(B) = 5, h(A) = 0, h(G) = 0
def small_map_problem() -> Problem:
    small_map = CityMap()
    small_map.add_road("S", "A", 4)
    small_map.add_road("S", "B", 1)
    small_map.add_road("B", "A", 1)
    small_map.add_road("A", "G", 5)
    return CityMapProblem("S", "G", small_map, CityHeuristic({"S": 4, "B": 5, "A": 0, "G": 0}))


# solves the problem with both algorithms and compares the results; returns 1 if they are the same
def check(name: str, yours: SearchAlgorithm, finished: SearchAlgorithm, problem: Problem) -> int:
    # print it first: if your search never ends, you see where.
    # end="" = stay on the same line, flush=True = show it now, not later
    print(f"Checking {name} ... ", end="", flush=True)
    your_goal = problem.solve(yours)
    goal = problem.solve(finished)
    return report(compare(your_goal, goal, yours, finished))


# returns None if the results are the same, or a text that says what is different
def compare(your_goal: Node | None, goal: Node | None,
            yours: SearchAlgorithm, finished: SearchAlgorithm) -> str | None:
    if goal is None and your_goal is not None:
        return "you found a path, but there is no solution here"
    if goal is not None:
        if your_goal is None:
            return "your search returned None (no solution)"
        # the cost first: it shows at once if the path is the cheapest one
        if your_goal.path_cost != goal.path_cost:
            return f"path cost = {your_goal.path_cost}, it should be {goal.path_cost}"
        if not same_path(your_goal, goal):
            return f"your path is not the same: {your_goal.depth} steps, it should be {goal.depth}"
    if yours.nodes_actually_expanded != finished.nodes_actually_expanded:
        return (f"expanded nodes = {yours.nodes_actually_expanded}"
                f", it should be {finished.nodes_actually_expanded}")
    if yours.generated_nodes != finished.generated_nodes:
        return f"generated nodes = {yours.generated_nodes}, it should be {finished.generated_nodes}"
    return None


# prints OK or NOT YET; returns 1 if it is OK
def report(problem_text: str | None) -> int:
    if problem_text is None:
        print("OK")
        return 1
    print(f"NOT YET: {problem_text}")
    return 0


# True if the two paths have the same states, in the same order
def same_path(a: Node, b: Node) -> bool:
    path_a = a.get_path_from_root()
    path_b = b.get_path_from_root()
    if len(path_a) != len(path_b):
        return False
    for i in range(len(path_a)):
        if path_a[i].state != path_b[i].state:
            return False
    return True


# run main() only when this file is started, not when another file imports it
if __name__ == "__main__":
    main()
