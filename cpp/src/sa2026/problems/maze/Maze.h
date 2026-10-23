#pragma once

#include <memory>
#include <string>
#include <vector>

namespace sa2026::problems::maze {

class Maze;
using MazePtr = std::shared_ptr<const Maze>;

/*
 * The maze map: a grid of free cells and walls, with a start cell and a goal cell.
 *
 * A maze is made from text lines. Each character is one cell:
 *   '#' = wall      '.' = free cell      'S' = start      'G' = goal
 *
 * The maze never changes after it is created, so many states can share it.
 */
class Maze {
public:
    /*
     * Creates a maze from text lines, for example: Maze::fromLines({"S.#", "..G"})
     *
     * Java uses "String..." (varargs). In C++ we pass a vector of strings.
     * The braces { } make the vector for us, so these two calls are the same:
     *   Maze::fromLines({"S.#", "..G"});
     *   Maze::fromLines(std::vector<std::string>{"S.#", "..G"});
     *
     * It returns a shared pointer, because many states will share this one maze.
     */
    static MazePtr fromLines(const std::vector<std::string>& lines);

    int getRows() const;
    int getCols() const;
    int getStartRow() const;
    int getStartCol() const;
    int getGoalRow() const;
    int getGoalCol() const;

    // true if the cell is inside the maze and is not a wall
    bool isFree(int row, int col) const;

    bool isGoal(int row, int col) const;

private:
    // private: only fromLines() can create a maze
    explicit Maze(const std::vector<std::string>& lines);

    std::vector<std::vector<bool>> walls;  // walls[row][col] is true if the cell is a wall
    int rows = 0;
    int cols = 0;
    int startRow = 0, startCol = 0;
    int goalRow = 0, goalCol = 0;
};

}  // namespace sa2026::problems::maze
