package sa2026.problems.maze;

import java.util.ArrayList;
import java.util.List;

import sa2026.core.IAction;
import sa2026.core.Problem;
import sa2026.core.State;

/**
 * The maze problem: move the player from the start cell to the goal cell.
 *
 * Initial state: the player is on 'S'.
 * Goal:          the player is on 'G'.
 * Actions:       move up, down, left, right (one cell, not into a wall).
 * Cost:          every move costs 1.
 *
 * There is no heuristic yet. We add it in a later session.
 */
public class MazeProblem extends Problem {

    private final State initialState;
    private final List<IAction> actions = new ArrayList<>();

    public MazeProblem(Maze maze) {
        MazeState.setMaze(maze); // all states share this one maze
        initialState = new MazeState(maze.getStartRow(), maze.getStartCol());

        // the order of this list is the order the algorithms try the actions
        actions.add(new MazeAction("Move up", -1, 0));
        actions.add(new MazeAction("Move down", 1, 0));
        actions.add(new MazeAction("Move left", 0, -1));
        actions.add(new MazeAction("Move right", 0, 1));
    }

    @Override
    public State getInitialState() {
        return initialState;
    }

    @Override
    public boolean isGoal(State state) {
        return state.isGoal();
    }

    @Override
    public List<IAction> getActions() {
        return actions;
    }

    // every step costs the same
    @Override
    public double getActionCost(State s, IAction a, State next) {
        return 1;
    }
}
