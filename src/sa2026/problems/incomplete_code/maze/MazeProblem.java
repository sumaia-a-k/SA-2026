package sa2026.problems.incomplete_code.maze;

import java.util.ArrayList;
import java.util.List;

import sa2026.core.IAction;
import sa2026.core.Problem;
import sa2026.core.State;

/**
 * STUDENT TASK: finish this class.
 *
 * The maze problem: move the player from the start cell to the goal cell.
 *
 * Initial state: the player is on 'S'.
 * Goal:          the player is on 'G'.
 * Actions:       move up, down, left, right (one cell, not into a wall).
 * Cost:          every move costs 1.
 *
 * There is no heuristic yet. We add it in a later session.
 *
 * Search for "TODO" and follow the steps.
 */
public class MazeProblem extends Problem {

    private final State initialState;
    private final List<IAction> actions = new ArrayList<>();

    public MazeProblem(Maze maze) {
        MazeState.setMaze(maze); // all states share this one maze

        // TODO 1: create the initial state. The player starts on the start cell.
        //         Hint: new MazeState(maze.getStartRow(), maze.getStartCol())
        initialState = null;

        // TODO 2: add the four actions to the list "actions".
        //         Use these names and changes (rowChange, colChange):
        //           "Move up"    (-1,  0)
        //           "Move down"  ( 1,  0)
        //           "Move left"  ( 0, -1)
        //           "Move right" ( 0,  1)
        //         The order of this list is the order the algorithms try the actions.
    }

    @Override
    public State getInitialState() {
        // TODO 3: return the initial state.
        return null;
    }

    @Override
    public boolean isGoal(State state) {
        // TODO 4: ask the state if it is a goal.
        return false;
    }

    @Override
    public List<IAction> getActions() {
        // TODO 5: return the list of actions.
        return null;
    }

    // The cost of going from state s to state next using action a.
    @Override
    public double getActionCost(State s, IAction a, State next) {
        // TODO 6: every step costs the same. Return 1.
        //         Question: what changes if some cells are "mud" and cost 3?
        return 0;
    }
}
