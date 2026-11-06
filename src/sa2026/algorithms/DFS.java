package sa2026.algorithms;

import java.util.ArrayDeque;
import java.util.Collection;
import java.util.Deque;
import java.util.HashSet;
import java.util.Set;

import sa2026.core.IAction;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.core.State;

/**
 * Depth-First Search (DFS), the standard version.
 *
 * DFS always goes deeper first. At a dead end it goes back
 * to the newest node that is still waiting in the stack.
 * The frontier is a Stack (LIFO): the last node in is the first node out.
 *
 * Tree search:  we do not remember anything. In a graph with cycles
 *               DFS can go around a cycle forever!
 * Graph search: we remember the explored states and do not expand them again.
 *
 * DFS is not optimal: the first path it finds can be a long one.
 */
public class DFS extends SearchAlgorithm {

    // tree search
    public DFS() {
        super(false);
    }

    // true = graph search, false = tree search
    public DFS(boolean useGraphSearch) {
        super(useGraphSearch);
    }

    @Override
    public Node search(Problem p) {
        resetCounters();

        // ArrayDeque used as a stack: push() and pop() both work on the top
        Deque<Node> frontier = new ArrayDeque<>();
        Set<State> explored = new HashSet<>(); // HashSet: contains() is fast
        int visitingOrder = 0;

        Node startNode = new Node(p.getInitialState());
        frontier.push(startNode);
        generatedNodes++; // the start node is a generated node too

        while (!frontier.isEmpty()) {
            // take the newest node (the top of the stack)
            Node currentNode = frontier.pop();

            // graph search: the same state can be in the stack more than once,
            // so skip it if we expanded it before
            if (useGraphSearch && explored.contains(currentNode.getState())) {
                continue;
            }

            currentNode.setVisitingOrder(++visitingOrder);

            // goal test when we take the node out of the stack
            if (p.isGoal(currentNode.getState())) {
                return currentNode;
            }

            if (useGraphSearch) {
                explored.add(currentNode.getState());
            }

            // expand: apply every action and push the children on the top.
            // The last child we push is the first one we take.
            nodesActuallyExpanded++;
            for (IAction action : p.getActions()) {
                Collection<State> nextStates = action.apply(currentNode.getState());
                for (State s : nextStates) {
                    double pathCost = currentNode.getPathCost()
                            + p.getActionCost(currentNode.getState(), action, s);
                    Node child = new Node(s, currentNode, action, pathCost);
                    frontier.push(child);
                    generatedNodes++;
                }
            }
        }

        // the stack is empty and we did not find a goal
        return null;
    }
}
