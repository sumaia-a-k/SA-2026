package sa2026.problems.npuzzle;

import java.util.Collection;
import java.util.Collections;

import sa2026.core.IAction;
import sa2026.core.State;

/**
 * One action of the N-puzzle: move the EMPTY cell up, down, left or right.
 * It is the same move as "the tile next to it slides the other way",
 * but now there are only 4 actions (not 8 tiles x 4 directions).
 *
 * Like MazeAction: one class, and four objects with different directions (see NpuzzleProblem):
 *   IAction up = new MoveEmptyAction("Move empty up", -1, 0);
 * (Better than four classes, MoveEmptyUp, ..., with almost the same code.)
 */
public class MoveEmptyAction implements IAction {

    private final String name;
    private final int rowChange; // how much the row of the empty cell changes: -1, 0 or +1
    private final int colChange; // how much the col of the empty cell changes: -1, 0 or +1

    public MoveEmptyAction(String name, int rowChange, int colChange) {
        this.name = name;
        this.rowChange = rowChange;
        this.colChange = colChange;
    }

    // moves the empty cell one step; returns no state if it would go outside the board
    @Override
    public Collection<State> apply(State s) {
        NpuzzleState current = (NpuzzleState) s;
        int newRow = current.getEmptyRow() + rowChange;
        int newCol = current.getEmptyCol() + colChange;
        int n = current.getSize();

        if (newRow < 0 || newRow >= n || newCol < 0 || newCol >= n) {
            return Collections.emptyList(); // outside the board: the move is not allowed
        }
        return Collections.singletonList(current.moveEmptyTo(newRow, newCol));
    }

    @Override
    public String getName() {
        return name;
    }
}
