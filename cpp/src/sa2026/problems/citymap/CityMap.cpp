#include "sa2026/problems/citymap/CityMap.h"

#include <stdexcept>

namespace sa2026::problems::citymap {

void CityMap::addCity(const std::string& city) {
    /*
     * roads[city] = insert only if the key is missing (like putIfAbsent in Java):
     * if the city is not there, [] adds it with an empty map.
     * If the city exists, it does nothing (so you don't wipe out its existing roads).
     */
    roads[city];
}

void CityMap::addRoad(const std::string& from, const std::string& to, int km) {
    // Validate: a road must be longer than 0 km. Otherwise throw an error.
    if (km <= 0) {
        throw std::invalid_argument("A road must be longer than 0 km, not " + std::to_string(km) + ".");
    }
    /*
     * Store the edge in both directions — from → to and to → from, with the same length.
     * This makes the graph undirected (A→B = B→A).
     * We do not need to call addCity() first (Java does): in C++, roads[from]
     * already creates the city if it is missing.
     */
    roads[from][to] = km;
    roads[to][from] = km;
}

CityMap CityMap::example() {
    CityMap map;
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

bool CityMap::hasCity(const std::string& city) const {
    return roads.count(city) > 0;
}

std::vector<std::string> CityMap::getNeighbors(const std::string& city) const {
    /*
     * Looks up the city's inner map, then takes just the neighbor names (not the distances).
     * Because the inner map is a std::map, the loop goes in alphabetical order —
     * the search algorithm will expand neighbors in ABC order.
     * We return a new vector (a copy), so the caller can not change our map by mistake.
     * (Java returns a live view with keySet(), not a copy.)
     */
    std::vector<std::string> neighbors;
    // at() is like [] but it does not add a missing city (and it works on a const map)
    for (const auto& [neighbor, km] : roads.at(city)) {
        neighbors.push_back(neighbor);
    }
    return neighbors;
}

int CityMap::getDistance(const std::string& from, const std::string& to) const {
    /*
     * Example: getDistance("A", "C")
     *   roads.at("A")             // → { C: 5, D: 12, S: 10 }
     *   neighbors.find("C")       // → points to the pair (C, 5)   (found!)
     *   road == neighbors.end()   // false, skip
     *   return road->second;      // 5
     * If there is no road (for example "A" to "G"), find() returns end(), so we throw an error.
     */
    const auto& neighbors = roads.at(from);
    auto road = neighbors.find(to);
    if (road == neighbors.end()) {
        throw std::invalid_argument("There is no road from " + from + " to " + to + ".");
    }
    return road->second;  // first = the neighbor, second = the km
}

}  // namespace sa2026::problems::citymap
