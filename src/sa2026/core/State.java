package sa2026.core;

/**
 * A state is one situation of the problem.
 * Example: in a maze, the state is the player position (row, col).
 *
 * Every problem has its own State class that implements this interface.
 */
public interface State {

    // true if this state is a goal state
    boolean isGoal();

    // how the state is printed on the screen
    @Override
    String toString();

    // two states are equal when they describe the same situation
    @Override
    boolean equals(Object o);

    // must give the same number for equal states
    @Override
    int hashCode();

    /*
     * Note: Java does NOT force you to write toString(), equals() and hashCode(),
     * because every class already gets them from Object.
     * So do not forget to write them in your State class.
     * Without equals() and hashCode(), graph search can not find repeated states.
     */
}
