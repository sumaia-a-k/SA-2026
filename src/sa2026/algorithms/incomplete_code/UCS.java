package sa2026.algorithms.incomplete_code;

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
 * STUDENT TASK: write the body of search().
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with UCSDemo (in this folder).
 *
 * Uniform-Cost Search (UCS).
 *
 * UCS always expands the CHEAPEST node first: the node with the smallest
 * path cost g(n) (the real cost from the start to the node).
 * The frontier is a PriorityQueue: poll() always gives the node with the smallest cost.
 *
 * Tree search:  we do not remember anything, so a state can come back many times.
 * Graph search: we remember the explored states and do not expand them again.
 *
 * UCS is optimal when every action costs more than 0.
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

        // The code is almost the same as your BFS.java. Only the frontier is different.

        // TODO 1: create the frontier, a PRIORITY queue of nodes:
        //           PriorityQueue<Node> frontier = new PriorityQueue<>();
        //         create the set of explored states:  Set<State> explored = new HashSet<>();
        //         and a counter:                      int visitingOrder = 0;
        //         Question: how does the PriorityQueue know which node is the cheapest?
        //                   (Look at Node.compareTo() and the Node constructors.)

        // TODO 2: create the start node from p.getInitialState() and add it to the frontier.
        //         Count it: generatedNodes++
        //         Question: what is the path cost of the start node?

        // TODO 3: while the frontier is not empty:
        //   a) take the CHEAPEST node out of the queue:  Node currentNode = frontier.poll();
        //      Question: this is the only line that makes it UCS and not BFS. Why?
        //   b) graph search only: if explored contains its state, skip it with "continue".
        //      Question: the same state can be in the queue two times, with two different costs.
        //                Which copy comes out first?
        //   c) currentNode.setVisitingOrder(++visitingOrder);
        //   d) goal test: if p.isGoal(currentNode.getState()), return currentNode.
        //      Question: in BFS it was only "better" to test the goal here.
        //                In UCS it is a MUST. Why? (Hint: S -> G costs 10, S -> A -> G costs 2.)
        //   e) graph search only: add the state to explored.
        //   f) expand the node: nodesActuallyExpanded++
        //      then for every action and every next state s (like in BFS):
        //        - pathCost = currentNode.getPathCost() + p.getActionCost(currentNode.getState(), action, s)
        //          Be careful: add the cost of THIS action to the cost of the parent.
        //        - Node child = new Node(s, currentNode, action, pathCost);
        //        - add the child to the queue:  frontier.add(child);   and count it: generatedNodes++
        //          The queue puts it in the right place for you (sorted by cost).

        // TODO 4: the queue is empty and we did not find a goal: return null.
        return null;
    }
}
