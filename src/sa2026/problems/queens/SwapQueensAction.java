package sa2026.problems.queens;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import sa2026.core.IAction;
import sa2026.core.State;

/**
 * The only action of the 8-queens problem: SWAP two queens.
 * The queen of column i takes the row of the queen of column j, and the other way.
 * After a swap there is still one queen in every row and every column.
 * (Moving ONE queen alone would put two queens in the same row.)
 *
 * Like DriveAction, this one action gives MANY next states:
 * all the pairs i < j: 8 x 7 / 2 = 28 neighbours.
 * The order: swap(0,1), swap(0,2), ..., swap(0,7), swap(1,2), ...
 * (the same order as on the lesson page: 1-2, 1-3, ..., 2-3, ...)
 */
public class SwapQueensAction implements IAction {

    @Override
    public Collection<State> apply(State s) {
        QueensState board = (QueensState) s;
        List<State> nextStates = new ArrayList<>();
        for (int i = 0; i < board.getSize(); i++) {
            for (int j = i + 1; j < board.getSize(); j++) {
                nextStates.add(board.swap(i, j));
            }
        }
        return nextStates;
    }

    @Override
    public String getName() {
        return "Swap two queens";
    }
}
