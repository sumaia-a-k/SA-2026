#include "sa2026/core/Node.h"

#include <sstream>
#include <utility>

namespace sa2026::core {

// One constructor can call another one (like this(...) in Java).
Node::Node(StatePtr state) : Node(std::move(state), nullptr, nullptr, 0.0) {}

Node::Node(StatePtr state, NodePtr parent, ActionPtr action, double pathCost)
    : Node(std::move(state), std::move(parent), std::move(action), pathCost, pathCost) {}

/*
 * The part after ":" is the initializer list. It gives the fields their first value.
 * "const" fields can get a value ONLY here, not inside { }.
 * std::move = "take this value, I do not need it any more". It saves a copy.
 */
Node::Node(StatePtr state, NodePtr parent, ActionPtr action, double pathCost, double totalCost)
    : state(std::move(state)),
      parent(std::move(parent)),
      action(std::move(action)),
      pathCost(pathCost),
      totalCost(totalCost),
      depth(this->parent == nullptr ? 0 : this->parent->depth + 1),
      visitingOrder(0) {}

StatePtr Node::getState() const {
    return state;
}

NodePtr Node::getParent() const {
    return parent;
}

ActionPtr Node::getAction() const {
    return action;
}

double Node::getPathCost() const {
    return pathCost;
}

double Node::getTotalCost() const {
    return totalCost;
}

void Node::setTotalCost(double newTotalCost) {
    totalCost = newTotalCost;
}

int Node::getDepth() const {
    return depth;
}

int Node::getVisitingOrder() const {
    return visitingOrder;
}

void Node::setVisitingOrder(int newVisitingOrder) {
    visitingOrder = newVisitingOrder;
}

bool Node::isRootNode() const {
    return parent == nullptr;
}

std::vector<const Node*> Node::getPathFromRoot() const {
    std::vector<const Node*> path;
    const Node* current = this;
    while (current != nullptr) {
        path.insert(path.begin(), current);  // add at the start of the vector
        current = current->parent.get();     // .get() gives the plain pointer
    }
    return path;
}

std::string Node::toString() const {
    std::string actionName = (action == nullptr) ? "no action (start)" : action->getName();
    return "action: " + actionName
           + ", pathCost: " + formatCost(pathCost)
           + ", depth: " + std::to_string(depth)
           + ", state:\n" + state->toString() + "\n";
}

bool Node::equals(const Node& other) const {
    if (this == &other) return true;
    return state->equals(*other.state);
}

std::size_t Node::hashCode() const {
    return state->hashCode();
}

int Node::compareTo(const Node& other) const {
    if (totalCost < other.totalCost) return -1;
    if (totalCost > other.totalCost) return 1;
    return 0;
}

/*
 * C++ prints 10.0 as "10", but Java prints "10.0".
 * So we add ".0" when the number has no decimal part, to get the same output as Java.
 */
std::string formatCost(double cost) {
    std::ostringstream text;  // like StringBuilder in Java, but we can use << on it
    text << cost;
    std::string result = text.str();
    if (result.find('.') == std::string::npos && result.find('e') == std::string::npos) {
        result += ".0";
    }
    return result;
}

std::ostream& operator<<(std::ostream& out, const Node& node) {
    return out << node.toString();
}

}  // namespace sa2026::core
