package sa2026.algorithms;

import java.util.Collection;
import java.util.HashSet;
import java.util.PriorityQueue;
import java.util.Set;

import sa2026.core.IAction;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.core.State;

/**
 * Uniform-Cost Search (UCS).
 *
 * UCS always expands the CHEAPEST node first: the node with the smallest
 * path cost g(n) (the real cost from the start to the node).
 * The frontier is a PriorityQueue: poll() always gives the node with the smallest cost.
 *
 * The code is the same as BFS. Only the frontier is different:
 *   BFS: a Queue          -> takes the OLDEST node    (fewest steps)
 *   UCS: a PriorityQueue  -> takes the CHEAPEST node  (smallest cost)
 *
 * Tree search:  we do not remember anything, so a state can come back many times.
 * Graph search: we remember the explored states and do not expand them again.
 *
 * UCS is optimal when every action costs more than 0.
 * If all the actions cost the same, UCS expands the nodes like BFS.
 */
public class UCS extends SearchAlgorithm {

    // tree search
    public UCS() {
        super(false);
    }

    // true = graph search, false = tree search
    public UCS(boolean useGraphSearch) {
        super(useGraphSearch);
    }

    @Override
    public Node search(Problem p) {
        resetCounters();

        // PriorityQueue uses Node.compareTo(): the node with the smallest totalCost comes first.
        // For UCS, totalCost = pathCost = g(n) (see the Node constructor).
        PriorityQueue<Node> frontier = new PriorityQueue<>();
        Set<State> explored = new HashSet<>(); // HashSet: contains() is fast
        int visitingOrder = 0;

        Node startNode = new Node(p.getInitialState());
        frontier.add(startNode);
        generatedNodes++; // the start node is a generated node too

        while (!frontier.isEmpty()) {
            // take the cheapest node (the smallest path cost)
            Node currentNode = frontier.poll();

            // graph search: the same state can be in the queue more than once
            // (with different costs). The cheapest copy comes out first,
            // so skip the other copies if we expanded this state before.
            if (useGraphSearch && explored.contains(currentNode.getState())) {
                continue;
            }
            currentNode.setVisitingOrder(++visitingOrder);

            // goal test when we take the node out of the queue.
            // In UCS this is VERY important: a goal we only generated
            // may still have a cheaper path that we did not find yet.
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
                    double pathCost = currentNode.getPathCost()
                            + p.getActionCost(currentNode.getState(), action, s);
                    Node child = new Node(s, currentNode, action, pathCost);
                    frontier.add(child); // the queue puts it in the right place (by cost)
                    generatedNodes++;
                }
            }
        }

        // the queue is empty and we did not find a goal
        return null;
    }
}
