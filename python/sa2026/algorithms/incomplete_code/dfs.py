from sa2026.core.node import Node
from sa2026.core.problem import Problem
from sa2026.core.search_algorithm import SearchAlgorithm
from sa2026.core.state import State  # you need it in TODO 1 (for the type hint)


class DFS(SearchAlgorithm):
    """
    STUDENT TASK: write the body of search().
    Everything else is ready. Search for "TODO" and follow the steps.
    Check your work with dfs_demo.py (in this folder).

    Depth-First Search (DFS), the standard version.

    DFS always goes deeper first. At a dead end it goes back
    to the newest node that is still waiting in the stack.
    The frontier is a stack (LIFO): the last node in is the first node out.

    Tree search:  we do not remember anything. In a graph with cycles
                  DFS can go around a cycle forever!
    Graph search: we remember the explored states and do not expand them again.

    DFS is not optimal: the first path it finds can be a long one.
    """

    # True = graph search, False = tree search (the default)
    def __init__(self, use_graph_search: bool = False):
        super().__init__(use_graph_search)

    def search(self, p: Problem) -> Node | None:
        self._reset_counters()

        # The code is almost the same as your bfs.py. Only the frontier is different.

        # TODO 1: create the frontier, a stack of nodes. A list is a good stack:
        #           frontier: list[Node] = []
        #         create the set of explored states:  explored: set[State] = set()
        #         and a counter:                      visiting_order = 0

        # TODO 2: create the start node from p.get_initial_state() and PUSH it on the stack:
        #         frontier.append(start_node)   Count it: self.generated_nodes += 1

        # TODO 3: while the frontier is not empty (while frontier:):
        #   a) take the newest node from the top of the stack:  current_node = frontier.pop()
        #      Question: this is the only line that makes it DFS and not BFS. Why?
        #   b) graph search only: if its state is in explored, skip it with "continue".
        #   c) visiting_order += 1, then current_node.visiting_order = visiting_order
        #   d) goal test: if p.is_goal(current_node.state), return current_node.
        #   e) graph search only: add the state to explored.
        #   f) expand the node: self.nodes_actually_expanded += 1
        #      then for every action and every next state s (like in BFS):
        #        - create the child node with its path_cost (like in BFS)
        #        - PUSH the child on the top of the stack:  frontier.append(child)
        #          and count it: self.generated_nodes += 1
        #      Be careful: pop() takes from the END, so append() must put the child at the END too.
        #      Do not use pop(0): that takes from the start (and then it is BFS!).
        #      Question: the children are pushed in the order of the actions.
        #                Which child does DFS take first?

        # TODO 4: the stack is empty and we did not find a goal: return None.
        return None
