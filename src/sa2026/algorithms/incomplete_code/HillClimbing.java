package sa2026.algorithms.incomplete_code;

import java.util.Collection;

import sa2026.core.HeuristicFunction;
import sa2026.core.IAction;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.core.State;

/**
 * STUDENT TASK: write the body of climb().
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with HillClimbingDemo (in this folder).
 *
 * Hill Climbing (steepest): a local search.
 *
 * It keeps only ONE state: the current one. No frontier, no explored set.
 * At every step it looks at ALL the neighbours, takes the best one (the smallest h),
 * and moves there ONLY IF it is better: h(best) < h(current).
 * If no neighbour is better, it stops. Same h: the first neighbour wins.
 *
 * search() returns the goal node, or null when it is stuck.
 * Then getStuckNode() gives the state where it stopped.
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

    // one climb from the state "start"
    public Node climb(Problem p, State start) {
        stuckNode = null;

        // TODO 1: get the heuristic: HeuristicFunction h = p.getHeuristicFunction();
        //         and int visitingOrder = 0.
        //         Question: Hill Climbing has no frontier and no explored set. What does it keep?

        // TODO 2: create the current node with FIVE values (like in Greedy):
        //           Node current = new Node(start, null, null, 0.0, h.getH(start));
        //         and count it: generatedNodes++

        // TODO 3: while (true):
        //   a) current.setVisitingOrder(++visitingOrder);
        //   b) goal test: if p.isGoal(current.getState()), return current.
        //   c) look at ALL the neighbours: nodesActuallyExpanded++
        //      Node best = null;
        //      for every action and every next state s (like in Greedy):
        //        - pathCost = current.getPathCost() + p.getActionCost(current.getState(), action, s)
        //        - Node child = new Node(s, current, action, pathCost, h.getH(s));
        //        - count it: generatedNodes++
        //        - keep the best one: if best == null or child.getTotalCost() < best.getTotalCost(), best = child
        //          Question: why "<" and not "<="? Which neighbour wins when two have the same h?
        //   d) stop if no neighbour is better:
        //        if best == null or best.getTotalCost() >= current.getTotalCost():
        //            stuckNode = current;  return null;
        //      Question: why ">=" and not ">"? What happens on a flat place if we use ">"?
        //   e) move: current = best;
        //   Question: run HillClimbingDemo. Why is it stuck at C with the misleading guess,
        //             although the path S -> B -> E -> G exists?

        return null; // remove this line when you write TODO 3 (the loop returns by itself)
    }
}
