package sa2026.algorithms;

import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;

/**
 * Iterative Deepening Search (IDS).
 *
 * We do not know the depth of the goal, so we try every limit:
 * DepthLimitedDFS with limit 0, then 1, then 2, ... until we find the goal.
 *
 * The first limit that finds a goal is its depth, so the path is a shortest one
 * (the same answer as BFS, if all steps cost the same).
 * But the memory is small, like DFS: only one path and the nodes that wait next to it.
 *
 * If the state space is INFINITE and there is no solution, IDS never stops (BFS neither).
 */
public class IterativeDeepening extends SearchAlgorithm {

    public IterativeDeepening() {
        super(false); // every iteration is a tree search with a cycle check
    }

    @Override
    public Node search(Problem p) {
        resetCounters();

        // try limit 0, 1, 2, ... until we find the goal
        for (int limit = 0; ; limit++) {
            DepthLimitedDFS dls = new DepthLimitedDFS(limit);
            Node result = dls.search(p);

            // count the work of every iteration
            generatedNodes += dls.getGeneratedNodes();
            nodesActuallyExpanded += dls.getNodesActuallyExpanded();

            if (result != null) {
                return result;   // found the goal
            }
            if (!dls.isCutoff()) {
                return null;     // no node stopped at the limit: there is no solution
            }
        }
    }
}
