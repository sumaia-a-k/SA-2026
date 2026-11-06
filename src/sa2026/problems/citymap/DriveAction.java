package sa2026.problems.citymap;

import java.util.ArrayList;
import java.util.Collection;
import java.util.List;

import sa2026.core.IAction;
import sa2026.core.State;

/**
 * The only action of the problem: drive on ONE road to a neighbor city.
 * Like ChangeLetterAction, this one action can give MANY next states:
 *   "A" -> "C", "D", "S"
 *
 * The action does not know the cost. The cost (the road length)
 * comes from CityMapProblem.getActionCost().
 */
public class DriveAction implements IAction {

    private final CityMap map;

    public DriveAction(CityMap map) {
        this.map = map;
    }

    @Override
    public Collection<State> apply(State s) {
        String city = ((CityState) s).getCity();
        List<State> nextStates = new ArrayList<>();
        for (String neighbor : map.getNeighbors(city)) {
            nextStates.add(new CityState(neighbor));
        }
        return nextStates;
    }

    @Override
    public String getName() {
        return "Drive to a neighbor city";
    }
}
