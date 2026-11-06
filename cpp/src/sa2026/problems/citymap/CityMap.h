#pragma once

#include <map>
#include <string>
#include <vector>

namespace sa2026::problems::citymap {

/*
 * The map: cities and the roads between them. Every road has a length (in km).
 * The roads go both ways: A -> B has the same length as B -> A.
 *
 * For each city we keep its neighbors and the road length:
 *   roads["A"] = {C: 5, D: 12, S: 10}
 * We use std::map (like TreeMap in Java), so the neighbors are always in ABC order
 * (the same order as the lesson page).
 */
class CityMap {
public:
    // adds a city with no roads (yet)
    void addCity(const std::string& city);

    // adds a road in both directions
    void addRoad(const std::string& from, const std::string& to, int km);

    // the map of the lesson page (ucs.html): the same graph as in BFS and DFS, now with road lengths
    static CityMap example();

    bool hasCity(const std::string& city) const;

    // the cities we can drive to from this city, in ABC order
    std::vector<std::string> getNeighbors(const std::string& city) const;

    // the length of the road between two neighbor cities
    int getDistance(const std::string& from, const std::string& to) const;

private:
    /*
     * std::map<std::string, std::map<std::string, int>> — a dictionary whose keys are city names (std::string),
     * and whose values are another dictionary (std::map<std::string, int>).
     * The inner std::map<std::string, int> — neighbor name → distance in km
     * roads = {
     *   "A": { "C": 5,  "D": 12, "S": 10 },
     *   "B": { "D": 8,  "E": 4,  "S": 12 },
     *   "C": { "A": 5,  "F": 2 },
     *   ...
     * }
     */
    std::map<std::string, std::map<std::string, int>> roads;
};

}  // namespace sa2026::problems::citymap
