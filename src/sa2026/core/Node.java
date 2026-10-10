package sa2026.core;

import java.util.ArrayList;
import java.util.List;
import java.util.Objects;

/**
 * A node is one box in the search tree.
 * It holds a state and remembers how we reached it.
 *
 * Node implements Comparable so a PriorityQueue can sort nodes by totalCost.
 */
public class Node implements Comparable<Node> {

    private final State state;     // the state inside this node
    private final Node parent;     // the node before this one (null for the root)
    private final IAction action;  // the action that created this node (null for the root)
    private final double pathCost; // g(n): the real cost from the start to this node
    private double totalCost;      // f(n): the value used to sort nodes in a PriorityQueue
    private final int depth;       // number of steps from the root
    private int visitingOrder;     // when the algorithm picked this node (1, 2, 3, ...)

    // creates the root node (the start of the search)
    public Node(State state) {
        this(state, null, null, 0.0);
    }

    // creates a child node; totalCost is the same as pathCost (used by UCS)
    public Node(State state, Node parent, IAction action, double pathCost) {
        this(state, parent, action, pathCost, pathCost);
    }

    // creates a child node with its own totalCost (used by Greedy and A*)
    public Node(State state, Node parent, IAction action, double pathCost, double totalCost) {
        this.state = state;
        this.parent = parent;
        this.action = action;
        this.pathCost = pathCost;
        this.totalCost = totalCost;
        this.depth = (parent == null) ? 0 : parent.depth + 1;
        this.visitingOrder = 0;
    }

    public State getState() {
        return state;
    }

    public Node getParent() {
        return parent;
    }

    public IAction getAction() {
        return action;
    }

    public double getPathCost() {
        return pathCost;
    }

    public double getTotalCost() {
        return totalCost;
    }

    public void setTotalCost(double totalCost) {
        this.totalCost = totalCost;
    }

    public int getDepth() {
        return depth;
    }

    public int getVisitingOrder() {
        return visitingOrder;
    }

    public void setVisitingOrder(int visitingOrder) {
        this.visitingOrder = visitingOrder;
    }

    public boolean isRootNode() {
        return parent == null;
    }

    // returns the path from the root to this node: [root, ..., this]
    public List<Node> getPathFromRoot() {
        List<Node> path = new ArrayList<>();
        Node current = this;
        while (current != null) {
            path.add(0, current); // add at the start of the list
            current = current.getParent();
        }
        return path;
    }

    @Override
    public String toString() {
        String actionName = (action == null) ? "no action (start)" : action.getName();
        return "action: " + actionName
                + ", pathCost: " + pathCost
                + ", depth: " + depth
                + ", state:\n" + state + "\n";
    }

    // two nodes are equal when they hold the same state
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Node other = (Node) o;
        return state.equals(other.state);
    }

    @Override
    public int hashCode() {
        return Objects.hash(state);
    }

    // the node with the smaller totalCost comes first
    @Override
    public int compareTo(Node other) {
        return Double.compare(totalCost, other.totalCost);
    }
}
