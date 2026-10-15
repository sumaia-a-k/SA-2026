package sa2026.problems.incomplete_code.maze;

import java.util.Collection;
import java.util.Collections;

import sa2026.core.IAction;
import sa2026.core.State;

/**
 * STUDENT TASK: finish this class.
 *
 * One move of the player: up, down, left or right.
 * All four moves work the same way, only the direction is different.
 * So we use ONE class and give it the direction (rowChange, colChange).
 * From this one class we create four action objects (in MazeProblem), for example:
 *   IAction moveUp = new MazeAction("Move up", -1, 0);
 *
 * Search for "TODO" and follow the steps.
 */
public class MazeAction implements IAction {

    // TODO 1: add three final fields:
    //         name (String), rowChange (int), colChange (int)
    //         rowChange and colChange are -1, 0 or +1.
    //         Example: "Move up" -> rowChange = -1, colChange = 0


    // TODO 2: write the constructor MazeAction(String name, int rowChange, int colChange).


    // Moves the player one cell. Returns no state if the new cell is a wall or outside.
    @Override
    public Collection<State> apply(State s) {
        // TODO 3: cast s to MazeState.
        //         No instanceof check is needed: MazeProblem only creates MazeState objects.
        //         Question: what happens if someone passes another kind of state?
        // TODO 4: find the new row and the new col (current position + the changes).
        // TODO 5: ask the maze if the new cell is free. Hint: MazeState.getMaze().isFree(...)
        //         - if NOT free: return Collections.emptyList()
        //         - if free:     create a new MazeState for the new cell
        //                        and return Collections.singletonList(newState)
        //         singletonList = a small list with exactly one item that can not be changed.
        //         A normal ArrayList with one item also works.
        //
        // Important: do NOT change the old state. Always create a new one.
        return Collections.emptyList();
    }

    @Override
    public String getName() {
        // TODO 6: return the name.
        return null;
    }
}
