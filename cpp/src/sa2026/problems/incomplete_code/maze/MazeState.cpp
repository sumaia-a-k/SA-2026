#include "sa2026/problems/incomplete_code/maze/MazeState.h"

namespace sa2026::problems::incomplete_code::maze {

// TODO 2: write the constructor MazeState::MazeState(int row, int col).
//         Save the two values in the fields.
//         Hint: const fields get their value in the initializer list:  : row(row), col(col) {}


void MazeState::setMaze(const MazePtr& newMaze) {
    maze = newMaze;
}

MazePtr MazeState::getMaze() {
    return maze;
}

// TODO 3: write the getters MazeState::getRow() and MazeState::getCol().


// The player reached the goal cell.
bool MazeState::isGoal() const {
    // TODO 4: ask the maze if the cell (row, col) is the goal. Hint: maze->isGoal(...)
    return false;
}

// Draws the maze: P = player, G = goal, # = wall, . = free cell
std::string MazeState::toString() const {
    std::string text;
    // TODO 5: go over every row r and every col c of the maze (maze->getRows(), maze->getCols()).
    //         For each cell, add ONE character to text (text += 'P';):
    //           'P' if (r, c) is the player cell
    //           'G' if (r, c) is the goal cell
    //           '.' if the cell is free (maze->isFree)
    //           '#' otherwise
    //         After each row, add '\n'.
    return text;
}

// Two states are equal when the player is in the same cell.
bool MazeState::equals(const core::State& other) const {
    // TODO 6: 1) return true if other is the same object (this == &other)
    //         2) cast to MazeState: const MazeState* o = dynamic_cast<const MazeState*>(&other);
    //            if o is nullptr, other is not a MazeState: return false
    //         3) compare row and col
    return false;
}

// Equal states must give the same number.
std::size_t MazeState::hashCode() const {
    // TODO 7: return the cell number. Hint: row * maze->getCols() + col
    //         Cells are numbered row by row, like seats in a cinema.
    //           cols = 4:  row 0 -> 0 1 2 3,  row 1 -> 4 5 6 7,  row 2 -> 8 9 10 11
    //         Each row has its own block of numbers, so two different cells never
    //         get the same number (no conflicts), for any maze size.
    //         Other option: 31 * row + col (31 is a prime, Java uses it in String.hashCode()).
    //         Question: find two cells that give the same number with 31 * row + col
    //                   in a maze with 40 columns.
    //         Question: what happens in a hash set if equals() is true but hashCode() is different?
    return 0;
}

}  // namespace sa2026::problems::incomplete_code::maze
