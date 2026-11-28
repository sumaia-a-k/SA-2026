package sa2026.algorithms;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;
import java.util.Random;

import sa2026.core.HeuristicFunction;
import sa2026.core.IAction;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.core.State;

/**
 * Stochastic Hill Climbing.
 *
 * The same as HillClimbing, but it does not take the BEST neighbour:
 * it takes a RANDOM one of the BETTER neighbours (h(neighbour) < h(current)).
 * Every better neighbour has the same chance.
 * It stops for the same reason: no neighbour is better.
 *
 * It usually needs more moves. Two runs with different seeds can end in different places.
 * The same seed always gives the same result. (Python and C++ have other random makers,
 * so there the same seed can give another result.)
 */
public class StochasticHillClimbing extends SearchAlgorithm {

    private final long seed;
    private Node stuckNode; // where the last search stopped, when it did not find a goal

    public StochasticHillClimbing(long seed) {
        this.seed = seed;
    }

    // the node where the last search stopped without a goal (null after a success)
    public Node getStuckNode() {
        return stuckNode;
    }

    @Override
    public Node search(Problem p) {
        resetCounters();
        stuckNode = null;
        // a new search with the same seed makes the same random choices again
        Random random = new Random(seed);
        HeuristicFunction h = p.getHeuristicFunction();
        int visitingOrder = 0;

        State start = p.getInitialState();
        Node current = new Node(start, null, null, 0.0, h.getH(start));
        generatedNodes++;

        while (true) {
            current.setVisitingOrder(++visitingOrder);
            if (p.isGoal(current.getState())) {
                return current;
            }

            // keep ALL the better neighbours (not only the best one)
            nodesActuallyExpanded++;
            List<Node> better = new ArrayList<>();
            for (IAction action : p.getActions()) {
                Collection<State> nextStates = action.apply(current.getState());
                for (State s : nextStates) {
                    double pathCost = current.getPathCost()
                            + p.getActionCost(current.getState(), action, s);
                    Node child = new Node(s, current, action, pathCost, h.getH(s));
                    generatedNodes++;
                    if (child.getTotalCost() < current.getTotalCost()) {
                        better.add(child);
                    }
                }
            }

            // no neighbour is better: stop, we are stuck
            if (better.isEmpty()) {
                stuckNode = current;
                return null;
            }
            // take a random one of the better neighbours
            current = better.get(random.nextInt(better.size()));
        }
    }
}
