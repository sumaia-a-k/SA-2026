package sa2026.core;

/**
 * The parent class of all search algorithms (BFS, DFS, UCS, A*, ...).
 * Each algorithm writes its own search() method.
 */
public abstract class SearchAlgorithm {

    // false = tree search (a state can be visited again)
    // true  = graph search (we remember explored states and do not visit them again)
    protected boolean useGraphSearch = false;

    // number of child nodes created (generated)
    protected int developedNodes = 0;

    // number of nodes taken from the frontier and expanded
    protected int nodesActuallyExpanded = 0;

    // searches for a goal and returns the goal node, or null if there is no solution
    public abstract Node search(Problem p);

    public int getDevelopedNodes() {
        return developedNodes;
    }

    public int getNodesActuallyExpanded() {
        return nodesActuallyExpanded;
    }

    // prints every step from the start to the goal
    public void printSolution(Node solution) {
        if (solution == null) {
            System.out.println("No solution found.");
            return;
        }
        for (Node node : solution.getPathFromRoot()) {
            System.out.println(node);
        }
        System.out.println("Solution cost: " + solution.getPathCost());
        System.out.println("Solution steps: " + solution.getDepth());
        System.out.println("Developed nodes: " + developedNodes);
        System.out.println("Expanded nodes: " + nodesActuallyExpanded);
    }
}
