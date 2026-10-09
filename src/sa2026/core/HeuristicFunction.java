package sa2026.core;

/**
 * A heuristic is a guess of the cost from a state to the goal.
 * It is used by informed algorithms like Greedy and A*.
 */
public interface HeuristicFunction {

    // returns h(n): the guessed cost from state s to the goal
    double getH(State s);
}
