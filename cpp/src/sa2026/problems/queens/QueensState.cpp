#include "sa2026/problems/queens/QueensState.h"

#include <cstdlib>  // std::abs
#include <memory>

namespace sa2026::problems::queens {

QueensState::QueensState(const std::vector<int>& rows) : rows(rows) {}

int QueensState::getSize() const {
    return static_cast<int>(rows.size());
}

int QueensState::getRow(int col) const {
    return rows[col];
}

core::StatePtr QueensState::swap(int i, int j) const {
    std::vector<int> newRows = rows;  // never change this state: work on a copy
    newRows[i] = rows[j];
    newRows[j] = rows[i];
    return std::make_shared<QueensState>(newRows);
}

int QueensState::countAttackingPairs() const {
    int pairs = 0;
    for (int i = 0; i < getSize(); i++) {
        for (int j = i + 1; j < getSize(); j++) {
            if (std::abs(rows[i] - rows[j]) == j - i) {
                pairs++;
            }
        }
    }
    return pairs;
}

bool QueensState::isGoal() const {
    return countAttackingPairs() == 0;
}

// draws the board: Q = a queen, . = an empty square
std::string QueensState::toString() const {
    std::string text;
    for (int row = 0; row < getSize(); row++) {
        for (int col = 0; col < getSize(); col++) {
            text += (rows[col] == row) ? " Q" : " .";
        }
        text += '\n';
    }
    return text;
}

// two states are equal when every queen is in the same row
bool QueensState::equals(const core::State& other) const {
    if (this == &other) return true;
    const QueensState* o = dynamic_cast<const QueensState*>(&other);
    if (o == nullptr) return false;
    return rows == o->rows;  // == on two vectors compares the numbers
}

// the same as Arrays.hashCode() in Java: mix all the rows with the prime 31
std::size_t QueensState::hashCode() const {
    std::size_t hash = 1;
    for (int row : rows) {
        hash = 31 * hash + static_cast<std::size_t>(row);
    }
    return hash;
}

}  // namespace sa2026::problems::queens
