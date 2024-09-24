class SortedList:
    """Implements a modified list"""

    def search(list, element):
        """
        Allows to search for an element inside the list. Returns false if the element is not found.

        Arguments:
            list: the list of interest
            element: the element to search for

        Returns:
            either the element (if found) or false
        """
        min = 0
        max = len(list) - 1
        while min <= max:
            middle = min + (max - min) // 2
            if list[middle] == element:
                return middle
            elif list[middle] < element:
                min = middle + 1
            else:
                max = middle - 1
        return False

    
    def insert(list, element):
        """
        Allows to insert an element inside the list. Launches an exception if the starting index is less than 0.

        Arguments:
            list: the list of interest
            element: the element to be inserted
        
        Returns:
            the element, be it freshly inserted or already present.
        """
        min = 0
        max = len(list)
        if min < 0:
            raise ValueError('min must be non-negative')
        if max is None:
            max = len(list)
        while min < max:
            middle = (min+max)//2
            if element < list[middle]:
                max = middle
            elif element == list[middle]:
                return list[middle]
            else:
                min = middle+1
        list.insert(min, element)
        return list[min]

        