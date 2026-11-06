package sa2026.problems.citymap;

import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.TreeMap;

/**
 * The map: cities and the roads between them. Every road has a length (in km).
 * The roads go both ways: A -> B has the same length as B -> A.
 *
 * For each city we keep its neighbors and the road length:
 *   roads.get("A") = {C=5, D=12, S=10}
 * We use a TreeMap, so the neighbors are always in ABC order
 * (the same order as the lesson page).
 */
public class CityMap {

    /**
     * Map<String, Map<String, Integer>> — a dictionary whose keys are city names (String),
     * and whose values are another dictionary (Map<String, Integer>).
     * The inner Map<String, Integer> — neighbor name → distance in km
     * roads = {
     *   "A": { "C": 5,  "D": 12, "S": 10 },
     *   "B": { "D": 8,  "E": 4,  "S": 12 },
     *   "C": { "A": 5,  "F": 2 },
     *   ...
     * }
     */
    private final Map<String, Map<String, Integer>> roads = new TreeMap<>();

    // adds a city with no roads (yet)
    public void addCity(String city) {
        /*
         * putIfAbsent = insert only if the key is missing.
         * If the city exists, do nothing (so you don't wipe out its existing roads).
         */
        roads.putIfAbsent(city, new TreeMap<>());
    }

    // adds a road in both directions
    public void addRoad(String from, String to, int km) {
        // Validate: a road must be longer than 0 km. Otherwise throw an error.
        if (km <= 0) {
            throw new IllegalArgumentException("A road must be longer than 0 km, not " + km + ".");
        }
        /*
         * Ensure both endpoints exist (auto-create them with addCity, which is safe due to putIfAbsent).
         * Store the edge in both directions — from → to and to → from, with the same length.
         * This makes the graph undirected (as the comment says: A→B = B→A).
         */
        addCity(from);
        addCity(to);
        roads.get(from).put(to, km);
        roads.get(to).put(from, km);
    }

    // the map of the lesson page (ucs.html): the same graph as in BFS and DFS, now with road lengths
    public static CityMap example() {
        CityMap map = new CityMap();
        map.addRoad("S", "A", 10);
        map.addRoad("S", "B", 12);
        map.addRoad("A", "C", 5);
        map.addRoad("A", "D", 12);
        map.addRoad("B", "D", 8);
        map.addRoad("B", "E", 4);
        map.addRoad("C", "F", 2);
        map.addRoad("D", "G", 11);
        map.addRoad("E", "G", 5);
        map.addRoad("F", "G", 1);
        return map;
    }

    public boolean hasCity(String city) {
        return roads.containsKey(city);
    }

    // the cities we can drive to from this city, in ABC order
    public List<String> getNeighbors(String city) {
        /*
         * Looks up the city's inner map,
         * then .keySet() = just the neighbor names (not the distances).
         * Because the inner map is a TreeMap, they come in alphabetical order —
         * the search algorithm will expand neighbors in ABC order.
         *
         * new ArrayList<>(...) = we return a COPY of the names, not the keySet() itself.
         * keySet() is a live view of our map: removing a name from it would delete
         * that road from the map (in one direction only!). With a copy, the caller
         * can not change our map by mistake. Python and C++ also return a new list.
         */
        return new ArrayList<>(roadsOf(city).keySet());
    }

    // the length of the road between two neighbor cities
    public int getDistance(String from, String to) {
        /*
         * Example: getDistance("A", "C")
         *   roadsOf("A")            // → { C=5, D=12, S=10 }
         *        .get("C")          // → Integer 5   (found!)
         *   Integer km = ...        // km = 5
         *   if (km == null) ...     // 5 == null → false, skip
         *   return km;              // auto-unbox Integer 5 → int 5
         * If there is no road (for example "A" to "G"), get() returns null, so we throw an error.
         */
        Integer km = roadsOf(from).get(to);
        if (km == null) {
            throw new IllegalArgumentException("There is no road from " + from + " to " + to + ".");
        }
        return km;
    }

    /*
     * The roads of a city, or a clear error if the city is not on the map.
     * Without this check, roads.get("Z") returns null, and the next call on it
     * gives a NullPointerException that does not say which city is wrong.
     */
    private Map<String, Integer> roadsOf(String city) {
        Map<String, Integer> cityRoads = roads.get(city);
        if (cityRoads == null) {
            throw new IllegalArgumentException("Unknown city: " + city + ". It is not on the map.");
        }
        return cityRoads;
    }
}
