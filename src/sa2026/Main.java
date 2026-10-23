package sa2026;

import sa2026.algorithms.BFS;
import sa2026.algorithms.BFSOptimized;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.problems.maze.Maze;
import sa2026.problems.maze.MazeProblem;

/**
 * The start point of the program.
 * We solve the maze with BFS, then we compare the BFS versions.
 */
public class Main {

    public static void main(String[] args) {
        Maze maze = Maze.fromLines(
                "S.#....",
                ".##.##.",
                "....#..",
                ".##....",
                "...#.#G");
        Problem problem = new MazeProblem(maze);

        // 1. solve the maze with BFS (graph search) and print every step
        System.out.println("=== BFS, graph search ===");
        SearchAlgorithm algorithm = new BFS(true);
        Node goal = problem.solve(algorithm);
        algorithm.printSolution(goal);

        // 2. the same maze with every version, to compare the numbers
        System.out.println("\n=== Compare the BFS versions ===");
        System.out.println("Version                  Steps  Expanded  Generated");
        compare("BFS, tree search", new BFS(false), problem);
        compare("BFS, graph search", new BFS(true), problem);
        compare("BFSOptimized, graph", new BFSOptimized(true), problem);
    }

    // solves the problem and prints one line of numbers
    private static void compare(String name, SearchAlgorithm algorithm, Problem problem) {
        Node goal = problem.solve(algorithm);
        int steps = (goal == null) ? -1 : goal.getDepth();
        System.out.printf("%-24s %5d %9d %10d%n", name, steps,
                algorithm.getNodesActuallyExpanded(), algorithm.getGeneratedNodes());
    }
}
