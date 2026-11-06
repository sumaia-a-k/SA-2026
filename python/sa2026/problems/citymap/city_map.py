class CityMap:
    """
    The map: cities and the roads between them. Every road has a length (in km).
    The roads go both ways: A -> B has the same length as B -> A.

    For each city we keep its neighbors and the road length:
      self._roads["A"] = {"C": 5, "D": 12, "S": 10}
    get_neighbors() gives them in ABC order (the same order as the lesson page).
    """

    def __init__(self):
        # dict[str, dict[str, int]] — a dictionary whose keys are city names (str),
        # and whose values are another dictionary (dict[str, int]).
        # The inner dict[str, int] — neighbor name → distance in km
        # _roads = {
        #   "A": { "C": 5,  "D": 12, "S": 10 },
        #   "B": { "D": 8,  "E": 4,  "S": 12 },
        #   "C": { "A": 5,  "F": 2 },
        #   ...
        # }
        self._roads: dict[str, dict[str, int]] = {}

    # adds a city with no roads (yet)
    def add_city(self, city: str):
        # Insert only if the key is missing (like putIfAbsent in Java).
        # If the city exists, do nothing (so you don't wipe out its existing roads).
        if city not in self._roads:
            self._roads[city] = {}

    # adds a road in both directions
    def add_road(self, from_city: str, to_city: str, km: int):
        # Validate: a road must be longer than 0 km. Otherwise raise an error.
        if km <= 0:
            raise ValueError(f"A road must be longer than 0 km, not {km}.")
        # Ensure both endpoints exist (auto-create them with add_city, which is safe: it never wipes a city).
        # Store the edge in both directions — from → to and to → from, with the same length.
        # This makes the graph undirected (A→B = B→A).
        self.add_city(from_city)
        self.add_city(to_city)
        self._roads[from_city][to_city] = km
        self._roads[to_city][from_city] = km

    # the map of the lesson page (ucs.html): the same graph as in BFS and DFS, now with road lengths
    @staticmethod
    def example() -> "CityMap":
        city_map = CityMap()  # not "map": map is a Python function
        city_map.add_road("S", "A", 10)
        city_map.add_road("S", "B", 12)
        city_map.add_road("A", "C", 5)
        city_map.add_road("A", "D", 12)
        city_map.add_road("B", "D", 8)
        city_map.add_road("B", "E", 4)
        city_map.add_road("C", "F", 2)
        city_map.add_road("D", "G", 11)
        city_map.add_road("E", "G", 5)
        city_map.add_road("F", "G", 1)
        return city_map

    def has_city(self, city: str) -> bool:
        return city in self._roads

    # the cities we can drive to from this city, in ABC order
    def get_neighbors(self, city: str) -> list[str]:
        # Looks up the city's inner dict. sorted() on a dict gives just the keys
        # (the neighbor names, not the distances), as a new list in alphabetical order —
        # the search algorithm will expand neighbors in ABC order.
        # We need sorted(): a Python dict keeps the order we ADDED the keys, not ABC order
        # (Java's TreeMap does the sorting for us).
        # sorted() makes a new list (a copy), so the caller can not change our map by mistake.
        return sorted(self._roads[city])

    # the length of the road between two neighbor cities
    def get_distance(self, from_city: str, to_city: str) -> int:
        # Example: get_distance("A", "C")
        #   self._roads["A"]           # → {"C": 5, "D": 12, "S": 10}
        #   "C" not in ... ?           # "C" is there → False, skip
        #   self._roads["A"]["C"]      # → 5
        # If there is no road (for example "A" to "G"), we raise an error ourselves.
        # (Without the check, self._roads["A"]["G"] would raise a KeyError, which is less clear.)
        if to_city not in self._roads[from_city]:
            raise ValueError(f"There is no road from {from_city} to {to_city}.")
        return self._roads[from_city][to_city]
