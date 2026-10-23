package sa2026.algorithms.incomplete_code;

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
 * STUDENT TASK: write the body of search().
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with BFSDemo (in this folder).
 *
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

        // TODO 1: create the frontier, a queue of nodes:  Queue<Node> frontier = new LinkedList<>();
        //         create the set of explored states:     Set<State> explored = new HashSet<>();
        //         and a counter:                         int visitingOrder = 0;
        //         Question: why do we create them here, and not as fields of the class?

        // TODO 2: create the start node from p.getInitialState() and add it to the frontier.
        //         The start node is a generated node too: generatedNodes++

        // TODO 3: while the frontier is not empty:
        //   a) take the oldest node out of the queue:  Node currentNode = frontier.poll();
        //   b) graph search only (useGraphSearch is true):
        //      if explored contains its state, skip it with "continue".
        //      Question: how can the same state be in the queue two times?
        //   c) currentNode.setVisitingOrder(++visitingOrder);
        //   d) goal test: if p.isGoal(currentNode.getState()), return currentNode.
        //      Question: why do we test the goal when we take the node OUT of the queue,
        //                and not when we put it in?
        //   e) graph search only: add the state to explored.
        //   f) expand the node: nodesActuallyExpanded++
        //      then for every action in p.getActions(),
        //      and for every next state s in action.apply(currentNode.getState()):
        //        - pathCost = currentNode.getPathCost() + p.getActionCost(currentNode.getState(), action, s)
        //        - Node child = new Node(s, currentNode, action, pathCost);
        //        - add the child to the END of the queue, and count it: generatedNodes++

        // TODO 4: the queue is empty and we did not find a goal: return null.
        return null;
    }
}
