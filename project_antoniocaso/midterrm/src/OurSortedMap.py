class SortedMap:
    """Implements a modified map"""

    def search(map,element):
        """
        Allows to search for an element inside the map. Returns false if the element is not found.

        Arguments:
            map: the map of interest
            element: the element to search for

        Returns:
            either the element (if found) or false
        """
        min = 0
        max = len(map) - 1
        while min <= max:
            middle = min + (max - min) // 2
            if map[middle][0] == element:
                return map[middle]
            elif map[middle][0] < element:
                min = middle + 1
            else:
                max = middle - 1
        return False

    
    def insert(map, element):
        """
        Allows to insert an element inside the map. Launches an exception if the starting index is less than 0.

        Arguments:
            map: the map of interest
            element: the element to be inserted
        
        Returns:
            the element, be it freshly inserted or already present.
        """
        min = 0
        max = len(map)
        while min < max:
            middle = (min+max)//2
            if element[0] < map[middle][0]:
                max = middle
            else:
                min = middle+1
        map.insert(min, element)
        return map[min]

        