package sa2026.problems.queens;

import sa2026.core.HeuristicFunction;
import sa2026.core.State;

/**
 * h = the number of pairs of queens on the same diagonal.
 * The goal has h = 0. Smaller is better, so Hill Climbing goes down to 0.
 */
public class DiagonalAttacks implements HeuristicFunction {

    @Override
    public double getH(State s) {
        return ((QueensState) s).countAttackingPairs();
    }
}
