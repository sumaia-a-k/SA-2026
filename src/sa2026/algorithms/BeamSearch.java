package sa2026.algorithms;

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
 * Beam Search.
 *
 * Beam Search is Greedy with a small frontier. The frontier can keep only
 * k nodes (k = the beam width). After each expansion we sort the WHOLE frontier
 * (old nodes and new children together) by f(n) = h(n), keep the k best nodes
 * and throw away the rest. A node that we throw away never comes back.
 *
 * The code is the same as Greedy. Only two things are different:
 *   1. the frontier is a list, not a PriorityQueue, because we must cut it
 *   2. one new step after each expansion: keep only the k best nodes
 * Same h: the node that came into the frontier first stays first (the sort keeps the order).
 *
 * k = 1:         only one node in the frontier. It always goes to the best child (close to Hill Climbing).
 * k = no limit:  nothing is thrown away. It is Greedy (only nodes with the same h
 *                can come out in another order: a PriorityQueue does not keep the order).
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

        // the guess h(n) of this problem (throws an error if the problem has no heuristic)
        HeuristicFunction h = p.getHeuristicFunction();

        // the frontier is a list, sorted by f(n): the best node is the first one (index 0)
        List<Node> frontier = new ArrayList<>();
        Set<State> explored = new HashSet<>(); // HashSet: contains() is fast
        int visitingOrder = 0;

        // the start node: path cost 0, f(n) = h(n)
        State start = p.getInitialState();
        Node startNode = new Node(start, null, null, 0.0, h.getH(start));
        frontier.add(startNode);
        generatedNodes++; // the start node is a generated node too

        while (!frontier.isEmpty()) {
            // take the node with the smallest f(n): the first one in the list
            Node currentNode = frontier.remove(0);

            // graph search: skip the other copies of a state we already expanded
            if (useGraphSearch && explored.contains(currentNode.getState())) {
                continue;
            }
            currentNode.setVisitingOrder(++visitingOrder);

            // goal test when we take the node out of the frontier (like Greedy)
            if (p.isGoal(currentNode.getState())) {
                return currentNode;
            }

            if (useGraphSearch) {
                explored.add(currentNode.getState());
            }

            // expand: apply every action and add the children to the end of the list
            nodesActuallyExpanded++;
            for (IAction action : p.getActions()) {
                Collection<State> nextStates = action.apply(currentNode.getState());
                for (State s : nextStates) {
                    // g(n): the real cost from the start (only to know the cost of the path)
                    double pathCost = currentNode.getPathCost()
                            + p.getActionCost(currentNode.getState(), action, s);
                    // f(n) = h(n), like Greedy
                    double f = h.getH(s);
                    Node child = new Node(s, currentNode, action, pathCost, f);
                    frontier.add(child);
                    generatedNodes++;
                }
            }

            // sort the whole frontier by f(n) (Node.compareTo()).
            // Collections.sort() keeps the order of two nodes with the same f(n), so the older one stays first.
            Collections.sort(frontier);

            // NEW in Beam Search: keep only the k best nodes, throw away the rest
            while (frontier.size() > beamWidth) {
                frontier.remove(frontier.size() - 1); // the worst node is the last one
                thrownAwayNodes++;
            }
        }

        // the frontier is empty and we did not find a goal
        // (maybe there is a goal, but we threw its way away)
        return null;
    }
}
