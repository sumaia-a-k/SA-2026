package sa2026.algorithms.incomplete_code;

import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;

/**
 * STUDENT TASK: write the body of search().
 * Do DepthLimitedDFS.java first: IDS only calls it again and again.
 * Search for "TODO" and follow the steps. Check your work with DFSDemo (in this folder).
 *
 * Iterative Deepening Search (IDS).
 *
 * We do not know the depth of the goal, so we try every limit:
 * DepthLimitedDFS with limit 0, then 1, then 2, ... until we find the goal.
 *
 * The first limit that finds a goal is its depth, so the path is a shortest one
 * (the same answer as BFS, if all steps cost the same).
 * But the memory is small, like DFS: only one path and the nodes that wait next to it.
 */
public class IterativeDeepening extends SearchAlgorithm {

    public IterativeDeepening() {
        super(false); // every iteration is a tree search with a cycle check
    }

    @Override
    public Node search(Problem p) {
        resetCounters();

        // TODO 1: a loop that never stops by itself:  for (int limit = 0; ; limit++) {
        //   a) create a DepthLimitedDFS with this limit (your class, in this folder),
        //      and run it:  Node result = dls.search(p);
        //   b) add its counters to ours, so we count the work of EVERY iteration:
        //        generatedNodes += dls.getGeneratedNodes();
        //        nodesActuallyExpanded += dls.getNodesActuallyExpanded();
        //   c) if result is not null, we found the goal: return result.
        //   d) if dls.isCutoff() is false, no node stopped at the limit.
        //      We searched everything, so there is no solution: return null.
        //      Question: what happens if we forget this test and there is no solution?
        // }
        //
        // When the loop is written, delete the "return null" below
        // (Java says "unreachable statement" after a loop that never stops).
        return null;
    }
}
