package sa2026.algorithms;

import java.util.Collection;

import sa2026.core.HeuristicFunction;
import sa2026.core.IAction;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.core.State;

/**
 * Hill Climbing (steepest): a local search.
 *
 * It keeps only ONE state: the current one. No frontier, no explored set.
 * At every step it looks at ALL the neighbours, takes the best one (the smallest h),
 * and moves there ONLY IF it is better: h(best) < h(current).
 * If no neighbour is better, it stops. Same h: the first neighbour wins.
 *
 * We minimize h (a distance to the goal, smaller is better).
 *
 * search() returns the goal node, or null when it is stuck (it stopped, but not at a goal).
 * Then getStuckNode() gives the state where it stopped: the best state of this climb.
 *
 * NOT complete (it can get stuck: local minimum, plateau, ridge). NOT optimal.
 * It is NOT tree search and NOT graph search: it has no frontier and no explored set.
 * It needs no explored set: h gets smaller at every move, so it can never come back to an old state.
 */
public class HillClimbing extends SearchAlgorithm {

    private Node stuckNode; // where the last climb stopped, when it did not find a goal

    // no useGraphSearch here: Hill Climbing is not tree search and not graph search
    public HillClimbing() {
    }

    // the node where the last search stopped without a goal (null after a success)
    public Node getStuckNode() {
        return stuckNode;
    }

    @Override
    public Node search(Problem p) {
        resetCounters();
        return climb(p, p.getInitialState());
    }

    /*
     * One climb from the state "start". RandomRestart calls it with random start states.
     * It does not reset the counters, so RandomRestart can count all its climbs together.
     */
    public Node climb(Problem p, State start) {
        stuckNode = null;
        HeuristicFunction h = p.getHeuristicFunction();
        int visitingOrder = 0;

        // the start node: path cost 0, totalCost = h(start)
        Node current = new Node(start, null, null, 0.0, h.getH(start));
        generatedNodes++;

        while (true) {
            current.setVisitingOrder(++visitingOrder);

            // goal test first
            if (p.isGoal(current.getState())) {
                return current;
            }

            // look at ALL the neighbours and keep the best one
            nodesActuallyExpanded++;
            Node best = null;
            for (IAction action : p.getActions()) {
                Collection<State> nextStates = action.apply(current.getState());
                for (State s : nextStates) {
                    double pathCost = current.getPathCost()
                            + p.getActionCost(current.getState(), action, s);
                    Node child = new Node(s, current, action, pathCost, h.getH(s));
                    generatedNodes++;
                    // "<" and not "<=": a later neighbour with the same h does not win
                    if (best == null || child.getTotalCost() < best.getTotalCost()) {
                        best = child;
                    }
                }
            }

            // no neighbour is better (or there is no neighbour): stop, we are stuck
            if (best == null || best.getTotalCost() >= current.getTotalCost()) {
                stuckNode = current;
                return null;
            }
            current = best;
        }
    }
}
