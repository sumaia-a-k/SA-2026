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
 * Do BFS.java first: this class is the same, with one small change.
 * Search for "TODO" and follow the steps. Check your work with BFSDemo (in this folder).
 *
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

        // TODO 1: create the frontier (a Queue<Node>), the set "reached" (a Set<State>)
        //         and the counter visitingOrder = 0.
        //         "reached" = every state we generated: the states in the queue AND the expanded ones.

        // TODO 2: create the start node, add it to the frontier and count it (generatedNodes++).
        //         Graph search only: add its state to "reached" too.
        //         Question: what goes wrong if we forget to add the start state here?

        // TODO 3: while the frontier is not empty:
        //   a) take the oldest node out of the queue (poll).
        //      There is NO "explored" check here. Question: why do we not need it?
        //   b) currentNode.setVisitingOrder(++visitingOrder);
        //   c) goal test: if p.isGoal(currentNode.getState()), return currentNode.
        //   d) expand the node: nodesActuallyExpanded++
        //      then for every action and every next state s (like in BFS):
        //        - THE CHANGE: graph search only:
        //            if reached contains s, skip it ("continue"),
        //            else add s to reached
        //        - create the child node with its pathCost (like in BFS),
        //          add it to the end of the queue and count it (generatedNodes++)

        // TODO 4: the queue is empty and we did not find a goal: return null.
        return null;
    }
}
