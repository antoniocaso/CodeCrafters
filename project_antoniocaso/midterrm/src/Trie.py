
class TrieNode:
    """"Implements the node of the trie"""
    def __init__(self):
        """TrieNode constructor, which initializes the children (number of potential children), isEndOfWord (whether the node is actually
        the one marking the end of a word) and pageList (reference to the occurrence list of that word) attributes."""
        self.children = [None]*95
        self.isEndOfWord = False
        self.pageList = None
 
class Trie:
    """Implements a trie"""
    def __init__(self):
        """Trie constructor, which initializes the root (root Node) of the trie"""
        self.root = self.getNode()
 
    def getNode(self):
        """Despite the name, this method is used to generete and return a blank node"""
        return TrieNode()
 
    def _charToIndex(self,ch):
        """
        Returns the ASCII index associated to a certain character

        Arguments:
            ch: the character of interest

        Returns:
            the associated index
        """
        # Converts key current character into index         
        return ord(ch)-ord(' ')

 
    def insert(self,key):
        """
        Allows to insert a node as an another node's child. This happens only if the node is not already present. Regardless, the node
        containing the last letter of the keyword 

        Arguments:
            key: the word to be inserted
        """
        pCrawl = self.root
        length = len(key)
        for level in range(length):
            index = self._charToIndex(key[level])
            if not pCrawl.children[index]:
                pCrawl.children[index] = self.getNode()
            pCrawl = pCrawl.children[index]
            
        pCrawl.isEndOfWord = True  
 
    def search(self, key):
        """
        Allows to search for a word inside the trie. If the word is present, the node containing
        the last letter of the word is returned

        Arguments:
            key: the word to be searched

        Returns:
            Either false is the word is absent or the node containing the last letter if the word
            is present.
        """ 
        pCrawl = self.root
        length = len(key)
        for level in range(length):
            index = self._charToIndex(key[level])
            if not pCrawl.children[index]:
                return False
            pCrawl = pCrawl.children[index]
        return pCrawl
 