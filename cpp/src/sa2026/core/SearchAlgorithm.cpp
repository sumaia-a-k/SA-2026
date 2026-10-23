#include "sa2026/core/SearchAlgorithm.h"

#include <iostream>

namespace sa2026::core {

SearchAlgorithm::SearchAlgorithm() : SearchAlgorithm(false) {}

SearchAlgorithm::SearchAlgorithm(bool useGraphSearch) : useGraphSearch(useGraphSearch) {}

void SearchAlgorithm::resetCounters() {
    developedNodes = 0;
    nodesActuallyExpanded = 0;
}

bool SearchAlgorithm::isGraphSearch() const {
    return useGraphSearch;
}

int SearchAlgorithm::getDevelopedNodes() const {
    return developedNodes;
}

int SearchAlgorithm::getNodesActuallyExpanded() const {
    return nodesActuallyExpanded;
}

void SearchAlgorithm::printSolution(const NodePtr& solution) const {
    if (solution == nullptr) {
        std::cout << "No solution found." << std::endl;
        return;
    }
    for (const Node* node : solution->getPathFromRoot()) {
        std::cout << *node << std::endl;  // *node = the node that the pointer points to
    }
    std::cout << "Solution cost: " << formatCost(solution->getPathCost()) << std::endl;
    std::cout << "Solution steps: " << solution->getDepth() << std::endl;
    std::cout << "Developed nodes: " << developedNodes << std::endl;
    std::cout << "Expanded nodes: " << nodesActuallyExpanded << std::endl;
}

}  // namespace sa2026::core
