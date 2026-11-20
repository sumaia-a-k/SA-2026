package sa2026.algorithms.incomplete_code;

import java.util.Collection;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Set;

import sa2026.core.HeuristicFunction;
import sa2026.core.IAction;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.core.State;

/**
 * STUDENT TASK: write the body of search().
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with GreedyDemo (in this folder).
 *
 * Greedy Best-First Search.
 *
 * Greedy always expands the node that LOOKS closest to the goal:
 * the node with the smallest guess h(n). So f(n) = h(n).
 *
 * Tree search:  can go around a loop forever, even with a good heuristic.
 * Graph search: complete (when the number of states is finite).
 *
 * Greedy is NOT optimal, with any heuristic. It is often fast.
 */
public class Greedy extends SearchAlgorithm {

    // tree search
    public Greedy() {
        super(false);
    }

    // true = graph search, false = tree search
    public Greedy(boolean useGraphSearch) {
        super(useGraphSearch);
    }

    @Override
    public Node search(Problem p) {
        resetCounters();

        // The code is almost the same as your UCS.java. Only f(n), the number the queue sorts by, is different.

        // TODO 1: get the heuristic of the problem:  HeuristicFunction h = p.getHeuristicFunction();
        //         Then, like in UCS: a PriorityQueue<Node> frontier, a Set<State> explored (HashSet)
        //         and int visitingOrder = 0.
        //         Question: the queue sorts the nodes by totalCost (Node.compareTo()).
        //                   For Greedy, what must totalCost be?

        // TODO 2: create the start node with FIVE values:
        //           new Node(start, null, null, 0.0, h.getH(start))
        //         (start = p.getInitialState()). Add it to the frontier and count it: generatedNodes++
        //         Question: UCS used new Node(start). Why is it not enough for Greedy?

        // TODO 3: while the frontier is not empty:
        //   a) take the node with the smallest f(n):  Node currentNode = frontier.poll();
        //   b) graph search only: if explored contains its state, skip it with "continue".
        //   c) currentNode.setVisitingOrder(++visitingOrder);
        //   d) goal test: if p.isGoal(currentNode.getState()), return currentNode.
        //   e) graph search only: add the state to explored.
        //   f) expand the node: nodesActuallyExpanded++
        //      then for every action and every next state s (like in UCS):
        //        - pathCost = currentNode.getPathCost() + p.getActionCost(currentNode.getState(), action, s)
        //          Question: Greedy does not use g(n) to choose. Why do we still compute it?
        //        - double f = h.getH(s);       <- the only line that makes it Greedy
        //        - Node child = new Node(s, currentNode, action, pathCost, f);
        //        - frontier.add(child);  and count it: generatedNodes++
        //   Question: run GreedyDemo. The path on the city map costs 21 km, but 18 km is possible. Why?

        // TODO 4: the queue is empty and we did not find a goal: return null.
        return null;
    }
}
