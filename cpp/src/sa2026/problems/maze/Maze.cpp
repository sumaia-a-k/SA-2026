#include "sa2026/problems/maze/Maze.h"

#include <stdexcept>

namespace sa2026::problems::maze {

MazePtr Maze::fromLines(const std::vector<std::string>& lines) {
    // We can not use std::make_shared here, because the constructor is private.
    return MazePtr(new Maze(lines));
}

Maze::Maze(const std::vector<std::string>& lines) {
    // std::invalid_argument is like IllegalArgumentException in Java
    if (lines.empty()) {
        throw std::invalid_argument("The maze has no rows.");
    }
    // size() gives an unsigned number (std::size_t), so we change it to int
    rows = static_cast<int>(lines.size());
    cols = static_cast<int>(lines[0].size());
    walls = std::vector<std::vector<bool>>(rows, std::vector<bool>(cols, false));

    bool foundStart = false;
    bool foundGoal = false;

    for (int row = 0; row < rows; row++) {
        if (static_cast<int>(lines[row].size()) != cols) {
            throw std::invalid_argument("Row " + std::to_string(row) + " has a different length.");
        }
        for (int col = 0; col < cols; col++) {
            char cell = lines[row][col];
            if (cell == '#') {
                walls[row][col] = true;
            } else if (cell == 'S') {
                startRow = row;
                startCol = col;
                foundStart = true;
            } else if (cell == 'G') {
                goalRow = row;
                goalCol = col;
                foundGoal = true;
            } else if (cell != '.') {
                throw std::invalid_argument(std::string("Unknown symbol '") + cell + "' at "
                                            + std::to_string(row) + "," + std::to_string(col));
            }
        }
    }
    if (!foundStart || !foundGoal) {
        throw std::invalid_argument("The maze needs one 'S' and one 'G'.");
    }
}

int Maze::getRows() const {
    return rows;
}

int Maze::getCols() const {
    return cols;
}

int Maze::getStartRow() const {
    return startRow;
}

int Maze::getStartCol() const {
    return startCol;
}

int Maze::getGoalRow() const {
    return goalRow;
}

int Maze::getGoalCol() const {
    return goalCol;
}

bool Maze::isFree(int row, int col) const {
    if (row < 0 || row >= rows || col < 0 || col >= cols) {
        return false;  // outside the maze
    }
    return !walls[row][col];
}

bool Maze::isGoal(int row, int col) const {
    return row == goalRow && col == goalCol;
}

}  // namespace sa2026::problems::maze
