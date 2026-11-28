package sa2026.algorithms;

import java.util.Random;

import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.core.State;

/**
 * Random-restart Hill Climbing.
 *
 * When Hill Climbing is stuck, start again from a NEW RANDOM state.
 * Repeat until we find a goal, or until we have done maxClimbs climbs.
 * (maxClimbs is a limit, so the search always stops.)
 *
 * The problem must be able to make a random start state (Problem.getRandomState),
 * for example 8-queens. On the city map the start is always S, so it does not help there.
 *
 * The counters (generated, expanded) count ALL the climbs together.
 * The same seed always gives the same random boards.
 */
public class RandomRestart extends SearchAlgorithm {

    private final int maxClimbs;
    private final long seed;
    private int climbs; // how many climbs the last search did

    public RandomRestart(int maxClimbs, long seed) {
        if (maxClimbs < 1) {
            throw new IllegalArgumentException("maxClimbs must be 1 or more, not " + maxClimbs + ".");
        }
        this.maxClimbs = maxClimbs;
        this.seed = seed;
    }

    // how many climbs the last search did
    public int getClimbs() {
        return climbs;
    }

    @Override
    public Node search(Problem p) {
        resetCounters();
        climbs = 0;
        Random random = new Random(seed);
        HillClimbing hill = new HillClimbing(); // its counters start at 0

        Node goal = null;
        while (climbs < maxClimbs && goal == null) {
            State start = p.getRandomState(random);
            goal = hill.climb(p, start);
            climbs++;
        }

        // the numbers of all the climbs together
        generatedNodes = hill.getGeneratedNodes();
        nodesActuallyExpanded = hill.getNodesActuallyExpanded();
        return goal; // null: no goal after maxClimbs climbs
    }
}
