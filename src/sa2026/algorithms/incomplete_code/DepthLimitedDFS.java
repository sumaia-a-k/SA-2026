package sa2026.algorithms.incomplete_code;

import java.util.ArrayDeque;
import java.util.Collection;
import java.util.Deque;

import sa2026.core.IAction;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.core.State;

/**
 * STUDENT TASK: write the body of search() and the body of isOnPath().
 * Do DFSCycleCheck.java first: this class is the same, with a depth limit.
 * Search for "TODO" and follow the steps. Check your work with DFSDemo (in this folder).
 *
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
        this.limit = limit;
    }

    // IDS asks this after the search: true = try a bigger limit, false = no solution
    public boolean isCutoff() {
        return cutoff;
    }

    @Override
    public Node search(Problem p) {
        resetCounters();

        // TODO 1: a new search: no cutoff yet, so set cutoff = false.
        //         Question: what goes wrong if the same object is used two times and we forget this?

        // TODO 2: create the frontier (a stack) and visitingOrder = 0.
        //         Create the start node, push it and count it (generatedNodes++).

        // TODO 3: while the frontier is not empty:
        //   a) pop the newest node, and set its visiting order.
        //   b) goal test: if p.isGoal(currentNode.getState()), return currentNode.
        //   c) THE CHANGE: if currentNode.getDepth() >= limit:
        //        set cutoff = true, and do not expand the node ("continue").
        //      Question: why is the goal test BEFORE this test, and not after it?
        //   d) expand the node: nodesActuallyExpanded++
        //      then for every action and every next state s (like in DFSCycleCheck):
        //        - if isOnPath(currentNode, s), skip s ("continue")
        //        - create the child node with its pathCost, push it and count it (generatedNodes++).

        // TODO 4: the stack is empty and we did not find a goal: return null.
        return null;
    }

    // true if the state is in this node or in one of its parents
    private boolean isOnPath(Node node, State s) {
        // TODO 5: the same as isOnPath() in your DFSCycleCheck.java
        return false;
    }
}
