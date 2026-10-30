package sa2026.algorithms;

import java.util.Collection;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

import sa2026.core.IAction;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.core.State;

/**
 * Breadth-First Search (BFS), the standard version.
 *
 * BFS visits the nodes level by level: first depth 0, then depth 1, then depth 2 ...
 * The frontier is a Queue (FIFO): the first node in is the first node out.
 *
 * Tree search:  we do not remember anything, so a state can come back many times.
 * Graph search: we remember the explored states and do not expand them again.
 *
 * BFS is optimal only when all the actions have the same cost.
 */
public class BFS extends SearchAlgorithm {

    // tree search
    public BFS() {
        super(false);
    }

    // true = graph search, false = tree search
    public BFS(boolean useGraphSearch) {
        super(useGraphSearch);
    }

    @Override
    public Node search(Problem p) {
        resetCounters();

        // We create these here and not as fields,
        // so every new search starts with an empty queue.
        Queue<Node> frontier = new LinkedList<>();
        Set<State> explored = new HashSet<>(); // HashSet: contains() is fast
        int visitingOrder = 0;

        Node startNode = new Node(p.getInitialState());
        frontier.add(startNode);
        generatedNodes++; // the start node is a generated node too

        while (!frontier.isEmpty()) {
            // take the oldest node (the first one in the queue)
            Node currentNode = frontier.poll();

            // graph search: the same state can be in the queue more than once,
            // so skip it if we expanded it before
            if (useGraphSearch && explored.contains(currentNode.getState())) {
                continue;
            }
            currentNode.setVisitingOrder(++visitingOrder);

            // goal test when we take the node out of the queue
            if (p.isGoal(currentNode.getState())) {
                return currentNode;
            }

            if (useGraphSearch) {
                explored.add(currentNode.getState());
            }

            // expand: apply every action and add the children to the end of the queue
            nodesActuallyExpanded++;
            for (IAction action : p.getActions()) {
                Collection<State> nextStates = action.apply(currentNode.getState());
                for (State s : nextStates) {
                    double pathCost = currentNode.getPathCost()
                            + p.getActionCost(currentNode.getState(), action, s);
                    Node child = new Node(s, currentNode, action, pathCost);
                    frontier.add(child);
                    generatedNodes++;
                }
            }
        }

        // the queue is empty and we did not find a goal
        return null;
    }
}
