#pragma once

#include <cstddef>
#include <string>

#include "sa2026/core/State.h"
#include "sa2026/problems/maze/Maze.h"

namespace sa2026::problems::maze {

/*
 * A state of the maze problem = where the player is now (row, col).
 * Only row and col are the state.
 *
 * "public core::State" = MazeState implements the State interface.
 */
class MazeState : public core::State {
public:
    MazeState(int row, int col);

    /*
     * MazeProblem calls this once, before the search starts.
     * This line does NOT copy the maze. It copies the shared pointer,
     * so "maze" points to the same original Maze object.
     */
    static void setMaze(const MazePtr& newMaze);
    static MazePtr getMaze();

    int getRow() const;
    int getCol() const;

    // "override" = this method replaces a virtual method of the parent.
    // The compiler gives an error if the name or the types are wrong.
    bool isGoal() const override;
    std::string toString() const override;
    bool equals(const core::State& other) const override;
    std::size_t hashCode() const override;

private:
    /*
     * The maze is NOT part of the state. The walls and the goal never change.
     * We keep it here only to check the goal and to draw the state.
     *
     * It is static: there is ONE maze for all states, not one per state.
     * So it takes no extra memory per state. It is not used in equals(); hashCode() only reads its number of columns.
     * Limit: we can work with only one maze at a time. A new maze replaces the old one.
     *
     * "inline" (C++17) lets us create the static field here, in the header.
     * Without "inline" we must also write it once in a .cpp file.
     *
     * Other options:
     *  1. A normal (non-static) field: each state keeps a pointer to the same maze.
     *     It costs only one pointer per state, and we can have many mazes.
     *  2. Keep the maze only in MazeProblem and MazeAction, so the state is just (row, col).
     *     But then it is harder to draw the maze with the player in it.
     */
    inline static MazePtr maze = nullptr;

    const int row;
    const int col;
};

}  // namespace sa2026::problems::maze
