#include "sa2026/problems/maze/MazeState.h"

namespace sa2026::problems::maze {

MazeState::MazeState(int row, int col) : row(row), col(col) {}

void MazeState::setMaze(const MazePtr& newMaze) {
    maze = newMaze;
}

MazePtr MazeState::getMaze() {
    return maze;
}

int MazeState::getRow() const {
    return row;
}

int MazeState::getCol() const {
    return col;
}

// the player reached the goal cell
bool MazeState::isGoal() const {
    return maze->isGoal(row, col);
}

// draws the maze: P = player, G = goal, # = wall, . = free cell
std::string MazeState::toString() const {
    std::string text;  // in C++ a string can grow, so we do not need a StringBuilder
    for (int r = 0; r < maze->getRows(); r++) {
        for (int c = 0; c < maze->getCols(); c++) {
            if (r == row && c == col) {
                text += 'P';
            } else if (maze->isGoal(r, c)) {
                text += 'G';
            } else if (maze->isFree(r, c)) {
                text += '.';
            } else {
                text += '#';
            }
        }
        text += '\n';
    }
    return text;
}

// two states are equal when the player is in the same cell
bool MazeState::equals(const core::State& other) const {
    if (this == &other) return true;
    // dynamic_cast to a pointer gives nullptr if "other" is not a MazeState (like instanceof in Java)
    const MazeState* o = dynamic_cast<const MazeState*>(&other);
    if (o == nullptr) return false;
    return row == o->row && col == o->col;
}

/*
 * Equal states must give the same number.
 * We use the cell number: cells are numbered row by row, like seats in a cinema.
 *   cols = 4:  row 0 -> 0 1 2 3,  row 1 -> 4 5 6 7,  row 2 -> 8 9 10 11
 * Each row has its own block of numbers, so two different cells never get
 * the same number (no conflicts), for any maze size.
 *
 * Other option: 31 * row + col (31 is a prime, Java uses it in String.hashCode()).
 * Primes are good when we do not know the ranges of the values.
 * Here we know them (0 <= col < cols), so we can have no conflicts at all.
 */
std::size_t MazeState::hashCode() const {
    return static_cast<std::size_t>(row * maze->getCols() + col);
}

}  // namespace sa2026::problems::maze
