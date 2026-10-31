package sa2026.algorithms.incomplete_code;

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
 * STUDENT TASK: write the body of search().
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with DFSDemo (in this folder).
 *
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

        // The code is almost the same as your BFS.java. Only the frontier is different.

        // TODO 1: create the frontier, a stack of nodes:  Deque<Node> frontier = new ArrayDeque<>();
        //         create the set of explored states:     Set<State> explored = new HashSet<>();
        //         and a counter:                         int visitingOrder = 0;

        // TODO 2: create the start node from p.getInitialState() and PUSH it on the stack:
        //         frontier.push(startNode);   Count it: generatedNodes++

        // TODO 3: while the frontier is not empty:
        //   a) take the newest node from the top of the stack:  Node currentNode = frontier.pop();
        //      Question: this is the only line that makes it DFS and not BFS. Why?
        //   b) graph search only: if explored contains its state, skip it with "continue".
        //   c) currentNode.setVisitingOrder(++visitingOrder);
        //   d) goal test: if p.isGoal(currentNode.getState()), return currentNode.
        //   e) graph search only: add the state to explored.
        //   f) expand the node: nodesActuallyExpanded++
        //      then for every action and every next state s (like in BFS):
        //        - create the child node with its pathCost (like in BFS)
        //        - PUSH the child on the top of the stack:  frontier.push(child);
        //          and count it: generatedNodes++
        //      Be careful: use push(), not add(). add() puts the node at the BOTTOM.
        //      Question: the children are pushed in the order of the actions.
        //                Which child does DFS take first?

        // TODO 4: the stack is empty and we did not find a goal: return null.
        return null;
    }
}
