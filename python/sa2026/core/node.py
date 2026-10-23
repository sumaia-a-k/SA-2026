from sa2026.core.i_action import IAction
from sa2026.core.state import State


class Node:
    """
    A node is one box in the search tree.
    It holds a state and remembers how we reached it.

    Node has __lt__ ("less than"), so a priority queue (heapq) can sort nodes by total_cost.
    """

    # Java has three constructors. Python has only one __init__,
    # so we use default values (= None, = 0.0) to get the same three ways:
    #   Node(state)                                      -> the root node (the start of the search)
    #   Node(state, parent, action, path_cost)           -> total_cost is the same as path_cost (used by UCS)
    #   Node(state, parent, action, path_cost, total)    -> its own total_cost (used by Greedy and A*)
    def __init__(self, state: State, parent: "Node | None" = None,
                 action: IAction | None = None, path_cost: float = 0.0,
                 total_cost: float | None = None):
        # Python has no "final". Do not change these five after the node is created.
        self.state = state          # the state inside this node
        self.parent = parent        # the node before this one (None for the root)
        self.action = action        # the action that created this node (None for the root)
        self.path_cost = path_cost  # g(n): the real cost from the start to this node
        self.depth: int = 0 if parent is None else parent.depth + 1  # number of steps from the root

        # f(n): the value used to sort nodes in a priority queue
        self.total_cost = path_cost if total_cost is None else total_cost
        # when the algorithm picked this node (1, 2, 3, ...)
        self.visiting_order = 0

    def is_root_node(self) -> bool:
        return self.parent is None

    # returns the path from the root to this node: [root, ..., self]
    def get_path_from_root(self) -> list["Node"]:
        path: list[Node] = []
        current: Node | None = self
        while current is not None:
            path.insert(0, current)  # add at the start of the list
            current = current.parent
        return path

    def __str__(self) -> str:
        action_name = "no action (start)" if self.action is None else self.action.get_name()
        return (f"action: {action_name}"
                f", pathCost: {self.path_cost}"
                f", depth: {self.depth}"
                f", state:\n{self.state}\n")

    # two nodes are equal when they hold the same state
    def __eq__(self, other: object) -> bool:
        if self is other:
            return True
        if not isinstance(other, Node):
            return False
        return self.state == other.state

    def __hash__(self) -> int:
        return hash(self.state)

    # the node with the smaller total_cost comes first (Java: compareTo)
    def __lt__(self, other: "Node") -> bool:
        return self.total_cost < other.total_cost
