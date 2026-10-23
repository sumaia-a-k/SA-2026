#include "sa2026/core/Problem.h"

#include <stdexcept>

#include "sa2026/core/SearchAlgorithm.h"

namespace sa2026::core {

std::shared_ptr<const HeuristicFunction> Problem::getHeuristicFunction() const {
    // std::logic_error is like UnsupportedOperationException in Java
    throw std::logic_error("This problem does not have a heuristic function.");
}

NodePtr Problem::solve(SearchAlgorithm& algorithm) const {
    return algorithm.search(*this);  // *this = this problem object
}

}  // namespace sa2026::core
