package sa2026.problems.maze;

import java.util.Collection;
import java.util.Collections;

import sa2026.core.IAction;
import sa2026.core.State;

/**
 * One move of the player: up, down, left or right.
 *
 * All four moves work the same way, only the direction is different.
 * So we use one class and give it the direction (rowChange, colChange).
 * From this one class we create four action objects (see MazeProblem):
 *   IAction moveUp    = new MazeAction("Move up",    -1,  0);
 *   IAction moveDown  = new MazeAction("Move down",   1,  0);
 *   IAction moveLeft  = new MazeAction("Move left",   0, -1);
 *   IAction moveRight = new MazeAction("Move right",  0,  1);
 */
public class MazeAction implements IAction {

    private final String name;
    private final int rowChange; // how much the row changes: -1, 0 or +1
    private final int colChange; // how much the column changes: -1, 0 or +1

    public MazeAction(String name, int rowChange, int colChange) {
        this.name = name;
        this.rowChange = rowChange;
        this.colChange = colChange;
    }

    // moves the player one cell; returns no state if the new cell is a wall or outside
    @Override
    public Collection<State> apply(State s) {
        // No instanceof check: MazeProblem only creates MazeState objects.
        // If another state comes here, it is a bug, and the ClassCastException shows it fast.
        MazeState current = (MazeState) s;
        int newRow = current.getRow() + rowChange;
        int newCol = current.getCol() + colChange;

        if (!MazeState.getMaze().isFree(newRow, newCol)) {
            return Collections.emptyList(); // the move is not allowed
        }
        State next = new MazeState(newRow, newCol);

        // singletonList = a small list with exactly one item that can not be changed.
        // A normal list does the same job:
        //   List<State> result = new ArrayList<>();
        //   result.add(next);
        //   return result;
        // The result is a Collection because in other problems one action can give many states.
        return Collections.singletonList(next);
    }

    @Override
    public String getName() {
        return name;
    }
}
