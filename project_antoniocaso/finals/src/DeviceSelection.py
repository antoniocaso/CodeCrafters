class DeviceSelection:
    """
    Class which implements the structure and the elements used to recover the most-efficient devices
    and relative back-up devices.
    """
    def __init__(self,N, X, data):
        """
        Constructor of the class. Sets both the graph attribute to the actual graph, and the number
        of nodes.

        Arguments:  
            N: tuple of strings
            X: integer
            data: dictionary
        """
        self.num_nodes=len(N)
        graph = {}
        for device in N:
            graph[device] = []
            for other_device in N:
                if device == other_device:
                    continue
                dominates = True
                for i in range(X-2):
                    if data[other_device][i] >= data[device][i]:
                        dominates = False
                        break
                if dominates:
                    graph[device].append(other_device)
        self.graph = graph     
        
                
    def bpm(self, u, matchR, seen):
        """
        Utility to execute bipartite matching. The purpose of this function is to find 
        a matching between two sets of nodes in a bipartite graph.

        Arguments:
            u: a node in the graph
            matchR: a dictionary representing the matching
            seen: a dictionary indicating which nodes have been seen during the search

        Returns:
            either true of false
        """
    # Iterate over the values in the self.graph[u] list
        for v, device in enumerate(self.graph[u]):
            if not seen[device]:
                seen[device] = True
                if matchR[device] is None or self.bpm(matchR[device], matchR, seen):
                    matchR[device] = u
                    return True
        return False

    def maxBPM(self):
        """
        Allows to find the maximum bipartite matching in a graph. A bipartite matching 
        is a set of edges connecting nodes from two different sets in a bipartite graph, such that no 
        two edges share a common end node. The maximum bipartite matching is the largest possible 
        matching in the graph, with the maximum number of edges.

        Arguments:

        Returns:
            dictionary containing the maximum matching from which it is possible to infer groups
        """
        d={nodes: None for nodes in self.graph} #Dizionario contenente {Dispositivo: None}
        match = {nodes: None for nodes in self.graph} #Dizionario che rappresenta il matching
        self.capi_groups=[] #Usata per conservare i capi gruppo, così da poter poi partire da loro a scorrere i dominati
        for u in self.graph:
            seen = {node: False for node in self.graph}
            self.bpm(u, match, seen)
        for k,v in match.items():
            if v is not None:
                d[v]=k
            else:
                self.capi_groups.append(k)
        return d

    def countDevices(self):
        """
        Allows to count the number of connected components found, and thus the number of sets
        which benefit from the Interleaving Property.

        Arguments:

        Returns:
            integer
        """
        bp_graph=self.maxBPM()
        #print("Procedo a ricavare le componenti connesse dotate di Interleaving Property...")
        self.get_groups(bp_graph)
        #print("Le componenti connesse sono: ")
        #print(format_list(self.groups))
        #print("Il numero di componenti è:")
        return len(self.groups)

    def nextDevice(self,i):
        """
        Allows to recover the nth-best device in a certain group.

        Arguments:
            i: integer

        Returns:
            string identifying a device
        """
        if i not in range(0,len(self.groups)+1):
            raise Exception("Il gruppo indicato non esiste!\nRiprovare con un numero tra 0 e %d" %(len(self.groups)-1))
        if(len(self.groups[i])==0):
            return None
        else:
            return str(self.groups[i].pop(0))

    def get_groups(self, two_sets):
        """
        Utility function used to recover and identify connected components amongst the maximum 
        bipartite matching. When over, the groups attribute will contain a number of lists each
        containing devices ordered by their dominancy (that is, sets benefiting from the property).

        Arguments:
            two_sets: a dictionary representing the maximum bipartite matching

        Returns:
            
        """
        self.groups = []
        for head in self.capi_groups:
            group_for_head = []
            group_for_head.append(head)
            previous =  head
            following = two_sets[previous]
            while following != None:
                group_for_head.append(following)
                previous = following
                following = two_sets[previous]
            self.groups.append(group_for_head)






 
     

