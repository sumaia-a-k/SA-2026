package sa2026.problems.citymap;

import sa2026.core.State;

/**
 * A state of the city map problem = the city where we are now, for example "A".
 */
public class CityState implements State {

    /*
     * The goal city is NOT part of the state. It is the same for all states.
     * Like the goal word in WordLadderState, it is static: one copy for all states.
     * CityMapProblem sets it once, before the search starts.
     */
    private static String goalCity;

    private final String city;

    public CityState(String city) {
        this.city = city;
    }

    public static void setGoalCity(String newGoalCity) {
        goalCity = newGoalCity;
    }

    public String getCity() {
        return city;
    }

    @Override
    public boolean isGoal() {
        return city.equals(goalCity);
    }

    @Override
    public String toString() {
        return city;
    }

    // two states are equal when they have the same city
    @Override
    public boolean equals(Object o) {
        if (this == o) return true;
        if (!(o instanceof CityState)) return false;
        CityState other = (CityState) o;
        return city.equals(other.city);
    }

    @Override
    public int hashCode() {
        return city.hashCode();
    }
}
