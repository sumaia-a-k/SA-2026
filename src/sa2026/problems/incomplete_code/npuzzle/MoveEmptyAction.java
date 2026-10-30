package sa2026.problems.incomplete_code.npuzzle;

import java.util.Collection;
import java.util.Collections;

import sa2026.core.IAction;
import sa2026.core.State;

/**
 * STUDENT TASK: finish this class.
 *
 * One action of the N-puzzle: move the EMPTY cell up, down, left or right.
 * It is the same move as "the tile next to it slides the other way",
 * but now there are only 4 actions (not 8 tiles x 4 directions).
 *
 * Like MazeAction: one class, and four objects with different directions (see NpuzzleProblem):
 *   IAction up = new MoveEmptyAction("Move empty up", -1, 0);
 *
 * Search for "TODO" and follow the steps.
 */
public class MoveEmptyAction implements IAction {

    // TODO 1: add three final fields:
    //         name (String), rowChange (int), colChange (int)
    //         They are the change of the EMPTY cell: -1, 0 or +1.


    // TODO 2: write the constructor MoveEmptyAction(String name, int rowChange, int colChange).


    // Moves the empty cell one step. Returns no state if it would go outside the board.
    @Override
    public Collection<State> apply(State s) {
        // TODO 3: cast s to NpuzzleState.
        // TODO 4: find the new row and col of the empty cell:
        //         current.getEmptyRow() + rowChange, current.getEmptyCol() + colChange
        // TODO 5: n = current.getSize(). If the new row or col is outside 0 .. n-1:
        //           return Collections.emptyList()
        //         Else: return Collections.singletonList(current.moveEmptyTo(newRow, newCol))
        //         Question: why is there no wall check here, like in the maze?
        return Collections.emptyList();
    }

    @Override
    public String getName() {
        // TODO 6: return the name.
        return null;
    }
}
