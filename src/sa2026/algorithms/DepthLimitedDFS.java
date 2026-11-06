package sa2026.algorithms;

import java.util.ArrayDeque;
import java.util.Collection;
import java.util.Deque;

import sa2026.core.IAction;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.core.State;

/**
 * Depth-Limited Search (DLS): DFS with a cycle check and a depth limit.
 *
 * A node at depth = limit is NOT expanded. So DFS can not go down forever.
 *
 * limit < depth of the goal:  no goal is found (returns null).
 * limit = depth of the goal:  a shortest path is found (if all steps cost the same).
 * limit > depth of the goal:  a goal is found, but maybe a long path.
 *
 * When it returns null, isCutoff() tells us why:
 *   true  = a node stopped at the limit: maybe there is a goal deeper.
 *   false = we searched everything: there is no goal at all.
 */
public class DepthLimitedDFS extends SearchAlgorithm {

    private final int limit;  // do not expand nodes at this depth
    private boolean cutoff;   // only a flag: did at least one node stop at the limit? (yes / no)

    public DepthLimitedDFS(int limit) {
        super(false); // tree search with a cycle check
        if (limit < 0) {
            throw new IllegalArgumentException("The limit must be 0 or more, not " + limit + ".");
        }
        this.limit = limit;
    }

    // IDS asks this after the search: true = try a bigger limit, false = no solution
    public boolean isCutoff() {
        return cutoff;
    }

    @Override
    public Node search(Problem p) {
        resetCounters();
        cutoff = false; // a new search: no cutoff yet

        Deque<Node> frontier = new ArrayDeque<>();
        int visitingOrder = 0;

        Node startNode = new Node(p.getInitialState());
        frontier.push(startNode);
        generatedNodes++;

        while (!frontier.isEmpty()) {
            Node currentNode = frontier.pop();
            currentNode.setVisitingOrder(++visitingOrder);

            if (p.isGoal(currentNode.getState())) {
                return currentNode;
            }

            // do not go deeper than the limit
            if (currentNode.getDepth() >= limit) {
                cutoff = true; // remember that it happened, nothing more
                continue;
            }

            nodesActuallyExpanded++;
            for (IAction action : p.getActions()) {
                Collection<State> nextStates = action.apply(currentNode.getState());
                for (State s : nextStates) {
                    // cycle check: do not go back to a state on our own path
                    if (isOnPath(currentNode, s)) {
                        continue;
                    }
                    double pathCost = currentNode.getPathCost()
                            + p.getActionCost(currentNode.getState(), action, s);
                    Node child = new Node(s, currentNode, action, pathCost);
                    frontier.push(child);
                    generatedNodes++;
                }
            }
        }

        return null;
    }

    // true if the state is in this node or in one of its parents
    // static: it does not use any field of the object
    private static boolean isOnPath(Node node, State s) {
        for (Node n = node; n != null; n = n.getParent()) {
            if (n.getState().equals(s)) {
                return true;
            }
        }
        return false;
    }
}
