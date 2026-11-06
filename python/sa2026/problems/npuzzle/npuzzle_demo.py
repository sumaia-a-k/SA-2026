"""
A small demo of the N-puzzle problem.
We check that the state, the actions and the goal test work,
and at the end we let BFS solve one board.

How to run (inside the SA-2026/python folder, NOT its parent folder):
    python -m sa2026.problems.npuzzle.npuzzle_demo
There is no compile step: Python always runs the newest code.
"""
from sa2026.algorithms.bfs import BFS
from sa2026.core.problem import Problem
from sa2026.core.state import State
from sa2026.problems.npuzzle.npuzzle_problem import NpuzzleProblem


def main():
    problem = NpuzzleProblem.medium()
    start = problem.get_initial_state()

    print("=== Initial state (the medium test) ===")
    print(start)
    print(f"Is it a goal? {problem.is_goal(start)}")

    # try every action on the initial state (the empty cell is in a corner)
    print("\n=== Try each action on the initial state ===")
    for action in problem.get_actions():
        result = action.apply(start)
        if not result:
            print(f"{action.get_name()}: not allowed\n")
        else:
            print(f"{action.get_name()}: allowed")
            print(result[0])

    # walk by hand: the easy test needs 2 moves
    print("=== Walk by hand: the easy test ===")
    easy = NpuzzleProblem.easy()
    current = easy.get_initial_state()
    print(current)
    for step in ["Move empty right", "Move empty down"]:
        current = apply_by_name(easy, current, step)
        if current is None:
            print(f'Stopped: "{step}" is not allowed here.')
            return
        print(f"{step}:")
        print(current)
    print(f"Is it a goal? {easy.is_goal(current)}")

    # only half of all boards can be solved
    print("\n=== Can these boards be solved? ===")
    boards = [[1, 2, 3, 4, 5, 6, 7, 0, 8], [1, 2, 3, 4, 5, 6, 8, 7, 0]]
    for board in boards:
        print(f"{board}: {NpuzzleProblem.is_solvable(board)}")
    try:
        NpuzzleProblem(1, 2, 3, 4, 5, 6, 8, 7, 0)
    except ValueError as e:
        print(f"NpuzzleProblem(...) says: {e}")

    # now a search algorithm can solve it
    print("\n=== BFS (graph search) solves the medium test ===")
    bfs = BFS(True)
    goal = problem.solve(bfs)
    moves = [node.action.get_name() for node in goal.get_path_from_root() if node.action is not None]
    print("Moves: " + ", ".join(moves))
    print(f"Steps: {goal.depth}, expanded: {bfs.nodes_actually_expanded}, generated: {bfs.generated_nodes}")


# finds the action with this name and applies it on the state
def apply_by_name(problem: Problem, state: State, name: str) -> State | None:
    for action in problem.get_actions():
        if action.get_name() == name:
            result = action.apply(state)
            return result[0] if result else None
    return None


# run main() only when this file is started, not when another file imports it
if __name__ == "__main__":
    main()
