package sa2026;

import java.util.Locale;

import sa2026.algorithms.BFS;
import sa2026.algorithms.BFSOptimized;
import sa2026.algorithms.DFS;
import sa2026.algorithms.DFSCycleCheck;
import sa2026.algorithms.DepthLimitedDFS;
import sa2026.algorithms.IterativeDeepening;
import sa2026.algorithms.UCS;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.problems.wordladder.WordDictionary;
import sa2026.problems.wordladder.WordLadderProblem;
import sa2026.problems.npuzzle.NpuzzleProblem;
import sa2026.problems.citymap.CityMap;
import sa2026.problems.citymap.CityMapProblem;
import sa2026.problems.maze.Maze;
import sa2026.problems.maze.MazeProblem;

/**
 * The start point of the program.
 * We solve the maze with BFS, then we compare the BFS versions and the DFS versions.
 * At the end we compare BFS and UCS on a city map where the roads have different lengths.
 */
public class Main {

    public static void main(String[] args) {
        Maze maze = Maze.fromLines(
                "S.#....",
                ".##.##.",
                "....#..",
                ".##....",
                "...#.#G");
       //Problem problem = new MazeProblem(maze);

        
        // Problem problem = new WordLadderProblem("cat", "dog", WordDictionary.threeLetterWords());
      Problem problem = NpuzzleProblem.medium();
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

        // 3. the DFS versions on the same maze (-1 steps = no solution found).
        // No DFS tree search: on this maze it goes around a cycle forever.
        System.out.println("\n=== Compare the DFS versions ===");
        System.out.println("Version                  Steps  Expanded  Generated");
        compare("DFS, graph search", new DFS(true), problem);
        compare("DFS + cycle check", new DFSCycleCheck(), problem);
        compare("DLS, limit 10", new DepthLimitedDFS(10), problem);
        compare("DLS, limit 9", new DepthLimitedDFS(9), problem);
        compare("IDS", new IterativeDeepening(), problem);

        // 4. a city map: the roads have different lengths, so fewer steps is not always cheaper
        System.out.println("\n=== City map S -> G: BFS vs UCS ===");
        Problem cityMap = new CityMapProblem("S", "G", CityMap.example());
        System.out.println("Version                  Steps   Cost  Expanded  Generated");
        compareCost("BFS, graph search", new BFS(true), cityMap);
        compareCost("UCS, graph search", new UCS(true), cityMap);
        compareCost("UCS, tree search", new UCS(false), cityMap);

        System.out.println("\n=== UCS, graph search: the path ===");
        SearchAlgorithm ucs = new UCS(true);
        ucs.printSolution(cityMap.solve(ucs));
    }

    // solves the problem and prints one line of numbers
    private static void compare(String name, SearchAlgorithm algorithm, Problem problem) {
        Node goal = problem.solve(algorithm);
        int steps = (goal == null) ? -1 : goal.getDepth();
        // The format "%-24s %5d %9d %10d%n" means:
        //   %-24s -> a text, 24 characters wide, on the left (the "-" means left)
        //   %5d   -> a whole number, 5 characters wide, on the right
        //   %9d   -> a whole number, 9 characters wide, on the right
        //   %10d  -> a whole number, 10 characters wide, on the right
        //   %n    -> a new line
        // Example: "BFS, graph search", 10, 23, 50 prints
        //   BFS, graph search           10        23         50
        // The fixed widths keep the columns straight under the table header.
        // Locale.ROOT keeps the digits 0-9, even on a PC with Arabic settings.
        System.out.printf(Locale.ROOT, "%-24s %5d %9d %10d%n", name, steps,
                algorithm.getNodesActuallyExpanded(), algorithm.getGeneratedNodes());
    }

    // the same as compare(), with the path cost too (%6.1f = a number with 1 digit after the point)
    private static void compareCost(String name, SearchAlgorithm algorithm, Problem problem) {
        Node goal = problem.solve(algorithm);
        int steps = (goal == null) ? -1 : goal.getDepth();
        double cost = (goal == null) ? -1 : goal.getPathCost();
        System.out.printf(Locale.ROOT, "%-24s %5d %6.1f %9d %10d%n", name, steps, cost,
                algorithm.getNodesActuallyExpanded(), algorithm.getGeneratedNodes());
    }
}
