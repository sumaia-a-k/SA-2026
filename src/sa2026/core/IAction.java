package sa2026.core;

import java.util.Collection;

/**
 * An action is a move that changes one state to another.
 * Example: in a maze, MoveUp moves the player one cell up.
 */
public interface IAction {

    /*
     * Applies the action on state s and returns the new states.
     * If the action is not allowed (for example a wall), return an empty collection.
     */
    Collection<State> apply(State s);

    // the action name, for example "Move up"
    String getName();
}
