package sa2026;

import java.util.Locale;

import sa2026.algorithms.BFS;
import sa2026.algorithms.BFSOptimized;
import sa2026.core.Node;
import sa2026.core.Problem;
import sa2026.core.SearchAlgorithm;
import sa2026.problems.wordladder.WordDictionary;
import sa2026.problems.wordladder.WordLadderProblem;
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

        
        // Problem problem = new WordLadderProblem("cat", "dog", WordDictionary.threeLetterWords());
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
}
