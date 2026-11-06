package sa2026.problems.citymap;

import java.util.ArrayList;
import java.util.List;

import sa2026.core.IAction;
import sa2026.core.Problem;
import sa2026.core.State;

/**
 * The city map problem: drive from the start city to the goal city
 * with the SHORTEST total distance (not the fewest roads!).
 *
 * Example: S -> A -> C -> F -> G  (4 roads, 18 km)
 *     and  S -> A -> D -> G       (3 roads, 33 km)
 *
 * Initial state: the start city.
 * Goal:          the goal city.
 * Actions:       drive to a neighbor city (only one action, but it gives many states).
 * Cost:          the length of the road. Roads have DIFFERENT costs,
 *                so this is a problem for UCS, not for BFS.
 */
public class CityMapProblem extends Problem {

    private final CityMap map;
    private final State initialState;
    private final List<IAction> actions = new ArrayList<>();

    public CityMapProblem(String startCity, String goalCity, CityMap map) {
        if (!map.hasCity(startCity) || !map.hasCity(goalCity)) {
            throw new IllegalArgumentException("The start and goal cities must be on the map.");
        }
        this.map = map;
        CityState.setGoalCity(goalCity);
        initialState = new CityState(startCity);
        actions.add(new DriveAction(map));
    }

    @Override
    public State getInitialState() {
        return initialState;
    }

    @Override
    public boolean isGoal(State state) {
        return state.isGoal();
    }

    @Override
    public List<IAction> getActions() {
        return actions;
    }

    // the cost of the action = the length of the road between the two cities
    @Override
    public double getActionCost(State s, IAction a, State next) {
        return map.getDistance(((CityState) s).getCity(), ((CityState) next).getCity());
    }
}
