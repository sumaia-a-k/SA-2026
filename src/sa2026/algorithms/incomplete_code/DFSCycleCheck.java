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
 * Do DFS.java first: this class is DFS tree search with one small change.
 * Search for "TODO" and follow the steps. Check your work with DFSDemo (in this folder).
 *
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
 */
public class DFSCycleCheck extends SearchAlgorithm {

    public DFSCycleCheck() {
        super(false); // tree search with a cycle check
    }

    @Override
    public Node search(Problem p) {
        resetCounters();

        // TODO 1: create the frontier (a stack: Deque<Node> with ArrayDeque) and visitingOrder = 0.
        //         There is NO explored set here. Question: why not?

        // TODO 2: create the start node, push it and count it (generatedNodes++).

        // TODO 3: while the frontier is not empty:
        //   a) pop the newest node, and set its visiting order.
        //   b) goal test: if p.isGoal(currentNode.getState()), return currentNode.
        //   c) expand the node: nodesActuallyExpanded++
        //      then for every action and every next state s (like in DFS):
        //        - THE CHANGE: if isOnPath(currentNode, s) is true, skip s ("continue").
        //          It would make a cycle.
        //        - create the child node with its pathCost, push it and count it (generatedNodes++).

        // TODO 4: the stack is empty and we did not find a goal: return null.
        return null;
    }

    // true if the state is in this node or in one of its parents
    private boolean isOnPath(Node node, State s) {
        // TODO 5: start with n = node. While n is not null:
        //           - if n.getState().equals(s), return true
        //           - go up one step: n = n.getParent()
        //         At the end (we reached above the start node): return false.
        //         Question: why do we need equals() here, and not == ?
        return false;
    }
}
