package sa2026.algorithms.incomplete_code;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashSet;
import java.util.List;
import java.util.Set;

import sa2026.core.HeuristicFunction;
import sa2026.core.IAction;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.core.State;

/**
 * STUDENT TASK: write the body of search().
 * Everything else is ready. Search for "TODO" and follow the steps.
 * Check your work with BeamDemo (in this folder).
 *
 * Beam Search.
 *
 * Beam Search is Greedy with a small frontier. The frontier can keep only
 * k nodes (k = the beam width). After each expansion we sort the WHOLE frontier
 * (old nodes and new children together) by f(n) = h(n), keep the k best nodes
 * and throw away the rest. A node that we throw away never comes back.
 *
 * Tree search and graph search: NOT complete. The way to the goal can be thrown away.
 * Beam Search is NOT optimal. Its good point: the frontier has at most k nodes after each step.
 */
public class BeamSearch extends SearchAlgorithm {

    private final int beamWidth;  // k: the most nodes the frontier can keep
    private int thrownAwayNodes;  // how many nodes the last search threw away

    // tree search
    public BeamSearch(int beamWidth) {
        this(beamWidth, false);
    }

    // true = graph search, false = tree search
    public BeamSearch(int beamWidth, boolean useGraphSearch) {
        super(useGraphSearch);
        if (beamWidth < 1) {
            throw new IllegalArgumentException("The beam width k must be 1 or more, not " + beamWidth + ".");
        }
        this.beamWidth = beamWidth;
    }

    public int getBeamWidth() {
        return beamWidth;
    }

    public int getThrownAwayNodes() {
        return thrownAwayNodes;
    }

    @Override
    public Node search(Problem p) {
        resetCounters();
        thrownAwayNodes = 0; // a new search: nothing thrown away yet

        // The code is almost the same as your Greedy.java. Only the frontier and one new step are different.

        // TODO 1: like in Greedy: HeuristicFunction h = p.getHeuristicFunction();
        //         a Set<State> explored (HashSet) and int visitingOrder = 0.
        //         NEW: the frontier is a list, not a PriorityQueue:
        //           List<Node> frontier = new ArrayList<>();
        //         Question: why can we not use a PriorityQueue here? (Look at TODO 3 h.)

        // TODO 2: like in Greedy: create the start node with FIVE values:
        //           new Node(start, null, null, 0.0, h.getH(start))
        //         (start = p.getInitialState()). Add it to the frontier and count it: generatedNodes++

        // TODO 3: while the frontier is not empty:
        //   a) take the best node. The list is sorted, so the best node is the first one:
        //        Node currentNode = frontier.remove(0);
        //   b) graph search only: if explored contains its state, skip it with "continue".
        //   c) currentNode.setVisitingOrder(++visitingOrder);
        //   d) goal test: if p.isGoal(currentNode.getState()), return currentNode.
        //   e) graph search only: add the state to explored.
        //   f) expand the node, like in Greedy: nodesActuallyExpanded++
        //      then for every action and every next state s:
        //        - pathCost = currentNode.getPathCost() + p.getActionCost(currentNode.getState(), action, s)
        //        - double f = h.getH(s);
        //        - Node child = new Node(s, currentNode, action, pathCost, f);
        //        - frontier.add(child);  (at the end of the list for now)  and count it: generatedNodes++
        //   g) after the for loops: sort the WHOLE frontier by f(n):  Collections.sort(frontier);
        //      Question: two nodes have the same h. Which one is first after the sort?
        //                (Collections.sort() does not change the order of equal nodes.)
        //   h) NEW in Beam Search: keep only the k best nodes. While frontier.size() > beamWidth:
        //        - remove the last node (the worst one):  frontier.remove(frontier.size() - 1);
        //        - count it: thrownAwayNodes++
        //      Question: can a node that was in the frontier BEFORE this step be thrown away too?
        //                (Look at step 3 of the trace on beam.html.)
        //   Question: run BeamDemo. With the misleading guess and k = 1 your search returns null,
        //             but the path S -> B -> E -> G exists. Why?

        // TODO 4: the frontier is empty and we did not find a goal: return null.
        return null;
    }
}
