#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <unordered_set>
#include <vector>

namespace sa2026::core {

/*
 * A state is one situation of the problem.
 * Example: in a maze, the state is the player position (row, col).
 *
 * Every problem has its own State class that implements this interface.
 * In C++ an "interface" is a class with only pure virtual methods (the ones with "= 0").
 */
class State {
public:
    // A parent class needs a virtual destructor, so the child object is deleted correctly.
    virtual ~State() = default;

    // true if this state is a goal state
    virtual bool isGoal() const = 0;

    // how the state is printed on the screen
    virtual std::string toString() const = 0;

    // two states are equal when they describe the same situation
    virtual bool equals(const State& other) const = 0;

    // must give the same number for equal states
    virtual std::size_t hashCode() const = 0;

    /*
     * Note: unlike Java, a C++ class does NOT get toString(), equals() and hashCode() for free.
     * They are "= 0" here, so the compiler forces you to write them in your State class.
     * Without equals() and hashCode(), graph search can not find repeated states.
     */
};

/*
 * A shared pointer to a state. It works like a reference in Java:
 *  - many objects can point to the same state,
 *  - the state is deleted automatically when nobody points to it any more,
 *  - it can be empty (nullptr), like null in Java.
 * "const" means: the state can not be changed through this pointer.
 */
using StatePtr = std::shared_ptr<const State>;

/*
 * A hash set of states needs two helpers: one gives the hash of a state,
 * and one says if two states are equal. They call our hashCode() and equals().
 * (Java's HashSet calls hashCode() and equals() by itself. In C++ we must tell the set.)
 * operator() lets us use the object like a function: StateHash{}(state)
 */
struct StateHash {
    std::size_t operator()(const StatePtr& s) const { return s->hashCode(); }
};

struct StateEqual {
    bool operator()(const StatePtr& a, const StatePtr& b) const { return a->equals(*b); }
};

// a hash set of states, like HashSet<State> in Java. count() and insert() are fast.
using StateSet = std::unordered_set<StatePtr, StateHash, StateEqual>;

// lets us write  std::cout << state  (it prints "null" if the pointer is empty, like Java)
std::ostream& operator<<(std::ostream& out, const StatePtr& state);

// lets us write  std::cout << states  (it prints them like Java: [cat, bat, hat])
std::ostream& operator<<(std::ostream& out, const std::vector<StatePtr>& states);

}  // namespace sa2026::core
