#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <string>
#include <vector>

#include "sa2026/core/IAction.h"
#include "sa2026/core/State.h"

namespace sa2026::core {

class Node;  // "this class exists", so we can use the name before the class is written
using NodePtr = std::shared_ptr<Node>;

/*
 * A node is one box in the search tree.
 * It holds a state and remembers how we reached it.
 *
 * Node has compareTo(), so a priority queue can sort nodes by totalCost.
 */
class Node {
public:
    // creates the root node (the start of the search)
    explicit Node(StatePtr state);

    // creates a child node; totalCost is the same as pathCost (used by UCS)
    Node(StatePtr state, NodePtr parent, ActionPtr action, double pathCost);

    // creates a child node with its own totalCost (used by Greedy and A*)
    Node(StatePtr state, NodePtr parent, ActionPtr action, double pathCost, double totalCost);

    StatePtr getState() const;
    NodePtr getParent() const;
    ActionPtr getAction() const;
    double getPathCost() const;
    double getTotalCost() const;
    void setTotalCost(double newTotalCost);
    int getDepth() const;
    int getVisitingOrder() const;
    void setVisitingOrder(int newVisitingOrder);
    bool isRootNode() const;

    /*
     * Returns the path from the root to this node: [root, ..., this]
     * The vector has plain pointers (Node*). They do not own the nodes, they only point to them.
     * This is safe: each node keeps its parent alive (with a shared pointer).
     */
    std::vector<const Node*> getPathFromRoot() const;

    std::string toString() const;

    // two nodes are equal when they hold the same state
    bool equals(const Node& other) const;

    std::size_t hashCode() const;

    // the node with the smaller totalCost comes first: returns -1, 0 or 1 (like Java)
    int compareTo(const Node& other) const;

private:
    // "const" fields can not change after the constructor (like "final" in Java)
    const StatePtr state;     // the state inside this node
    const NodePtr parent;     // the node before this one (nullptr for the root)
    const ActionPtr action;   // the action that created this node (nullptr for the root)
    const double pathCost;    // g(n): the real cost from the start to this node
    double totalCost;         // f(n): the value used to sort nodes in a priority queue
    const int depth;          // number of steps from the root
    int visitingOrder;        // when the algorithm picked this node (1, 2, 3, ...)
};

// prints a cost like Java does: 10.0, 1.5
std::string formatCost(double cost);

// lets us write  std::cout << node
std::ostream& operator<<(std::ostream& out, const Node& node);

}  // namespace sa2026::core
