package sa2026.problems.maze;

import sa2026.core.HeuristicFunction;
import sa2026.core.State;

/**
 * The Manhattan distance from the player to the goal: |row - goalRow| + |col - goalCol|.
 *
 * It is the number of steps when there are no walls. Every step moves one cell,
 * up, down, left or right, so we need AT LEAST this number of steps.
 * The real path can only be longer (walls), never shorter.
 * So this guess is admissible. It is also consistent: one step changes it by 1 at most.
 */
public class ManhattanDistance implements HeuristicFunction {

    @Override
    public double getH(State s) {
        MazeState player = (MazeState) s;
        Maze maze = MazeState.getMaze();
        return Math.abs(player.getRow() - maze.getGoalRow())
                + Math.abs(player.getCol() - maze.getGoalCol());
    }
}
