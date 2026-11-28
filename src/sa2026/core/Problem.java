package sa2026.core;

import java.util.List;
import java.util.Random;

/**
 * A problem says: where we start, what the goal is,
 * which actions we have, and how much each action costs.
 *
 * For each new problem, write a class that extends Problem.
 */
public abstract class Problem {

    // the state where the search starts
    public abstract State getInitialState();

    // true if the state is a goal state
    public abstract boolean isGoal(State state);

    // all the actions of this problem
    public abstract List<IAction> getActions();

    // the cost of going from state s to state next using action a
    public abstract double getActionCost(State s, IAction a, State next);

    /*
     * The heuristic used by Greedy and A*.
     * By default a problem has no heuristic, so this method throws an error.
     * Override it if your problem has a heuristic.
     */
    public HeuristicFunction getHeuristicFunction() {
        throw new UnsupportedOperationException("This problem does not have a heuristic function.");
    }

    /*
     * A random start state, used by RandomRestart.
     * By default a problem can not make one, so this method throws an error.
     * Override it if any state of your problem can be a start (for example 8-queens).
     */
    public State getRandomState(Random random) {
        throw new UnsupportedOperationException("This problem can not make a random start state.");
    }

    // solves this problem with the given algorithm and returns the goal node (or null)
    public Node solve(SearchAlgorithm algorithm) {
        return algorithm.search(this);
    }
}
