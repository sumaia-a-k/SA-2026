#pragma once

#include <cstddef>
#include <string>

#include "sa2026/core/State.h"
#include "sa2026/problems/incomplete_code/maze/Maze.h"

namespace sa2026::problems::incomplete_code::maze {

/*
 * STUDENT TASK: finish this class (here and in MazeState.cpp).
 *
 * A state of the maze problem = where the player is now (row, col).
 * Only row and col are the state.
 *
 * Search for "TODO" and follow the steps.
 */
class MazeState : public core::State {
public:
    // TODO 2: declare the constructor MazeState(int row, int col).
    //         Write its body in MazeState.cpp.


    /*
     * MazeProblem calls this once, before the search starts.
     * This line does NOT copy the maze. It copies the shared pointer,
     * so "maze" points to the same original Maze object.
     */
    static void setMaze(const MazePtr& newMaze);
    static MazePtr getMaze();

    // TODO 3: declare the getters getRow() and getCol(). Both are "const" methods.
    //         Write their bodies in MazeState.cpp.


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
     *
     * Question: what goes wrong if we create two MazeProblem objects with two different mazes?
     */
    inline static MazePtr maze = nullptr;

    // TODO 1: add two const int fields: the row and the col of the player.

};

}  // namespace sa2026::problems::incomplete_code::maze
