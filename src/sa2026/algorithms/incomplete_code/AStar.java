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
 * Check your work with AStarDemo (in this folder).
 *
 * A* Search.
 *
 * A* always expands the node with the smallest f(n) = g(n) + h(n):
 *   g(n) = the real cost from the start to n (we already paid it)
 *   h(n) = a guess of the cost from n to the goal
 *
 * A* is complete (like UCS, when every cost is more than 0).
 * A* is optimal:
 *   tree search  -> if h is admissible
 *   graph search -> if h is consistent
 */
public class AStar extends SearchAlgorithm {

    // tree search
    public AStar() {
        super(false);
    }

    // true = graph search, false = tree search
    public AStar(boolean useGraphSearch) {
        super(useGraphSearch);
    }

    @Override
    public Node search(Problem p) {
        resetCounters();

        // The code is almost the same as your UCS.java (and your Greedy.java).
        // Only f(n), the number the queue sorts by, is different.

        // TODO 1: get the heuristic of the problem:  HeuristicFunction h = p.getHeuristicFunction();
        //         Then, like in UCS: a PriorityQueue<Node> frontier, a Set<State> explored (HashSet)
        //         and int visitingOrder = 0.

        // TODO 2: create the start node with FIVE values:
        //           new Node(start, null, null, 0.0, f)
        //         (start = p.getInitialState()). Add it to the frontier and count it: generatedNodes++
        //         Question: what is f(n) of the start node? (g = 0)

        // TODO 3: while the frontier is not empty:
        //   a) take the node with the smallest f(n):  Node currentNode = frontier.poll();
        //   b) graph search only: if explored contains its state, skip it with "continue".
        //   c) currentNode.setVisitingOrder(++visitingOrder);
        //   d) goal test: if p.isGoal(currentNode.getState()), return currentNode.
        //      Question: why must we test the goal here, and not when we create the child?
        //   e) graph search only: add the state to explored.
        //   f) expand the node: nodesActuallyExpanded++
        //      then for every action and every next state s (like in UCS):
        //        - pathCost = currentNode.getPathCost() + p.getActionCost(currentNode.getState(), action, s)
        //        - double f = pathCost + h.getH(s);   <- the only line that makes it A*
        //        - Node child = new Node(s, currentNode, action, pathCost, f);
        //        - frontier.add(child);  and count it: generatedNodes++
        //   Question: what happens if h.getH(s) is 0 for every state? (AStarDemo has a check for it.)

        // TODO 4: the queue is empty and we did not find a goal: return null.
        //   Question: on the "small map" in AStarDemo, graph search returns a path of 9 km,
        //             but tree search finds 7 km. The guess is admissible. Why is it not enough?
        return null;
    }
}
