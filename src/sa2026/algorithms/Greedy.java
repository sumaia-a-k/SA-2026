package sa2026.algorithms;

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
 * Greedy Best-First Search.
 *
 * Greedy always expands the node that LOOKS closest to the goal:
 * the node with the smallest guess h(n). So f(n) = h(n).
 *
 * The code is the same as UCS. Only f(n), the number the queue sorts by, is different:
 *   UCS:    f(n) = g(n)   the real cost so far
 *   Greedy: f(n) = h(n)   the guess to the goal
 * We still compute g(n) (pathCost), but only to know the cost of the path at the end.
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

        // the guess h(n) of this problem (throws an error if the problem has no heuristic)
        HeuristicFunction h = p.getHeuristicFunction();

        // PriorityQueue uses Node.compareTo(): the node with the smallest totalCost comes first.
        // Here totalCost = f(n), and we give it to the Node constructor ourselves.
        PriorityQueue<Node> frontier = new PriorityQueue<>();
        Set<State> explored = new HashSet<>(); // HashSet: contains() is fast
        int visitingOrder = 0;

        // the start node: path cost 0, f(n) = h(n)
        State start = p.getInitialState();
        Node startNode = new Node(start, null, null, 0.0, h.getH(start));
        frontier.add(startNode);
        generatedNodes++; // the start node is a generated node too

        while (!frontier.isEmpty()) {
            // take the node with the smallest f(n)
            Node currentNode = frontier.poll();

            // graph search: skip the other copies of a state we already expanded
            if (useGraphSearch && explored.contains(currentNode.getState())) {
                continue;
            }
            currentNode.setVisitingOrder(++visitingOrder);

            // goal test when we take the node out of the queue (like UCS)
            if (p.isGoal(currentNode.getState())) {
                return currentNode;
            }

            if (useGraphSearch) {
                explored.add(currentNode.getState());
            }

            // expand: apply every action and add the children to the priority queue
            nodesActuallyExpanded++;
            for (IAction action : p.getActions()) {
                Collection<State> nextStates = action.apply(currentNode.getState());
                for (State s : nextStates) {
                    // g(n): the real cost from the start
                    double pathCost = currentNode.getPathCost()
                            + p.getActionCost(currentNode.getState(), action, s);
                    // f(n) = h(n): Greedy uses only the guess, not the cost
                    double f = h.getH(s);
                    Node child = new Node(s, currentNode, action, pathCost, f);
                    frontier.add(child); // the queue puts it in the right place (by f)
                    generatedNodes++;
                }
            }
        }

        // the queue is empty and we did not find a goal
        return null;
    }
}
