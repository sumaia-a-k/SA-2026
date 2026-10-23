#pragma once

#include <memory>
#include <string>
#include <vector>

#include "sa2026/core/State.h"

namespace sa2026::core {

/*
 * An action is a move that changes one state to another.
 * Example: in a maze, MoveUp moves the player one cell up.
 */
class IAction {
public:
    virtual ~IAction() = default;

    /*
     * Applies the action on state s and returns the new states.
     * If the action is not allowed (for example a wall), return an empty vector.
     */
    virtual std::vector<StatePtr> apply(const StatePtr& s) const = 0;

    // the action name, for example "Move up"
    virtual std::string getName() const = 0;
};

// a shared pointer to an action (see StatePtr in State.h)
using ActionPtr = std::shared_ptr<const IAction>;

}  // namespace sa2026::core
