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
 * DFS tree search with a cycle check (also called "path check").
 *
 * A cycle is ONE path that comes back to a state that is already on it,
 * for example S -> A -> S. Tree search DFS can go around a cycle forever.
 *
 * Graph search stops cycles with an explored set, but that set keeps EVERY state
 * we expanded (a lot of memory). Here we only look at the path of the node:
 * node -> parent -> parent ... -> start. We do not push a child whose state is on it.
 *
 * Good:  every cycle is stopped, and we need no new memory (the parents are already there).
 * Bad:   the same state can still come again on a DIFFERENT path, so we can do more work.
 *        And in an INFINITE state space DFS can still go down forever (use DepthLimitedDFS).
 */
public class DFSCycleCheck extends SearchAlgorithm {

    public DFSCycleCheck() {
        super(false); // tree search with a cycle check
    }

    @Override
    public Node search(Problem p) {
        resetCounters();

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

            nodesActuallyExpanded++;
            for (IAction action : p.getActions()) {
                Collection<State> nextStates = action.apply(currentNode.getState());
                for (State s : nextStates) {
                    // the change: s is already on our path, so it is a cycle
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
