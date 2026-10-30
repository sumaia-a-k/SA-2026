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
 * BFS with one small change for graph search:
 * we check the state when we CREATE the child, not when we take it out of the queue.
 *
 * In the standard BFS the same state can go into the queue many times
 * (it is skipped later, but it still uses memory).
 * Here "reached" has every state we generated: the states in the queue
 * and the states already expanded. So each state goes into the queue only once.
 *
 * Why "reached" and not "visited"? People use "visited" for two different things
 * (added to the queue, or expanded). "reached" is the name in the AIMA book.
 *
 * The answer is the same as the standard BFS. We only use less memory and less time.
 * In tree search mode this class works exactly like the standard BFS.
 */
public class BFSOptimized extends SearchAlgorithm {

    // tree search
    public BFSOptimized() {
        super(false);
    }

    // true = graph search, false = tree search
    public BFSOptimized(boolean useGraphSearch) {
        super(useGraphSearch);
    }

    @Override
    public Node search(Problem p) {
        resetCounters();

        Queue<Node> frontier = new LinkedList<>();
        Set<State> reached = new HashSet<>(); // every state we generated: in the queue or expanded
        int visitingOrder = 0;

        Node startNode = new Node(p.getInitialState());
        frontier.add(startNode);
        generatedNodes++;
        if (useGraphSearch) {
            reached.add(startNode.getState());
        }

        while (!frontier.isEmpty()) {
            Node currentNode = frontier.poll();
            currentNode.setVisitingOrder(++visitingOrder);

            if (p.isGoal(currentNode.getState())) {
                return currentNode;
            }

            nodesActuallyExpanded++;
            for (IAction action : p.getActions()) {
                Collection<State> nextStates = action.apply(currentNode.getState());
                for (State s : nextStates) {
                    // the change: we saw this state before, so do not add it again
                    if (useGraphSearch && reached.contains(s)) {
                        continue;
                    }
                    if (useGraphSearch) {
                        reached.add(s);
                    }

                    double pathCost = currentNode.getPathCost()
                            + p.getActionCost(currentNode.getState(), action, s);
                    Node child = new Node(s, currentNode, action, pathCost);
                    frontier.add(child);
                    generatedNodes++;
                }
            }
        }

        return null;
    }
}
