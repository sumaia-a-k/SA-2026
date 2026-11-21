from sa2026.core.heuristic_function import HeuristicFunction
from sa2026.core.state import State
from sa2026.problems.maze.maze_state import MazeState


class ManhattanDistance(HeuristicFunction):
    """
    The Manhattan distance from the player to the goal: |row - goal_row| + |col - goal_col|.

    It is the number of steps when there are no walls. Every step moves one cell,
    up, down, left or right, so we need AT LEAST this number of steps.
    The real path can only be longer (walls), never shorter.
    So this guess is admissible. It is also consistent: one step changes it by 1 at most.
    """

    def get_h(self, s: State) -> float:
        maze = MazeState.maze
        return float(abs(s.row - maze.goal_row) + abs(s.col - maze.goal_col))
